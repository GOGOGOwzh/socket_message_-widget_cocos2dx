//
//  GameStartLayerCtr.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#ifndef __PressBug_0_1__GameStartLayerCtr__
#define __PressBug_0_1__GameStartLayerCtr__

#include "DDLIB/Share/IncludeFile.h"
#include "GameStartLayer.h"
#include "SkillManager.h"

class GameStartLayerCtr:public MessageContrDelegate
{
private:
    static GameStartLayer * _layer;
public:
    GameStartLayerCtr();
    static GameStartLayer * createLayer(std::string);
public:
    void registeMsg();
    void getMessage(Message*) override;
};

#endif /* defined(__PressBug_0_1__GameStartLayerCtr__) */
