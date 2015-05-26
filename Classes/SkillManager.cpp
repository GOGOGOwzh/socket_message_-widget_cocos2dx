//
//  SkillManager.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/14.
//
//

#include "SkillManager.h"

SkillManager * SkillManager::_inst = nullptr;

SkillManager::SkillManager():_ice(false),_laser(false),_hole(false),_gun(false),_more(false),_gunCount(5)
{
    _selectedSkill.clear();
}

SkillManager * SkillManager::getInstance()
{
    if (_inst == nullptr) {
        _inst = new SkillManager();
    }
    return _inst;
}

