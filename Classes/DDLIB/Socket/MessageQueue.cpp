//
//  MessageQueue.cpp
//  DDLIB
//
//  Created by wzh on 14-11-18.
//
//

#include "MessageQueue.h"

MessageQueue * MessageQueue::create()
{
    MessageQueue * ret = new MessageQueue();
    if (ret && ret->init()) {
        return ret;
    }
    return nullptr;
}

bool MessageQueue::init()
{
    return msgQeue.size() == 0;
}

void MessageQueue::sendToQueue(SocketMessage* msg)
{
   // std::lock_guard<std::mutex> lck(queueLock);
    msgQeue.push(msg);
}

SocketMessage * MessageQueue::frontQueue()
{
   // std::lock_guard<std::mutex> lck(queueLock);
    return msgQeue.front();
}

SocketMessage * MessageQueue::frontAndPopQueue()
{
   // std::lock_guard<std::mutex> lck(queueLock);
    SocketMessage * ret = msgQeue.front();
    msgQeue.pop();
    return ret;
}

int MessageQueue::getQueueSize()
{
    return (int)msgQeue.size();
}

void MessageQueue::popQueue()
{
   // std::lock_guard<std::mutex> lck(queueLock);
    msgQeue.pop();
}

void MessageQueue::queueLck()
{
    queueLock.lock();
}

void MessageQueue::queueUnlck()
{
    queueLock.unlock();
}
