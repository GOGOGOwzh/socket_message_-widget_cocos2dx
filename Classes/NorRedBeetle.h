//
//  NorRedBeetle.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#ifndef __PressBug_0_1__NorRedBeetle__
#define __PressBug_0_1__NorRedBeetle__

#include "Bug.h"
class NorRedBeetle:public Bug
{
public:
    NorRedBeetle();
public:
    static NorRedBeetle * create();
public:
    void onEnter() override;
    void onExit() override;
    void touchEvent(Touch * touch,Event * event);
    void directDieAction() override;
};

#endif /* defined(__PressBug_0_1__NorRedBeetle__) */
