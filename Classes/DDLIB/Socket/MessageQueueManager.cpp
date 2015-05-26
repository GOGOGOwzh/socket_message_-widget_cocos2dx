//
//  MessageQueueManager.cpp
//  DDLIB
//
//  Created by wzh on 14-11-18.
//
//

#include "MessageQueueManager.h"

MessageQueueManager * MessageQueueManager::_inst = nullptr;

MessageQueueManager::MessageQueueManager():sendQueue(nullptr),revQueue(nullptr),hasInit(false)
{

}

MessageQueueManager::~MessageQueueManager()
{
    delete sendQueue;
    delete revQueue;
}

void MessageQueueManager::init()
{
    if (hasInit == false) {
        sendQueue = MessageQueue::create();
        revQueue = MessageQueue::create();
        hasInit = true;
        CCLOG("SEND QUEUE AND REV QUEUE HAS CREATED!");
    }
    else{
        CCLOG("SEND ADN REV QUEUE HAS CREATE ! \n");
    }

}

MessageQueueManager * MessageQueueManager::getInstance()
{
    if (_inst == nullptr) {
        _inst = new MessageQueueManager();
    }
    return _inst;
}

void MessageQueueManager::sendMsgToSendQueue(SocketMessage *msg)
{
    sendQueue->sendToQueue(msg);
}

void MessageQueueManager::sendMsgToRevQueue(SocketMessage *msg)
{
    revQueue->sendToQueue(msg);
}

MessageQueue * MessageQueueManager::getSendQueue()
{
    return this->sendQueue;
}

MessageQueue * MessageQueueManager::getRevQueue()
{
    return this->revQueue;
}
