//
//  NormalRedBug.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#include "NormalRedBug.h"
NormalRedBug::NormalRedBug():Bug(BugType::normalRedBug)
{
    
}

NormalRedBug::NormalRedBug(float blood,float angle,float speed):Bug(BugType::normalRedBug,blood,angle,speed)
{
    
}

NormalRedBug * NormalRedBug::create()
{
    auto bug = new NormalRedBug();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

NormalRedBug * NormalRedBug::create(float blood,float angle,float speed)
{
    auto bug = new NormalRedBug(blood,angle,speed);
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}


void NormalRedBug::onEnter()
{
    Bug::onEnter();
}

void NormalRedBug::onExit()
{
    Bug::onExit();
}