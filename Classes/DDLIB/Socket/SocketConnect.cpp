//
//  SocketConnect.cpp
//  DDLIB
//
//  Created by wzh on 14-11-17.
//
//

#include "SocketConnect.h"
SocketConnect::SocketConnect(std::string ip , int port):sendThread(nullptr),revThread(nullptr)
{
    this->port = port;
    this->ip = ip;
}

SocketConnect::~SocketConnect()
{
    this->shutDownSocket();
    delete sendThread;
    delete revThread;
}

SocketConnect * SocketConnect::create(std::string ip , int port)
{
    SocketConnect * ret = new SocketConnect(ip,port);
    if (ret) {
        return ret;
    }
    return nullptr;
}

bool SocketConnect::init()
{
    //初始化socket库，win32需要，其他不需要
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        return false;
    }
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
    {
        return false;
    }
    
    return true;
#endif
   return true;
}

bool SocketConnect::socketConnected()
{
    socketSet = socket(AF_INET, SOCK_STREAM, 0);
    
	struct sockaddr_in s_add;
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = inet_addr(this->ip.c_str()); //将十进制的ip地址转换为unsigned long 的整数 192.168.1.122  8992  192.168.1.126
	s_add.sin_port = htons(this->port);//端口号   115.28.220.130
    
	if (-1 == connect(socketSet, (struct sockaddr*)&s_add, sizeof(struct sockaddr_in)))
	{
		CCLOG("connect fail !!");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		closesocket(socketSet);
		WSACleanup();
		return false;
#else
		close(socketSet);
        return false;
#endif
    }
	else
	{
		CCLOG("connect successful !");
        
        MessageQueueManager::getInstance()->init();
        
		return true;
	}
}

void SocketConnect::socketStart()
{
    if (this->init()) {
        if (this->socketConnected())
        {
            sendThread = new std::thread(&SocketConnect::sendMessage,this);
            
            revThread = new std::thread(&SocketConnect::revMessage,this);
        }
        else
        {
            CCLOG("CONNECT FAILUE !\n");
        }
    }
    else
    {
        CCLOG("SOCKET INITIAL FAILUE!\n");
    }
}

void SocketConnect::sendMessage()
{
    CCLOG("SEND THREAD HAS BEGAN !\n");
    SOCKET socket = this->socketSet;
    MessageQueue * queue = MessageQueueManager::getInstance()->getSendQueue();
    while (true)
    {
        if (queue->getQueueSize() > 0)
        {
            CCLOG("SENDQUEUE SIZE IS %d\n",queue->getQueueSize());
            
            queue->queueLck();
            SocketMessage *  msg = queue->frontQueue();
            queue->queueUnlck();
            
            CCLOG("SEND TO SERVER FROM SENDQUEUE : %s, DATA LENGTHT : %d\n",msg->getData().c_str(),msg->dataLength());
        
            if (-1 == send(socket, msg->getData().c_str(), msg->dataLength(), 0)) {
                CCLOG("SEND TO SERVER ERROR ! WILL BE TRY TO SEND AGAGIN !\n");
            }
            else{
                CCLOG("SEND TO SERVER SUCCESS !\n");
                
                queue->queueLck();
                queue->popQueue();
                queue->queueUnlck();
                delete msg;
            }
        }
        else{
           // CCLOG("QUEUE IS EMPTY !");
        }
    }
}

void SocketConnect::revMessage()
{
    CCLOG("RECEIVE THREAD HAS BEGAN !\n");
    
    SOCKET socket = this->socketSet;
    
    char buf[1024] = "";
    
    while (true) {
        if (-1 == recv(socket, buf, sizeof(buf), 0)) {
            CCLOG("RECEIVE ERROR !\n");
        }
        else{
            
            MessageQueue * queue = MessageQueueManager::getInstance()->getRevQueue();
            
            SocketMessage * msg = SocketMessage::create();
            msg->setData(buf);
            
            CCLOG("CLIENT HAS RECEIVE : %s",msg->getData().c_str());
            
            if (msg->dataLength() > 0) {
                
                queue->queueLck();
                MessageQueueManager::getInstance()->sendMsgToRevQueue(msg);
                queue->queueUnlck();
                
                memset(buf, 0, 1024);
            }else{
                CCLOG("MAYBE SOMETHING WRONG !\n");
            }
        }
    }
}

void SocketConnect::shutDownSocket()
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	closesocket(socketSet);
	WSACleanup();
#else
	close(socketSet);
#endif
//	pthread_exit((void*)"the thread exit"); ///暂时先这么用，找到方法再换掉
    
    delete sendThread;  ///不知道这样可不可以
    delete revThread;
	return;
}
