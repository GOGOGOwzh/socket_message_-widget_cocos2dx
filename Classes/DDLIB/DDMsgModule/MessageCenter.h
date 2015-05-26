//
//  MessageCenter.h
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//

#ifndef __DDLIB__MessageCenter__
#define __DDLIB__MessageCenter__

#include <iostream>
#include "cocos2d.h"
#include "MessageContrDelegate.h"
#include "ListenerArray.h"
#include "Message.h"
USING_NS_CC;

class MessageCenter
{
    cocos2d::Map<std::string,ListenerArray *> _dicArray;
private:
    static MessageCenter * _center;
public:
    static MessageCenter * getInstance();
    MessageCenter();
    ~MessageCenter();
public:
    void addEventListener(MessageContrDelegate *delegate ,const std::string msg_name);
    void removeListenerByDelegate(MessageContrDelegate *delegate);
    void removeListenerByMsg(MessageContrDelegate *delegate,const std::string msg_name);
    void removeAllListeners();
    // void postMessage(MessageContrDelegate *delegate,Message* message);
    void postMessage(Message* message);
};


#endif /* defined(__DDLIB__MessageCenter__) */
