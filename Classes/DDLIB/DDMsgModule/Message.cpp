//
//  Message.cpp
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//

#include "Message.h"

Message * Message::create()
{
    Message * ret = new Message();
    if (ret) {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}

Message * Message::create(std::string name,std::string body,int kind)
{
    Message * ret = new Message();
    if (ret) {
        ret->autorelease();
        
        ret->setMessageName(name);
        ret->setMessageBody(body);
        ret->setMessageKind(kind);
        
        return ret;
    }
    return nullptr;
}

Message::Message():_msg(""),_msgBody("")
{
    _msgKind = 1;
}

Message::~Message()
{
    _msg = "";
    _msgBody = "";
    _msgKind = 1;
}
