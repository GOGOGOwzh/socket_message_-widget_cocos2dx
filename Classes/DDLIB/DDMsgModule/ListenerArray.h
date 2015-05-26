//
//  ListenerArray.h
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//

#ifndef __DDLIB__ListenerArray__
#define __DDLIB__ListenerArray__

#include <iostream>
#include "cocos2d.h"
#include "MessageContrDelegate.h"

class ListenerArray :public Ref
{
private:
    cocos2d::Vector<MessageContrDelegate *> _array;
public:
    static ListenerArray * create();
    ListenerArray(){
        _array.clear();
    }
public:
    void pushBack(MessageContrDelegate *);
    void clear();
    void eraseObject(MessageContrDelegate *,bool removeAll = false);
    
    bool contains(MessageContrDelegate *);
    bool empty();
    
    ssize_t size();
    MessageContrDelegate * at(ssize_t index);
    
};


#endif /* defined(__DDLIB__ListenerArray__) */
