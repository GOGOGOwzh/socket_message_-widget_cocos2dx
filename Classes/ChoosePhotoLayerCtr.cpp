//
//  ChoosePhotoLayerCtr.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#include "ChoosePhotoLayerCtr.h"

void ChoosePhotoLayerCtr::getMessage(Message *msg)
{
    
}

ChoosePhotoLayer *ChoosePhotoLayerCtr::createLayer(std::string strnum)
{
    std::stringstream ss;
    ss<<strnum;
    int num;
    ss>>num;
    std::string path = StringUtils::format("%d.png",num);
    return ChoosePhotoLayer::createLayer(path);
}