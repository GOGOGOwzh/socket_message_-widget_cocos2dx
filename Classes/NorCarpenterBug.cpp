//
//  NorCarpenterBug.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#include "NorCarpenterBug.h"

NorCarpenterBug::NorCarpenterBug():Bug(norCarpenterBug)
{
    
}

NorCarpenterBug * NorCarpenterBug::create()
{
    auto bug = new NorCarpenterBug();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

void NorCarpenterBug::onEnter()
{
    Bug::onEnter();
}

void NorCarpenterBug::onExit()
{
    Bug::onExit();
}

void NorCarpenterBug::touchEvent(Touch * touch, Event * event)
{
    this->dereaseBlood();
    if (_blood <=0) {
        this->directDieAction();
    }
}

void NorCarpenterBug::dereaseBlood()
{
    _blood = _blood - 0.25;
}

void NorCarpenterBug::directDieAction()
{
    _score = 15;
    this->postMsg(true);
    
    _blood = 0;
    this->unschedule(schedule_selector(Bug::randMove));
    this->stopAllActions();
    
    auto sp1 = Sprite::createWithSpriteFrameName("worm2_die.png");
    sp1->setPosition(this->getContentSize().width/2,this->getContentSize().height/8-sp1->getContentSize().height/2);
    this->addChild(sp1);
    
    this->setSpriteFrame("worm2_die.png");
    this->setScale(0.5);
    auto delay = DelayTime::create(0.6);
    this->runAction(Sequence::create(delay,CallFunc::create(CC_CALLBACK_0(Bug::dieAction, this)) ,NULL));
}