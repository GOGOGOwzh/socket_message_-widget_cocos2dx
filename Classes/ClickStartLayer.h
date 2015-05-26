//
//  ClickStartLayer.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#ifndef __PressBug_0_1__ClickStartLayer__
#define __PressBug_0_1__ClickStartLayer__

#include "DDLIB/Share/IncludeFile.h"

USING_NS_CC;
class ClickStartLayer:public Layer
{
    int _bgNum;
public:
    bool init() override;
public:
    void createUI();
    void createTouchLayer();
    void createBug(float);
    void endLayer();
public:
    void soundBtnCallback(Ref*);
    CREATE_FUNC(ClickStartLayer);
};

#endif /* defined(__PressBug_0_1__ClickStartLayer__) */
