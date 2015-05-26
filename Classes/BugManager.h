//
//  BugManager.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#ifndef __PressBug_0_1__BugManager__
#define __PressBug_0_1__BugManager__

#include "NorMosquito.h"
#include "NorYellowBeetle.h"
#include "NorRedBeetle.h"
#include "NorCarpenterBug.h"
#include "NormalBlueBug.h"
#include "NormalYellowBug.h"
#include "NormalGreenBug.h"
#include "NormalRedBug.h"
#include "BombBug.h"

class BugManager
{
private:
    static BugManager * _inst;
public:
    static BugManager * getInstance();
    
    Bug * createBug(int);
    Vector<Bug*> createMoreBug();
};

#endif /* defined(__PressBug_0_1__BugManager__) */
