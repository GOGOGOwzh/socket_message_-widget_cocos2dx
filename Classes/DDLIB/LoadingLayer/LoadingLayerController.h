//
//  LoadingLayerController.h
//  DDLIB
//
//  Created by wzh on 14-11-25.
//
//

#ifndef __DDLIB__LoadingLayerController__
#define __DDLIB__LoadingLayerController__

#include <iostream>
#include "LoadingLayer.h"
#include "../DDMsgModule/MessageContrDelegate.h"

class LoadingLayerController :public MessageContrDelegate
{
public:
    void getMessage(Message * msg) override ;
};
#endif /* defined(__DDLIB__LoadingLayerController__) */
