//
//  Message.cpp
//  DDLIB
//
//  Created by wzh on 14-11-17.
//
//

#include "SocketMessage.h"

int SocketMessage::dataLength()
{
    return (int)this->_data.size();
}

SocketMessage * SocketMessage::create()
{
    SocketMessage * ret = new SocketMessage();
    if (ret) {
        return ret;
    }
    return nullptr;
}