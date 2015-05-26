//
//  NorMosquito.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#include "NorMosquito.h"

NorMosquito::NorMosquito():Bug(BugType::norMosquito)
{
    
}

NorMosquito * NorMosquito::create()
{
    auto bug = new NorMosquito();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

void NorMosquito::onEnter()
{
    Bug::onEnter();
}

void NorMosquito::onExit()
{
    Bug::onExit();
}

void NorMosquito::touchEvent(Touch* touch, Event* event)
{
    this->dereaseBlood();
    
    if (_blood <=0) {
        this->directDieAction();
    }
}

void NorMosquito::dieOtherBug()
{
    ((GameStartLayer*)this->getParent())->dieAllNorBlueBug();
}

void NorMosquito::directDieAction()
{
    _blood = 0;
    this->unschedule(schedule_selector(Bug::randMove));
    this->stopAllActions();
    this->setSpriteFrame("worm1_die.png");
    this->dieOtherBug();
    auto delay = DelayTime::create(0.6);
    
    this->runAction(Sequence::create(delay,CallFunc::create(CC_CALLBACK_0(Bug::dieAction, this)) ,NULL));
}