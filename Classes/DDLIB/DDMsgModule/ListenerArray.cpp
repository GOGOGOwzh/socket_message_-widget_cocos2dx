//
//  ListenerArray.cpp
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
// 对cocos2d::vector 的封装 ，让其继承与Ref

#include "ListenerArray.h"

ListenerArray * ListenerArray::create()
{
    ListenerArray * ret = new ListenerArray();
    if (ret) {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}

void ListenerArray::pushBack(MessageContrDelegate * delegate)
{
    _array.pushBack(delegate);
}

void ListenerArray::clear()
{
    _array.clear();
}

void ListenerArray::eraseObject(MessageContrDelegate *delegate,bool removeAll)
{
    _array.eraseObject(delegate,removeAll);
}

bool ListenerArray::empty()
{
    return _array.empty();
}

bool ListenerArray::contains(MessageContrDelegate * delegate)
{
    return _array.contains(delegate);
}

ssize_t ListenerArray::size()
{
    return _array.size();
}

MessageContrDelegate * ListenerArray::at(ssize_t index)
{
    return _array.at(index);
}

