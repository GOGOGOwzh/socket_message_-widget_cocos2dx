//
//  NormalBlueBug.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/4.
//
//

#ifndef __PressBug_0_1__NormalBlueBug__
#define __PressBug_0_1__NormalBlueBug__

#include "Bug.h"

class NormalBlueBug:public Bug
{
public:
    NormalBlueBug();
public:
    static NormalBlueBug * create();
public:
    void onEnter() override;
    void onExit() override;
};

#endif /* defined(__PressBug_0_1__NormalBlueBug__) */
