//
//  LoadingLayer.h
//  DDLIB
//
//  Created by wzh on 14-11-25.
//
//

#ifndef __DDLIB__LoadingLayer__
#define __DDLIB__LoadingLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class LoadingLayer:public Layer
{
public:
    enum LODDINGTYPE
    {
        CONNECTING,
        LOADING
    };
public:
    static LoadingLayer * create(LODDINGTYPE);
public:
    bool init() override;
    void createLayer(LODDINGTYPE);
    void createConnectingLayer();
    void createLoadingLayer();
};
#endif /* defined(__DDLIB__LoadingLayer__) */
