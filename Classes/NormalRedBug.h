//
//  NormalRedBug.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#ifndef __PressBug_0_1__NormalRedBug__
#define __PressBug_0_1__NormalRedBug__

#include "Bug.h"
#include "GameStartLayer.h"
class NormalRedBug:public Bug
{
public:
    NormalRedBug();
    NormalRedBug(float blood,float angle,float speed);
public:
    static NormalRedBug * create();
    static NormalRedBug * create(float blood,float angle,float speed);
public:
    void onEnter() override;
    void onExit() override;
public:
    
};

#endif /* defined(__PressBug_0_1__NormalRedBug__) */
