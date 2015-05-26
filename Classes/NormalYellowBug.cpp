//
//  NormalYellowBug.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/5.
//
//

#include "NormalYellowBug.h"

NormalYellowBug::NormalYellowBug():Bug(BugType::normalYellowBug)
{
    
}

NormalYellowBug * NormalYellowBug::create()
{
    auto bug = new NormalYellowBug();
    if (bug) {
        return bug;
    }
    CC_SAFE_DELETE(bug);
    return nullptr;
}

void NormalYellowBug::onEnter()
{
    Bug::onEnter();
}

void NormalYellowBug::onExit()
{
    Bug::onExit();
}