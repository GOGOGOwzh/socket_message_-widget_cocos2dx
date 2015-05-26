//
//  MsgTable.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#ifndef __PressBug_0_1__MsgTable__
#define __PressBug_0_1__MsgTable__

#include <iostream>

class MsgTable
{
public:
    ///SCENE MESSAGE
    static std::string CHANGE_TO_CHOOSEPHOTO_LAYER;
    static std::string CHANGE_TO_CLICKSTART_LAYER;
    static std::string CHANGE_TO_SELSKILL_LAYER;
    static std::string CHANGE_TO_GAMESTART_LAYER;
    static std::string CHANGE_TO_SHOP_LAYER;
    
    ///SKILL MESSAGE
    static std::string SKILL_ICE;
    static std::string SKILL_HOLE;
    static std::string SKILL_LASER;
    static std::string SKILL_GUN;
    static std::string SKILL_MORE;
    
    ///SCORE MESSAGE
    static std::string SCORE_CHANGE;
};
#endif /* defined(__PressBug_0_1__MsgTable__) */
