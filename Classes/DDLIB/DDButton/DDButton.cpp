//
//  DDButton.cpp
//  DDLIB
//
//  Created by wzh on 15/3/2.
//
//

#include "DDButton.h"

DDButton::DDButton(std::string normal,std::string sel,bool mode):callback(nullptr),normalname(normal),selname(sel),flagMode(mode),_enable(true),_enableScroll(true),_swallow(true),_lis(nullptr)
{
    
}

DDButton::~DDButton()
{
    
}

DDButton * DDButton::createFromFile(std::string normalfilename,std::string selfilename)
{
    DDButton * button = new DDButton(normalfilename,selfilename,false);
    if (button && button->init()) {
        button->initWithFile(normalfilename);
        button->autorelease();
    }
    return button;
}

DDButton * DDButton::createFromFrame(std::string normalframename,std::string selframename)
{
    DDButton * button = new DDButton(normalframename,selframename,true);
    if (button && button->init()) {
        button->initWithSpriteFrameName(normalframename);
        button->autorelease();
    }
    return button;
}

bool DDButton::init()
{
    if (!Sprite::init()) {
        return false;
    }

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](Touch * touch , Event * event)
    {
        return this->onTouchBegan(touch,event);
    };
    
    listener->onTouchMoved =[=](Touch* touch,Event * event)
    {
        this->onTouchMoved(touch,event);
    };
    
    listener->onTouchEnded =[=](Touch * touch, Event * event)
    {
        this->onTouchEnded(touch,event);
    };
    
    _lis = listener;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void DDButton::onEnter()
{
    Sprite::onEnter();
}

void DDButton::onExit()
{
    _eventDispatcher->removeEventListenersForTarget(this);
    Sprite::onExit();
}

bool DDButton::onTouchBegan(Touch * touch, Event * event)
{
    
    Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
    
    Size s = this->getContentSize();
    
    Rect rect = Rect(0,0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode) && _enable == true) {
        
        _moveBeginPosY = touch->getLocation().y;
        
        if (this->getSelname() != "") {
            if (flagMode == false) {
                this->setTexture(this->getSelname());
            }else{
                this->setSpriteFrame(this->getSelname());
            }
        }else{
            this->setScale(0.8);
        }
        return true;
    }
    return false;
}

void DDButton::onTouchMoved(Touch *touch, Event * event)
{
    Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
    Size s = this->getContentSize();
    
    Rect rect = Rect(0,0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode)) {
        if (this->getSelname() != "") {
            if (flagMode == false) {
                this->setTexture(this->getNormalname());
            }else{
                this->setSpriteFrame(this->getNormalname());
            }
        }else{
            this->setScale(0.8);
        }
    }
}

void DDButton::onTouchEnded(Touch * touch,Event * event)
{
    Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
    Size s = this->getContentSize();
    
    Rect rect = Rect(0,0, s.width, s.height);
    
    if (this->getSelname() != "") {
        if (flagMode == false) {
            this->setTexture(this->getNormalname());
        }else{
            this->setSpriteFrame(this->getNormalname());
        }
    }else{
        this->setScale(1);
    }
    
    if (rect.containsPoint(locationInNode)) {
        if (callback) {
            if (_enableScroll) {
                float _moveEndPosY = touch->getLocation().y;
                float _acceptableDis = _moveEndPosY - _moveBeginPosY;
                if (ACCEPTABLEDIS >= std::abs(_acceptableDis)) {
                    callback(this);
                }
            }
            else
            {
                callback(this);
            }
        }
    }
}

void DDButton::setSwallowEnable(bool able)
{
    _lis->setSwallowTouches(able);
}

void DDButton::addCallBackListener(const ccMenuCallback & callback)
{
    this->callback = callback;
}
