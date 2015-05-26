//
//  SocketConnect.h
//  DDLIB
//
//  Created by wzh on 14-11-17.
//
//

#ifndef __DDLIB__SocketConnect__
#define __DDLIB__SocketConnect__

#pragma once
#include "cocos2d.h"
#include <thread>
#pragma comment(lib,"ws2_32.lib")

USING_NS_CC;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 ||  CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

#include <WinSock2.h>

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>

#endif

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <thread>

#include "SocketMessage.h"
#include "cocos2d.h"
#include "MessageQueueManager.h"

typedef unsigned int SOCKET;


class SocketConnect
{
private:
    SOCKET socketSet;
    int port;
    std::string ip;
    std::thread * sendThread;
    std::thread * revThread;
public:
    static SocketConnect * create(std::string,int);
    SocketConnect(std::string,int);
    ~SocketConnect();
public:
    bool init();
    bool socketConnected();
    void socketStart();
    void shutDownSocket();
    void sendMessage();
    void revMessage();
};


#endif

 /* defined(__DDLIB__SocketConnect__) */
