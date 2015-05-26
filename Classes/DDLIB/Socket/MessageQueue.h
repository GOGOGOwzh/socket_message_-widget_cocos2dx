//
//  MessageQueue.h
//  DDLIB
//
//  Created by wzh on 14-11-18.
//
//

#ifndef __DDLIB__MessageQueue__
#define __DDLIB__MessageQueue__

#include <iostream>
#include <queue>
#include <mutex>
#include "SocketMessage.h"

class MessageQueue
{
private:
    std::mutex queueLock;
    std::queue<SocketMessage*> msgQeue;
public:
    static MessageQueue * create();
public:
    
    bool init();
    
    void sendToQueue(SocketMessage*);
    void popQueue();
    
    void queueLck();
    void queueUnlck();
    
    int getQueueSize();
    
    SocketMessage * frontQueue();
    SocketMessage * frontAndPopQueue();  //这个应该不能这么用了，先暂时禁用
   
};
#endif /* defined(__DDLIB__MessageQueue__) */
