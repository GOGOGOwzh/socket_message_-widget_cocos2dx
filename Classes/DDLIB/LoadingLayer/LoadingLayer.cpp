//
//  LoadingLayer.cpp
//  DDLIB
//
//  Created by wzh on 14-11-25.
//
//

#include "LoadingLayer.h"

LoadingLayer * LoadingLayer::create(LoadingLayer::LODDINGTYPE type)
{
    LoadingLayer * ret = new LoadingLayer();
    if (ret && ret->init()) {
        ret->createLayer(type);
        return ret;
    }
    return nullptr;
}

bool LoadingLayer::init()
{
    if (Layer::init()) {
        return false;
    }
    
    return true;
}

void LoadingLayer::createLayer(LoadingLayer::LODDINGTYPE type)
{
    if (type == LODDINGTYPE::LOADING) {
        this->createLoadingLayer();
    }
    else if (type == LODDINGTYPE::CONNECTING){
        this->createConnectingLayer();
    }
}

void LoadingLayer::createConnectingLayer()
{
    
}

void LoadingLayer::createLoadingLayer()
{
    
}
