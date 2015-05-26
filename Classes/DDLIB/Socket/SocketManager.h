//
//  SocketManager.h
//  DDLIB
//
//
//  因为不保证客户端只有一个socket，所以SocketManager可以建立多个socket，用名字来区分
//  讲socket存在一个map里面
//  Forexample :  createSocket("LogIn","192.168.1.101",8080)  createSocket("Battle","192.168.1.102",8081)
//
//  Created by wzh on 14-11-17.
//
//

#ifndef __DDLIB__SocketManager__
#define __DDLIB__SocketManager__

#include <iostream>
#include "cocos2d.h"
#include "SocketConnect.h"

USING_NS_CC;

class SocketManager
{
private:
    static SocketManager * _inst;
    
    std::map<std::string, SocketConnect *> socketMap;
    
public:
    SocketManager();
    static SocketManager * getInstance();
public:
    
    SocketConnect * createSocket(std::string name,std::string ip ,int port);
    SocketConnect * getSocketByName(std::string name);
    
    void closeSocketByName(std::string name);
    void closeAllSocket();
    
};
#endif /* defined(__DDLIB__SocketManager__) */
