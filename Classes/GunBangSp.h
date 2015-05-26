//
//  GunBangSp.h
//  PressBug_0.1
//
//  Created by wzh on 15/5/3.
//
//

#ifndef __PressBug_0_1__GunBangSp__
#define __PressBug_0_1__GunBangSp__

#include "cocos2d.h"
USING_NS_CC;

class GunBangSp : public Sprite
{
public:
    GunBangSp(Vec2 & pos);
public:
    static GunBangSp * create(Vec2  & pos);
public:
    void createAnimate();
    void cleanUpSelf();
};

#endif /* defined(__PressBug_0_1__GunBangSp__) */
