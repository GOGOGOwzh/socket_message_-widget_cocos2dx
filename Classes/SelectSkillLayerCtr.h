//
//  SelectSkillLayerCtr.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#ifndef __PressBug_0_1__SelectSkillLayerCtr__
#define __PressBug_0_1__SelectSkillLayerCtr__

#include "SelectSkillLayer.h"
#include "DDLIB/Share/IncludeFile.h"

class SelectSkillLayerCtr:public MessageContrDelegate
{
public:
    void getMessage(Message*) override;
public:
    SelectSkillLayer * createLayer(std::string);
};

#endif /* defined(__PressBug_0_1__SelectSkillLayerCtr__) */
