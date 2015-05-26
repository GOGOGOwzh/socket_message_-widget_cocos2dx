//
//  NorCarpenterBug.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#ifndef __PressBug_0_1__NorCarpenterBug__
#define __PressBug_0_1__NorCarpenterBug__

#include "Bug.h"
class NorCarpenterBug:public Bug
{
private:

public:
    NorCarpenterBug();
public:
    static NorCarpenterBug * create();
public:
    void onEnter() override;
    void onExit() override;
    void touchEvent(Touch*,Event*) override;
    void dereaseBlood() override;
    void directDieAction() override;
};

#endif /* defined(__PressBug_0_1__NorCarpenterBug__) */
