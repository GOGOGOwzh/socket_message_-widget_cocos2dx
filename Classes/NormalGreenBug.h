//
//  NormalGreenBug.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#ifndef __PressBug_0_1__NormalGreenBug__
#define __PressBug_0_1__NormalGreenBug__

#include "Bug.h"

class NormalGreenBug:public Bug
{
public:
    NormalGreenBug();
public:
    static NormalGreenBug * create();
public:
    void onEnter() override;
    void onExit() override;
};


#endif /* defined(__PressBug_0_1__NormalGreenBug__) */
