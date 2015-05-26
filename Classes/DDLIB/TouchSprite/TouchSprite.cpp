//
//  TouchSprite.cpp
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//

#include "TouchSprite.h"

TouchSprite * TouchSprite::create(int priority,bool isSwallow)
{
    TouchSprite * ret = new TouchSprite(priority,isSwallow);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else{
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void TouchSprite::touchEvent(Touch * touch,Event * event)
{
    CCLOG("这个应该可以");
}

void TouchSprite::onEnter()
{
    Sprite::onEnter();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_isSwallow);
    
    listener->onTouchBegan = [=](Touch * touch , Event * event){
        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        Size s = this->getContentSize();
        
        Rect rect = Rect(0,0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode)) {
            CCLOG("touch begin");
            return true;
        }
        return false;
    };
    
    listener->onTouchEnded = [=](Touch * touch,Event * event){
        CCLOG("touch end");
        this->touchEvent(touch,event);
    };
    
    if (this->_priority != 0) {
        _eventDispatcher->addEventListenerWithFixedPriority(listener, this->_priority);
    }
    else{
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    
    this->_listener = listener;
}

void TouchSprite::onExit(){
    _eventDispatcher->removeEventListener(this->_listener);
    Sprite::onExit();
}
