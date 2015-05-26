//
//  ShopLayerCtr.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#ifndef __PressBug_0_1__ShopLayerCtr__
#define __PressBug_0_1__ShopLayerCtr__

#include "DDLIB/Share/IncludeFile.h"
#include "ShopLayer.h"
class ShopLayerCtr:public MessageContrDelegate
{
    CC_SYNTHESIZE(ShopLayer*, _layer, Layer);
public:
    ShopLayerCtr();
public:
    void getMessage(Message *);
};

#endif /* defined(__PressBug_0_1__ShopLayerCtr__) */
