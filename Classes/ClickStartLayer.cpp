//
//  ClickStartLayer.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#include "ClickStartLayer.h"
#include "DDLIB/Share/VisibleRect.h"
#include "BugManager.h"
#include "MsgTable.h"

bool ClickStartLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    this->createUI();
    return true;
}

void ClickStartLayer::createUI()
{
    _bgNum = rand()%5;
    char strNum[30] = {0};
    sprintf(strNum, "%d.png",_bgNum);
    
    auto bgSprite = Sprite::create(strNum);
    bgSprite->setPosition(VisibleRect::center());
    this->addChild(bgSprite,-2);
    
    auto logo = Sprite::createWithSpriteFrameName("logo.png");
    logo->setPosition(bgSprite->getPositionX(),bgSprite->getPositionY() + 200);
    this->addChild(logo);
    
    auto clickSp = Sprite::createWithSpriteFrameName("touchtostart_0.png");
    clickSp->setPosition(bgSprite->getPositionX(),bgSprite->getPositionY()-100);
    this->addChild(clickSp);
    
    Vector<SpriteFrame*> anim;
    char strName[100] = {0};
    for (int i=0; i<7; i++) {
        sprintf(strName, "touchtostart_%d.png",i);
        anim.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(strName));
    }
    auto clickAnimation = Animation::createWithSpriteFrames(anim, 0.1);
    auto clickAnimate = Animate::create(clickAnimation);
    
    clickSp->runAction(RepeatForever::create(clickAnimate));
    
    this->schedule(schedule_selector(ClickStartLayer::createBug), 1.2);
    this->createTouchLayer();
    
    DDButton * soundBtn = DDButton::createFromFrame("music_on.png");
    soundBtn->setPosition(VisibleRect::width()-100,VisibleRect::height()/12);
    this->addChild(soundBtn);
}

void ClickStartLayer::createBug(float dt)
{
    int bugNum = rand()%3+1;
    this->addChild(BugManager::getInstance()->createBug(bugNum),-1);
}

void ClickStartLayer::createTouchLayer()
{
    auto layer = Layer::create();
    this->addChild(layer);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch * touch,Event * event)
    {
        return true;
    };
    
    listener->onTouchEnded = [=](Touch * touch,Event * event)
    {
        Message * msg = Message::create(MsgTable::CHANGE_TO_CHOOSEPHOTO_LAYER,StringUtils::format("%d",_bgNum));
        MessageCenter::getInstance()->postMessage(msg);
        this->endLayer();
    };
    
    layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
}

void ClickStartLayer::endLayer()
{
    this->unschedule(schedule_selector(ClickStartLayer::createBug));
    this->removeAllChildren();
    this->removeFromParent();
}

void ClickStartLayer::soundBtnCallback(Ref * pSender)
{
    
}