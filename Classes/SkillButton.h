//
//  SkillButton.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/12.
//
//

#ifndef __PressBug_0_1__SkillButton__
#define __PressBug_0_1__SkillButton__

#include "DDLIB/DDButton/DDButton.h"
#include "SkillManager.h"
#include "MsgTable.h"
#include "DDLIB/Share/IncludeFile.h"

class SkillButton:public Sprite
{
private:
    int _type;
    bool _touchEnable;
    EventListenerTouchOneByOne * _listener;
    
    Sprite * _cold;
    Sprite * _enerying;
    Sprite * _ready;
    Sprite * _readyAni;
    Sprite * _icon;
    
    ProgressTimer * _coldingTimer;
    
public:
    SkillButton(int);
    static SkillButton * create(int);
public:
    void onEnter() override;
    void onExit() override;
public:
    void onTouchBegan(Touch* ,Event *);
public:
    void initSp();
    void coldAnimation(float);
    void readyAnimation(float);
    void stopReadyAnimation();
    void startEnery();
    void readySkill();
};


#endif /* defined(__PressBug_0_1__SkillButton__) */
