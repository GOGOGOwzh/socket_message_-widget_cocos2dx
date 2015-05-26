//
//  ClickStartLayerCtr.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#include "ClickStartLayerCtr.h"

ClickStartLayerCtr::ClickStartLayerCtr():_layer(nullptr)
{
    this->setLayer(ClickStartLayer::create());
}

void ClickStartLayerCtr::getMessage(Message *msg)
{
    
}
