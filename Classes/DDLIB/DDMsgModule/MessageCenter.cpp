//
//  MessageCenter.cpp
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//

#include "MessageCenter.h"

MessageCenter * MessageCenter::_center = nullptr;

MessageCenter * MessageCenter::getInstance()
{
    if (!_center) {
        _center = new MessageCenter();
    }
    return _center;
}

MessageCenter::MessageCenter()
{
    _dicArray.clear();
}

MessageCenter::~MessageCenter()
{
    _dicArray.clear();
}

void MessageCenter::addEventListener(MessageContrDelegate * delegate, const std::string msg_id)
{
    if (delegate == NULL) {
        CCLOG("MessageContrDelegate CAN NOT BE NULL");
        return;
    }
    
    
    ListenerArray * _listenerArray = (ListenerArray *)_dicArray.at(msg_id);
    if (_listenerArray == nullptr) {
        _listenerArray = ListenerArray::create();
        _dicArray.insert(msg_id, _listenerArray);
    }
    
    for (int i = 0 ;i <_listenerArray->size();i++) {
        MessageContrDelegate * exist_list = _listenerArray->at(i);
        if (exist_list) {
            CCLOG("ONE MESSAGE CAN REGIST BY ONE CLASS , ONLY ONCE !");
            return;
        }
    }
    _listenerArray->pushBack(delegate);
}

void MessageCenter::postMessage(Message* message)
{
    if (message == nullptr) {
        CCLOG("MESSAGE CAN NOT BE NULL !");
        return;
    }
    
    ListenerArray * _listenrArray = (ListenerArray *)_dicArray.at(message->getMessageName());
    if (_listenrArray) {
        for (int i=0; i<_listenrArray->size(); i++) {
            MessageContrDelegate * delegate = _listenrArray->at(i);
            if (delegate) {
                delegate->getMessage(message);
            }
            else{
                CCLOG("LISTENER ARRAY MAYBE HAS SOMETHING WRONG");
            }
        }
    }
    else{
        CCLOG("MESSAGE LISTENER FOR %s IS NOT EXSITED !",message->getMessageName().c_str());
        return;
    }
}


void MessageCenter::removeListenerByMsg(MessageContrDelegate *delegate, const std::string msg_id)
{
    if (delegate == nullptr or msg_id == "") {
        CCLOG("YOU MUST GIVE DELEGATE OR MEG_ID TO REMVOE !");
        return;
    }
    ListenerArray * _listenrArray = (ListenerArray *)_dicArray.at(msg_id);
    if (_listenrArray->contains(delegate)) {
        _listenrArray->eraseObject(delegate);
    }
    else
    {
        CCLOG("LISTENER ARRAY DO NOT CONTAINS THIS DELEGATE !");
        return;
    }
    
}

void MessageCenter::removeListenerByDelegate(MessageContrDelegate *delegate)
{
    if (delegate == nullptr) {
        CCLOG("YOU MUST GIVE DELEGATE TO REMVOE !");
        return;
    }
    auto _allKeys =  _dicArray.keys();
    
    for (int i=0;i<_allKeys.size();i++) {
        std::string _listkey = _allKeys.at(i);
        ListenerArray * _listenerArray = _dicArray.at(_listkey);
        if (_listenerArray and _listenerArray->contains(delegate)) {
            _listenerArray->eraseObject(delegate);
        }
        else{
            CCLOG("MAYBE LISTENER ARRAY HAS BEEN DISAPPEARED !");
        }
    }
}

void MessageCenter::removeAllListeners()
{
    _dicArray.clear();
}