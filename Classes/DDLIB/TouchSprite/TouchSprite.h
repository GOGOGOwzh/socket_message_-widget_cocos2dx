//
//  TouchSprite.h
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//  TouchSprite 可以继承使用，并重写touchEvent，分发点击事件

#ifndef __DDLIB__TouchSprite__
#define __DDLIB__TouchSprite__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class TouchSprite:public Sprite
{
private:
    EventListener * _listener;
    int _priority;
    bool _isSwallow;
public:
    TouchSprite(int priority , bool isSwallow ):_listener(nullptr),_priority(priority),_isSwallow(isSwallow)
    {}
public:
    static TouchSprite * create(int priority = 0, bool isSwallow = false);
    
    // bool init() override;
    virtual void touchEvent(Touch * touch,Event * event);
    void onEnter() override;
    void onExit() override;
};


#endif /* defined(__DDLIB__TouchSprite__) */
