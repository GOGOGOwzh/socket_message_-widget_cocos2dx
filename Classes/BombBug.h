//
//  BombBug.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#ifndef __PressBug_0_1__BombBug__
#define __PressBug_0_1__BombBug__

#include "Bug.h"
#include "GameStartLayer.h"

class BombBug:public Bug
{
public:
    BombBug();
public:
    static BombBug * create();
public:
    void onEnter() override;
    void onExit() override;
    void touchEvent(Touch * touch,Event * event) override;
    void directDieAction() override;
};

#endif /* defined(__PressBug_0_1__BombBug__) */
