//
//  BombBug.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#include "BombBug.h"

BombBug::BombBug():Bug(BugType::bombBug)
{
    
}

BombBug * BombBug::create()
{
    auto bug = new BombBug();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

void BombBug::onEnter()
{
    Bug::onEnter();
}

void BombBug::onExit()
{
    Bug::onExit();
}

void BombBug::touchEvent(Touch *touch, Event *event)
{
    this->dereaseBlood();
    
    if (_blood <=0) {
        this->directDieAction();
//        this->unschedule(schedule_selector(Bug::randMove));
//        this->stopAllActions();
//        this->setSpriteFrame("effect_1000_0.png");
//        this->setScale(1.2);
//        Vector<SpriteFrame*> arr;
//        char str[100] = {0};
//        for (int i = 0; i<12; i++) {
//            sprintf(str,"effect_1000_%d.png",i);
//            arr.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
//        }
//        
//        auto animation = Animation::createWithSpriteFrames(arr,1.0/11.0);
//        auto animate = Animate::create(animation);
//
//        auto delay = DelayTime::create(0.6);
//        
//        auto pos = this->getPosition();
//        auto size = this->getContentSize();
//        
//        ((GameStartLayer*)this->getParent())->bombBugEffect(pos, size);
//        
//        this->runAction(Sequence::create(animate,delay,CallFunc::create(CC_CALLBACK_0(Bug::dieAction, this)) ,NULL));
    }
}

void BombBug::directDieAction()
{
    _blood = 0;
    this->unschedule(schedule_selector(Bug::randMove));
    this->stopAllActions();
    this->setSpriteFrame("effect_1000_0.png");
    this->setScale(1.2);
    Vector<SpriteFrame*> arr;
    char str[100] = {0};
    for (int i = 0; i<12; i++) {
        sprintf(str,"effect_1000_%d.png",i);
        arr.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
    }
    
    auto animation = Animation::createWithSpriteFrames(arr,1.0/11.0);
    auto animate = Animate::create(animation);
    
    auto delay = DelayTime::create(0.6);
    
    auto pos = this->getPosition();
    auto size = this->getContentSize();
    
    ((GameStartLayer*)this->getParent())->bombBugEffect(pos, size);
    this->runAction(Sequence::create(animate,delay,CallFunc::create(CC_CALLBACK_0(Bug::dieAction, this)) ,NULL));
}