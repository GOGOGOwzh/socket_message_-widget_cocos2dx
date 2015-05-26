//
//  Message.h
//  DDLIB
//
//  Created by wzh on 14-11-17.
//
//

#ifndef __DDLIB__Message__
#define __DDLIB__Message__

#include <iostream>
#include "cocos2d.h"

class SocketMessage
{
public:
    
    static SocketMessage * create();
    
    CC_SYNTHESIZE(std::string,_data,Data);
    CC_SYNTHESIZE(int,_protocoltype,Protocoltype)
    int dataLength();
};

#endif /* defined(__DDLIB__Message__) */
