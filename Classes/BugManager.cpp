//
//  BugManager.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#include "BugManager.h"

BugManager * BugManager::_inst = nullptr;

BugManager * BugManager::getInstance()
{
    if (!_inst) {
        _inst = new BugManager();
    }
    return _inst;
}

Bug * BugManager::createBug(int type)
{
    Bug *bug = nullptr;
    switch (type) {
        case BugType::normalBlueBug :
            bug = NormalBlueBug::create();
            break;
        case BugType::normalGreenBug :
            bug = NormalGreenBug::create();
            break;
        case BugType::normalRedBug :
            bug = NormalRedBug::create();
            break;
        case BugType::normalYellowBug :
            bug = NormalYellowBug::create();
            break;
        case BugType::bombBug :
            bug = BombBug::create();
            break;
        case BugType::norCarpenterBug :
            bug = NorCarpenterBug::create();
            break;
        case BugType::norMosquito :
            bug = NorMosquito::create();
            break;
        case BugType::norYellowBeetle :
            bug = NorYellowBeetle::create();
            break;
        case BugType::norRedBeetle :
            bug = NorRedBeetle::create();
            break;
        default:
            break;
    }
    
    return bug;
}

Vector<Bug*> BugManager::createMoreBug()
{
    Vector<Bug*> bugList;
    for (int i = 0; i<25;i++) {
        int num =rand()%4+1;
        auto bug = _inst->createBug(num);
        bugList.pushBack(bug);
    }
    return bugList;
}