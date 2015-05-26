//
//  MessageQueueManager.h
//  DDLIB
//
//  Created by wzh on 14-11-18.
//
//

#ifndef __DDLIB__MessageQueueManager__
#define __DDLIB__MessageQueueManager__

#include <iostream>
#include "SocketMessage.h"
#include "MessageQueue.h"

class MessageQueueManager
{
private:
    
    bool hasInit;  // 加个锁以防队列被更改
    
    MessageQueue * sendQueue;
    MessageQueue * revQueue;
    static MessageQueueManager * _inst;
public:
    MessageQueueManager();
    ~MessageQueueManager();
    static MessageQueueManager * getInstance();
public:
    
    void init();
    void sendMsgToSendQueue(SocketMessage*);
    void sendMsgToRevQueue(SocketMessage*);

    MessageQueue * getSendQueue();
    MessageQueue * getRevQueue();
};

#endif /* defined(__DDLIB__MessageQueueManager__) */
