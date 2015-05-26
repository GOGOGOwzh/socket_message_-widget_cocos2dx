//
//  Bug.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/4.
//
//

#ifndef __PressBug_0_1__Bug__
#define __PressBug_0_1__Bug__

#include "cocos2d.h"
#include "SkillManager.h"
#include "SourceManager.h"
#include "MsgTable.h"
#include "DDLIB/Share/IncludeFile.h"
USING_NS_CC;

enum BugType
{
    normalBlueBug = 1,
    normalGreenBug,
    normalRedBug,
    normalYellowBug,
    bombBug,
    norCarpenterBug,
    norMosquito,
    norYellowBeetle,
    norRedBeetle
};

class Bug:public Sprite
{
    CC_SYNTHESIZE(int, _mode, Mode); //0 默认随机模式 1 自定义模式
    CC_SYNTHESIZE(int, _score, Score);
    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE(float, _blood, Blood);
    CC_SYNTHESIZE(float, _angle, Angle);
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(float, _iceSpeed, IceSpeed)
    CC_SYNTHESIZE(bool, _isHole, IsHole)
    CC_SYNTHESIZE(EventListener *, _listener, listener);
protected:
    float _runTime;
public:
    Bug(int type);
    Bug(int type,float blood,float angle,float speed);
public:
    void onEnter() override;
    void onExit() override;
public:
    void randDir();
    void randBlood();
    void randSpeed();
    void createBug();
    void createPosAndDir();
public:
    virtual void dereaseBlood();
    virtual void directDieAction();
    virtual void dieAction();
    virtual void randMove(float);
    virtual void touchEvent(Touch * touch,Event * event);
public:
    void postMsg(bool);
};

#endif /* defined(__PressBug_0_1__Bug__) */
