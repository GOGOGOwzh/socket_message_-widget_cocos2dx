//
//  GunBangSp.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/5/3.
//
//

#include "GunBangSp.h"

GunBangSp::GunBangSp(Vec2 & pos)
{
    this->initWithSpriteFrameName("effect.png");
//    this->setScale(0.8);
    this->setPosition(pos);
    this->createAnimate();
}

GunBangSp * GunBangSp::create(Vec2 & pos)
{
    auto sp = new GunBangSp(pos);
    if (sp) {
        sp->retain();
        return sp
        ;
    }
    CC_SAFE_DELETE(sp);
    return nullptr;
}

void GunBangSp::createAnimate()
{
    auto sp = Sprite::createWithSpriteFrameName("ana.png");
    sp->setAnchorPoint(Vec2(0, 0));
    this->addChild(sp);
    
    auto delay  = DelayTime::create(1);
    auto seq = Sequence::create(delay, CallFunc::create(CC_CALLBACK_0(GunBangSp::cleanUpSelf, this)),NULL);
    this->runAction(seq);
}

void GunBangSp::cleanUpSelf()
{
    CCLOG("cleanup gunbangsp");
    this->removeFromParent();
}