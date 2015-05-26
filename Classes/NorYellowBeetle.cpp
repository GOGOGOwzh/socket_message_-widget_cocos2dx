//
//  NorYellowBeetle.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#include "NorYellowBeetle.h"

NorYellowBeetle::NorYellowBeetle():Bug(BugType::norYellowBeetle)
{
    _extraScorePath.push_back("10.png");
    _extraScorePath.push_back("25.png");
    _extraScorePath.push_back("50.png");
}

NorYellowBeetle * NorYellowBeetle::create()
{
    auto bug = new NorYellowBeetle();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

void NorYellowBeetle::onEnter()
{
    Bug::onEnter();
}

void NorYellowBeetle::onExit()
{
    Bug::onExit();
}

void NorYellowBeetle::touchEvent(Touch * touch,Event * event)
{
    this->dereaseBlood();
    
    if (_blood <=0) {
        this->directDieAction();
    }
}

void NorYellowBeetle::directDieAction()
{
    _blood = 0;
    this->unschedule(schedule_selector(Bug::randMove));
    this->stopAllActions();
    this->setSpriteFrame("worm4_die.png");
    
    int randScore = rand()%3;
    if (randScore == 0) {
        _score = 10;
    }
    else if (randScore == 1)
    {
        _score = 25;
    }
    else
    {
        _score = 50;
    }
    this->postMsg(true);
    
    auto path = _extraScorePath.at(randScore);
    auto scoreSp = Sprite::create(path);
    scoreSp->setTag(20);
    scoreSp->setScale(2);
    scoreSp->setPosition(this->getPosition());
    this->getParent()->addChild(scoreSp);
    
    auto fadeOut = FadeOut::create(1.2);
    scoreSp->runAction(fadeOut);
    
    auto delay = DelayTime::create(0.6);
    
    this->runAction(Sequence::create(delay,CallFunc::create(CC_CALLBACK_0(Bug::dieAction, this)) ,NULL));
}