//
//  NorYellowBeetle.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/6.
//
//

#ifndef __PressBug_0_1__NorYellowBeetle__
#define __PressBug_0_1__NorYellowBeetle__

#include "Bug.h"
#include <iostream>
class NorYellowBeetle:public Bug
{
private:
    std::vector<std::string> _extraScorePath;
public:
    NorYellowBeetle();
public:
    static NorYellowBeetle * create();
public:
    void onEnter() override;
    void onExit() override;
    void touchEvent(Touch * touch,Event * event) override;
    void directDieAction() override;
};

#endif /* defined(__PressBug_0_1__NorYellowBeetle__) */
