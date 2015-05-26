//
//  NormalGreenBug.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#include "NormalGreenBug.h"
NormalGreenBug::NormalGreenBug():Bug(BugType::normalGreenBug)
{
    
}

NormalGreenBug * NormalGreenBug::create()
{
    auto bug = new NormalGreenBug();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

void NormalGreenBug::onEnter()
{
    Bug::onEnter();
}

void NormalGreenBug::onExit()
{
    Bug::onExit();
}