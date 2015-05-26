//
//  SkillLayer.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/12.
//
//

#ifndef __PressBug_0_1__SkillLayer__
#define __PressBug_0_1__SkillLayer__

#include "cocos2d.h"
#include "SkillButton.h"
#include "DDLIB/Share/VisibleRect.h"
USING_NS_CC;

class SkillLayer:public Layer
{
private:
    std::vector<int> _skillArry;
    EventListener * _listener;
    Vector<SpriteFrame*>  _laserTouchArray;
    Vector<SpriteFrame*>  _laserLineArray;
    Sprite * _touchSp;
    Sprite * _lineSp;
    Sprite * _laserSkilBg;
public:
    SkillLayer(std::vector<int> );
    static SkillLayer * create(std::vector<int> );
public:
    bool init() override;
    void onEnter() override;
public:
    bool onTouchBegan(Touch*,Event *);
    void onTouchMove(Touch*,Event *);
    void onTouchEnd(Touch*,Event *);
public:
    void createTouchEvent();
    void removeTouchEvent(float);
    void createUI();
    void createCacheAin();
    void createSkill();
    void destorySkill();
    Vec2 getLaserSkillPos();
    Sprite * getLaserSkill();
};

#endif /* defined(__PressBug_0_1__SkillLayer__) */
