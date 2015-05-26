//
//  NormalYellowBug.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/5.
//
//

#ifndef __PressBug_0_1__NormalYellowBug__
#define __PressBug_0_1__NormalYellowBug__

#include "Bug.h"
class NormalYellowBug:public Bug
{
public:
    NormalYellowBug();
public:
    static NormalYellowBug * create();
public:
    void onEnter() override;
    void onExit() override;
};
#endif /* defined(__PressBug_0_1__NormalYellowBug__) */
