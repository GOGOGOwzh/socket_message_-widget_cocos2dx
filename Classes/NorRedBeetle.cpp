//
//  NorRedBeetle.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#include "NorRedBeetle.h"
#include "NormalRedBug.h"

NorRedBeetle::NorRedBeetle():Bug(BugType::norRedBeetle)
{
    
}

NorRedBeetle * NorRedBeetle::create()
{
    auto bug = new NorRedBeetle();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

void NorRedBeetle::onEnter()
{
    Bug::onEnter();
}

void NorRedBeetle::onExit()
{
    Bug::onExit();
}

void NorRedBeetle::touchEvent(Touch * touch,Event * event)
{
    this->dereaseBlood();
    if (_blood <= 0) {
        
        this->directDieAction();
    }
}

void NorRedBeetle::directDieAction()
{
    
    this->postMsg(true);
    _blood = 0;
    this->unschedule(schedule_selector(Bug::randMove));
    this->stopAllActions();
    this->setSpriteFrame("worm3_die.png");
    
    auto parent = this->getParent();
    auto pos = this->getPosition();
    for (int i = 0; i<=7; i++) {
        auto angle = i*45.0/180.0*3.1415926;
        auto bug = NormalRedBug::create(1,angle, 12);
        bug->setRotation(i*45);
        bug->setPosition(pos);
        parent->addChild(bug);
    }
    
    auto delay = DelayTime::create(0.6);
    
    this->runAction(Sequence::create(delay,CallFunc::create(CC_CALLBACK_0(Bug::dieAction, this)) ,NULL));
}