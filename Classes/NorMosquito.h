//
//  NorMosquito.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#ifndef __PressBug_0_1__NorMosquito__
#define __PressBug_0_1__NorMosquito__

#include "Bug.h"
#include "GameStartLayer.h"

class NorMosquito:public Bug
{
public:
    NorMosquito();
public:
    static NorMosquito * create();
public:
    void onEnter() override;
    void onExit() override;
    void touchEvent(Touch * touch,Event * event) override;
    void directDieAction() override;
public:
    void dieOtherBug();
};

#endif /* defined(__PressBug_0_1__NorMosquito__) */
