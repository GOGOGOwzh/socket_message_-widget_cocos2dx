//
//  MessageContrDelegate.h
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//

#ifndef __DDLIB__MessageContrDelegate__
#define __DDLIB__MessageContrDelegate__

#include <iostream>
#include "cocos2d.h"
#include "Message.h"
USING_NS_CC;

class MessageContrDelegate :public Ref{
public:
    virtual void getMessage(Message * msg) = 0;
};

#endif /* defined(__DDLIB__MessageContrDelegate__) */
