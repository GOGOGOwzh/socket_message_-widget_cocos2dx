//
//  SkillManager.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/14.
//
//

#ifndef __PressBug_0_1__SkillManager__
#define __PressBug_0_1__SkillManager__

#include "cocos2d.h"

enum SkillType
{
    skill_laser = 0,
    skill_ice,
    skill_hole,
    skill_gun,
    skill_more
};

class SkillManager
{
    CC_SYNTHESIZE(bool, _ice, IceSkill)
    CC_SYNTHESIZE(bool, _laser, LaserSkill)
    CC_SYNTHESIZE(bool, _hole, HoleSkill)
    CC_SYNTHESIZE(bool, _gun, GunSkill)
    CC_SYNTHESIZE(bool, _more, MoreSkill)
    CC_SYNTHESIZE(int, _gunCount, GunCount)
    
private:
    static SkillManager * _inst;
    SkillManager();
private:
    std::vector<int> _selectedSkill;
public:
    static SkillManager * getInstance();
public:
    std::vector<int> & getSelectedSkill(){return _selectedSkill;}
};

#endif /* defined(__PressBug_0_1__SkillManager__) */
