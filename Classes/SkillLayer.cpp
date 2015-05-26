//
//  SkillLayer.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/12.
//
//

#include "SkillLayer.h"

SkillLayer::SkillLayer(std::vector<int> array):_skillArry(array),_listener(nullptr),_lineSp(nullptr),_touchSp(nullptr),_laserSkilBg(nullptr)
{
    _laserLineArray.clear();
    _laserTouchArray.clear();
}

SkillLayer * SkillLayer::create(std::vector<int> array)
{
    auto layer = new SkillLayer(array);
    if (layer && layer->init()) {
        return layer;
    }
    
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool SkillLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->createUI();
    
    return true;
}

void SkillLayer::onEnter()
{
    Layer::onEnter();
    this->createCacheAin();
}

void SkillLayer::createCacheAin()
{
    Vector<SpriteFrame*> lineArray;
    for (int i=0; i<4; i++) {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("light_%d.png",i));
        lineArray.pushBack(frame);
    }
    
    auto lineAimation = Animation::createWithSpriteFrames(lineArray);
    AnimationCache::getInstance()->addAnimation(lineAimation, "lineAnimation");
 
    Vector<SpriteFrame*> touchArray;
    for (int i=0; i<4; i++) {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("touch_%d.png",i));
        touchArray.pushBack(frame);
    }
    
    auto touchAimation = Animation::createWithSpriteFrames(touchArray);
    AnimationCache::getInstance()->addAnimation(touchAimation, "touchAnimation");
    
}

void SkillLayer::createSkill()
{
    _laserSkilBg = Sprite::createWithSpriteFrameName("laser_bg.png");
    _laserSkilBg->setPosition(VisibleRect::center());
    this->addChild(_laserSkilBg);
    
    _lineSp = Sprite::createWithSpriteFrameName("light_0.png");
    _lineSp->setPositionY(VisibleRect::center().y);
    _lineSp->setVisible(false);
    this->addChild(_lineSp);
    auto lineAin = AnimationCache::getInstance()->getAnimation("lineAnimation");
    auto lineAimate = Animate::create(lineAin);
    _lineSp->runAction(RepeatForever::create(lineAimate));
    
    _touchSp = Sprite::createWithSpriteFrameName("touch_0.png");
    _touchSp->setPositionX(_lineSp->getContentSize().width/2);
    _lineSp->addChild(_touchSp);
    auto touchAin = AnimationCache::getInstance()->getAnimation("touchAnimation");
    auto touchAimate = Animate::create(touchAin);
    _touchSp->runAction(RepeatForever::create(touchAimate));

}

void SkillLayer::destorySkill()
{
    _laserSkilBg->removeFromParent();
    _touchSp->stopAllActions();
    _lineSp->stopAllActions();
    
    _lineSp->removeFromParent();
    _lineSp = nullptr;
    
    SkillManager::getInstance()->setLaserSkill(false);
}

Vec2 SkillLayer::getLaserSkillPos()
{
    return _lineSp->getPosition();
}

Sprite * SkillLayer::getLaserSkill()
{
    return _lineSp;
}

void SkillLayer::createUI()
{
    auto skill1Sp = Sprite::createWithSpriteFrameName("skill_6.png");
    skill1Sp->setTag(0);
    skill1Sp->setPosition(VisibleRect::left().x +70, VisibleRect::height()/12-10);
    this->addChild(skill1Sp);
    
    auto skill2Sp = Sprite::createWithSpriteFrameName("skill_6.png");
    skill2Sp->setTag(100);
    skill2Sp->setPosition(skill1Sp->getPositionX() + skill1Sp->getContentSize().width+5, skill1Sp->getPositionY());
    this->addChild(skill2Sp);
    
    auto skill3Sp = Sprite::createWithSpriteFrameName("skill_6.png");
    skill3Sp->setTag(200);
    skill3Sp->setPosition(skill2Sp->getPositionX() + skill2Sp->getContentSize().width+5, skill2Sp->getPositionY());
    this->addChild(skill3Sp);

    if (_skillArry.size() > 0) {
        for (int i=0; i<_skillArry.size(); i++) {
            auto num = _skillArry.at(i);
            auto skill = SkillButton::create(num);
            skill->setPosition(VisibleRect::left().x +70 + i*(skill->getContentSize().width+5),VisibleRect::height()/12-10);
            this->addChild(skill);
            
            this->getChildByTag(i*100)->removeFromParent();
        }
    }
}

void SkillLayer::createTouchEvent()
{
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch *touch,Event * event)
    {
        return this->onTouchBegan(touch, event);
    };
    listener->onTouchMoved = [=](Touch *touch,Event * event)
    {
        this->onTouchMove(touch, event);
    };
    
    listener->onTouchEnded = [=](Touch* touch,Event* event)
    {
        this->onTouchMove(touch, event);
    };
    
    _listener = listener;
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
    
    this->scheduleOnce(schedule_selector(SkillLayer::removeTouchEvent), 4);
    
    this->createSkill();
}

void SkillLayer::removeTouchEvent(float dt)
{
    this->getEventDispatcher()->removeEventListener(_listener);
    _listener = nullptr;
    this->destorySkill();
}

bool SkillLayer::onTouchBegan(Touch * touch, Event * event)
{
    if (SkillManager::getInstance()->getLaserSkill()) {
        auto pos = _lineSp->convertToNodeSpace(touch->getLocation());
        _lineSp->setVisible(true);
        _lineSp->setPositionX(touch->getLocation().x);
        _touchSp->setPositionY(pos.y);
        
        return true;
    }
    return false;
}

void SkillLayer::onTouchMove(Touch* touch, Event * event)
{
    auto pos = _lineSp->convertToNodeSpace(touch->getLocation());
    _lineSp->setPositionX(touch->getLocation().x);
    _touchSp->setPositionY(pos.y);
}

void SkillLayer::onTouchEnd(Touch * touch, Event* event)
{
    _lineSp->setVisible(false);
}