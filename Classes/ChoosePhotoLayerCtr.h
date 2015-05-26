//
//  ChoosePhotoLayerCtr.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#ifndef __PressBug_0_1__ChoosePhotoLayerCtr__
#define __PressBug_0_1__ChoosePhotoLayerCtr__

#include "ChoosePhotoLayer.h"
#include "DDLIB/DDMsgModule/MessageContrDelegate.h"

class ChoosePhotoLayerCtr:public MessageContrDelegate
{
private:
    ChoosePhotoLayer * _layer;
public:
    void getMessage(Message*) override;
    ChoosePhotoLayer * createLayer(std::string);
};
#endif /* defined(__PressBug_0_1__ChoosePhotoLayerCtr__) */
