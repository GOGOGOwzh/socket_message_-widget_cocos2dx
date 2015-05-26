//
//  SkillButton.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/12.
//
//

#include "SkillButton.h"

SkillButton::SkillButton(int type):_listener(nullptr),_touchEnable(true),_type(type)
{
    this->initWithSpriteFrameName(StringUtils::format("skill_%d.png",type));
    this->initSp();
}

SkillButton * SkillButton::create(int num)
{
    auto btn = new SkillButton(num);
    if (btn) {
        btn->startEnery();
        return btn;
    }
    return nullptr;
}

void SkillButton::onEnter()
{
    Sprite::onEnter();
    _listener = EventListenerTouchOneByOne::create();
    _listener->setSwallowTouches(false);
    _listener->onTouchBegan = [=](Touch*touch,Event*event)
    {
        auto locationInNode = this->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
        if (rect.containsPoint(locationInNode) && _touchEnable) {
            this->onTouchBegan(touch, event);
            return true;
        }
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
}

void SkillButton::onExit()
{
    Sprite::onExit();
}

void SkillButton::initSp(){
    
    _readyAni = Sprite::createWithSpriteFrameName("usable_effect.png");
    _readyAni->setVisible(false);
    _readyAni->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    this->addChild(_readyAni);
    
    _icon = Sprite::createWithSpriteFrameName(StringUtils::format("skill_%d.png",_type));
    _icon->setVisible(false);
    _icon->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    this->addChild(_icon);
    
    _ready = Sprite::createWithSpriteFrameName("skill_usable.png");
    _ready->setVisible(false);
    _ready->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    this->addChild(_ready);
    
    _cold = Sprite::createWithSpriteFrameName("cd.png");
    
    _coldingTimer = ProgressTimer::create(_cold);
    _coldingTimer->setReverseDirection(true);
    _coldingTimer->setVisible(false);
    _coldingTimer->setType(ProgressTimer::Type::RADIAL);
    _coldingTimer->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    this->addChild(_coldingTimer);
    
    _enerying = Sprite::createWithSpriteFrameName("skill_waiting.png");
    _enerying->setVisible(false);
    _enerying->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    this->addChild(_enerying);
}

void SkillButton::onTouchBegan(Touch* touch, Event *event)
{
    Message * msg = nullptr;
    if (_type == SkillType::skill_laser) {
        msg = Message::create(MsgTable::SKILL_LASER);
    }
    else if (_type == SkillType::skill_ice)
    {
        msg = Message::create(MsgTable::SKILL_ICE);
    }
    else if (_type == SkillType::skill_hole)
    {
        msg = Message::create(MsgTable::SKILL_HOLE);
    }
    else if (_type == SkillType::skill_gun)
    {
        msg = Message::create(MsgTable::SKILL_GUN);
    }
    else if (_type == SkillType::skill_more)
    {
        msg = Message::create(MsgTable::SKILL_MORE);
    }
    else if (_type == 5)
    {
        
    }
    
    MessageCenter::getInstance()->postMessage(msg);
    
    this->stopReadyAnimation();
    this->startEnery();
}

void SkillButton::coldAnimation(float)
{
    float per = _coldingTimer->getPercentage();
    if (per > 0 ) {
       _coldingTimer->setPercentage(per-5);
    }else
    {
        this->unschedule(schedule_selector(SkillButton::coldAnimation));
        _coldingTimer->setVisible(false);
        _enerying->setVisible(false);
        
        this->readyAnimation(0);
    }
    
}

void SkillButton::stopReadyAnimation()
{
    _readyAni->stopAllActions();
    _readyAni->setVisible(false);
    _ready->setVisible(false);
    this->_touchEnable = true;
}

void SkillButton::readyAnimation(float)
{
    this->_touchEnable = true;
    _readyAni->setVisible(true);
    _ready->setVisible(true);
    _icon->setVisible(true);
    
    auto ani = RotateBy::create(1, 180);
    _readyAni->runAction(RepeatForever::create(ani));
}

void SkillButton::startEnery()
{
    this->_touchEnable = false;
    _coldingTimer->setVisible(true);
    _enerying->setVisible(true);
    _coldingTimer->setPercentage(100);
    
    this->schedule(schedule_selector(SkillButton::coldAnimation), 0.5);
}

void SkillButton::readySkill()
{
    
}
