//
//  Bug.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/4.
//
//

#include "Bug.h"

Bug::Bug(int ty):_type(ty),_blood(1),_angle(0.0),_speed(3.0),_runTime(0.0),_mode(0),_isHole(false)
{
    _score = _blood;
    this->createBug();
}

Bug::Bug(int type,float blood,float angle,float speed):_type(type),_blood(blood),_angle(angle),_speed(speed),_runTime(0.0),_mode(1),_isHole(false)
{
    _score = _blood;
    this->createBug();
}

void Bug::onEnter()
{
    Sprite::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch * touch ,Event * event)
    {
        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        Size s = this->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && _blood > 0 && SkillManager::getInstance()->getGunSkill() == false) {
            this->touchEvent(touch,event);
            return true;
        }
        return false;
    };
    
    this->_listener = listener;
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Bug::onExit()
{
    _eventDispatcher->removeEventListener(this->_listener);
    Sprite::onExit();
}

void Bug::touchEvent(Touch *touch, Event *event)
{
    this->dereaseBlood();
    
    if (_blood <=0) {
        this->postMsg(true);
        
        this->unschedule(schedule_selector(Bug::randMove));
        this->stopAllActions();
        this->setSpriteFrame(String::createWithFormat("worm%d_die.png",_type)->getCString());
        
        auto delay = DelayTime::create(0.6);
        
        this->runAction(Sequence::create(delay,CallFunc::create(CC_CALLBACK_0(Bug::dieAction, this)) ,NULL));
    }
}

void Bug::dieAction()
{
    this->unscheduleAllCallbacks();
    this->stopAllActions();
    this->removeFromParent();
}

void Bug::directDieAction()
{
    this->postMsg(true);
    _blood = 0;
    this->unschedule(schedule_selector(Bug::randMove));
    this->stopAllActions();
    this->setSpriteFrame(String::createWithFormat("worm%d_die.png",_type)->getCString());
    
    auto delay = DelayTime::create(1);
    
    this->runAction(Sequence::create(delay,CallFunc::create(CC_CALLBACK_0(Bug::dieAction, this)) ,NULL));
}

void Bug::dereaseBlood()
{
    _blood --;
    if (_type != BugType::norCarpenterBug) {
        this->setScale(_blood*0.5+0.5);
    }
}

void Bug::randBlood()
{
    if (_mode == 0) {  //随机模式
        int randNum = rand()%100 +1;
        if (randNum >= 1 && randNum <= 85) {
            _blood = 1;
        }
        else if (randNum > 85 && randNum <= 95){
            _blood = 2;
        }
        else{
            _blood = 3;
        }
        
        if (_type == BugType::norCarpenterBug) {    //正常毛毛虫
            _blood = 1;
        }
        else if (_type == BugType::norYellowBeetle){ //
            _blood = 3;
        }
        else if (_type == BugType::norRedBeetle){
            _blood = 4;
        }
        else if (_type == BugType::bombBug){
            _blood = 1;
        }
        else if (_type == BugType::norMosquito){
            _blood = 1;
        }
        
        CCLOG("randNum %d",randNum);
        
    }
    else  //自定义模式
    {
        
    }
    this->setScale(_blood*0.5+0.5);
}

void Bug::randSpeed()
{
    if (_mode == 0) {
        int randNum = rand()%100;
        if (randNum <= 40) {
            _speed = rand()%4+3;   ///3--7的速度
        }
        else if( randNum> 40 && randNum <= 70)
        {
            _speed = rand()%4+ 8;
        }
        else
        {
            _speed = rand()%3 + 12;
        }
        
        if (_type == BugType::bombBug) {
            _speed = 10;
        }
    }
    else
    {
        
    }
    _iceSpeed = _speed;
}

void Bug::randMove(float dt)
{
    _runTime = _runTime + 0.01;
    auto pos = this->getPosition();
    if ((pos.x <  VisibleRect::leftBottom().x - this->getContentSize().height) || (pos.x > VisibleRect::right().x + this->getContentSize().height)) {
//        this->postMsg(false);
        this->dieAction();
    }else{
        if (_runTime - 1.0 > 0 && _mode == 0) {
            this->randDir();
        }
    
        if (SkillManager::getInstance()->getIceSkill()) {
            _speed = _speed * 0.6;
        }
        else
        {
            _speed = _iceSpeed;
        }
        
        if (SkillManager::getInstance()->getHoleSkill()) {
            if (_isHole == false) {
                auto moveToCenter = MoveTo::create(1, VisibleRect::center());
                Sequence * seq = nullptr;
                if (_type == BugType::norCarpenterBug or _type == BugType::norRedBeetle) {
                    seq = Sequence::create(moveToCenter, NULL);
                }
                else
                {
                    seq = Sequence::create(moveToCenter,CallFunc::create(CC_CALLBACK_0(Bug::directDieAction, this)), NULL);
                }
                seq->setTag(20);
                this->runAction(seq);
                _isHole = true;
            }
        }
        else
        {
            auto act = this->getActionByTag(20);
            if (act) {
                this->stopAction(act);
            }
            if (_mode == 0) {
                this->setPosition(this->getPositionX() + _speed*cos(_angle),this->getPositionY()+ _speed*sin(_angle));
            }
            else
            {
                this->setPosition(this->getPositionX() - _speed*sin(_angle),this->getPositionY()- _speed*cos(_angle));
            }
        }
        

    }
}

void Bug::randDir()
{
    int isChange = rand()%100 +1;
    if (isChange >=10) {  //三分之一的概率会改变方向
        CCLOG("change !!");
        float angle = rand()%180+60;
        _angle += angle/180*3.14;
        this->setRotation(270-_angle*180/3.14);
    }
    _runTime = 0.0;
}

void Bug::createBug()
{
    auto frameName = String::createWithFormat("worm%d_0.png",_type);
    this->initWithSpriteFrameName(frameName->getCString());
    
    this->createPosAndDir();
    this->randSpeed();
    this->randBlood();
    
    Vector<SpriteFrame*> animFrams;
    for (int i =0; i<2; i++) {
        std::string  strName;
        if (i == 0) {
            strName = StringUtils::format("worm%d_0.png",_type);
        }else
        {
            strName = StringUtils::format("worm%d_1.png",_type);
        }
        auto frameName = SpriteFrameCache::getInstance()->getSpriteFrameByName(strName.c_str());
        animFrams.pushBack(frameName);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrams,0.5);
    auto animate = Animate::create(animation);
    
    this->runAction(RepeatForever::create(animate));
    
    this->schedule(schedule_selector(Bug::randMove),0.01);
}

void Bug::createPosAndDir()
{
    if (_mode == 0) {
        auto visibleSize = VisibleRect::getVisibleRect().size;
        float posEdgeX = 0.0;
        float posEdgeY = 0.0;
        
        int fullD=(visibleSize.width+visibleSize.height-185-133)*2;
        int d=abs(rand())%fullD;
        
        if (d>fullD-visibleSize.height+185+133) {
            posEdgeX=0;
            posEdgeY=visibleSize.height-d%(int)(fullD-visibleSize.height+185);
        }else if (d<=fullD-visibleSize.height+185+133&&d>fullD/2) {
            posEdgeX=visibleSize.width-d%(fullD/2);
            posEdgeY=visibleSize.height-133;
        }else if (d<=fullD/2&&d>visibleSize.width) {
            posEdgeX=visibleSize.width;
            posEdgeY=d%(int)visibleSize.width+185;
        }else if (d<=visibleSize.width) {
            posEdgeX=d;
            posEdgeY=185;
        }
        
        _angle=atan2f(((visibleSize.height-185)/2-posEdgeY),(visibleSize.width/2-posEdgeX));
        this->setRotation(-_angle/3.14*180+270);
        this->setPosition(Vec2(posEdgeX,posEdgeY));
    }
    else
    {
        this->setRotation(_angle);
    }
}

void Bug::postMsg(bool addOrDecr)
{
//    if(addOrDecr == false)
//    {
//        _score = -_score;
//    }
    
    SourceManager::getInstance()->setScore(_score);
}