//
//  Message.h
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//  _msgKind 有2中类型 ：
//  1、数字  2、 string

#ifndef __DDLIB__Message__
#define __DDLIB__Message__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class Message:public Ref
{
    CC_SYNTHESIZE(std::string,_msg,MessageName)
    CC_SYNTHESIZE(int,_msgKind,MessageKind)
    CC_SYNTHESIZE(std::string,_msgBody,MessageBody)
public:
    enum MessageKind{
        NUMBER = 1,
        STRING
    };
    static Message * create();
    static Message * create(std::string name,std::string body = "",int kind = 1);
public:
    Message();
    ~Message();
};


#endif /* defined(__DDLIB__Message__) */
