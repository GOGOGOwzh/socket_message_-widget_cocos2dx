//
//  SelectSkillLayerCtr.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#include "SelectSkillLayerCtr.h"

void SelectSkillLayerCtr::getMessage(Message * msg)
{
    
}

SelectSkillLayer * SelectSkillLayerCtr::createLayer(std::string path)
{
    return SelectSkillLayer::createLayer(path);
}