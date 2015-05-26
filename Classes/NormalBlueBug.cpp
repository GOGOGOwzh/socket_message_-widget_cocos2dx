//
//  NormalBlueBug.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/4.
//
//

#include "NormalBlueBug.h"

NormalBlueBug::NormalBlueBug():Bug(BugType::normalBlueBug)
{
    
}

NormalBlueBug * NormalBlueBug::create()
{
    auto bug = new NormalBlueBug();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

void NormalBlueBug::onEnter()
{
    Bug::onEnter();
}

void NormalBlueBug::onExit()
{
    Bug::onExit();
}