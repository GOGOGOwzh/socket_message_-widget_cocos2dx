//
//  SocketManager.cpp
//  DDLIB
//
//  Created by wzh on 14-11-17.
//
//

#include "SocketManager.h"

SocketManager * SocketManager::_inst = nullptr;

SocketManager::SocketManager()
{
    
}

SocketManager * SocketManager::getInstance()
{
    if (_inst == nullptr) {
        _inst = new SocketManager();
    }
    return _inst;
}

SocketConnect * SocketManager::createSocket(std::string name, std::string ip, int port)
{
    SocketConnect * socket = SocketConnect::create(ip, port);
    socket->socketStart();
    
    socketMap.insert(std::pair<std::string,SocketConnect *>(name, socket));
    
    return socket;
}

SocketConnect * SocketManager::getSocketByName(std::string name)
{
    if(socketMap.at(name))
    {
        return socketMap.at(name);
    }
    else
    {
        return nullptr;
    }
}

void SocketManager::closeAllSocket()
{
    for (std::map<std::string,SocketConnect *>::iterator it = socketMap.begin();it!=socketMap.end(); it++) {
        (*it).second->shutDownSocket();
    }
    socketMap.clear();
}


void SocketManager::closeSocketByName(std::string name)
{
    if (socketMap.at(name)) {
        socketMap.at(name)->shutDownSocket();
        socketMap.erase(name);
        CCLOG("SOCKET %s CLOSED !\n",name.c_str());
    }
    else
    {
        CCLOG("SOCKET %s NOT FOUND !\n",name.c_str());
    }
}

