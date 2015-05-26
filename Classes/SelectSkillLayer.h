//
//  SelectSkillLayer.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#ifndef __PressBug_0_1__SelectSkillLayer__
#define __PressBug_0_1__SelectSkillLayer__

#include "DDLIB/Share/IncludeFile.h"
#include "SourceManager.h"
#include "SkillManager.h"

class SelectSkillLayer:public Layer
{
private:
    std::string _path;
    int _showListCount;
public:
    SelectSkillLayer(std::string);
    bool init() override;
    static SelectSkillLayer * createLayer(std::string);
public:
    void createUI();
    void createSkillIconPos();
    void endLayer();
    void sureBtnCallback(Ref*);
    void skillIconCallback(Ref*);
};

#endif /* defined(__PressBug_0_1__SelectSkillLayer__) */
