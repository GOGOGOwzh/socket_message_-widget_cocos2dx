//
//  ClickStartLayerCtr.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#ifndef __PressBug_0_1__ClickStartLayerCtr__
#define __PressBug_0_1__ClickStartLayerCtr__

#include "ClickStartLayer.h"
#include "DDLIB/Share/IncludeFile.h"

class ClickStartLayerCtr:public MessageContrDelegate
{
    CC_SYNTHESIZE_RETAIN(ClickStartLayer *, _layer, Layer)
public:
    ClickStartLayerCtr();
public:
    void getMessage(Message * msg) override;
};

#endif /* defined(__PressBug_0_1__ClickStartLayerCtr__) */
