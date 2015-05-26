//
//  DDButton.h
//  DDLIB
//
//  Created by wzh on 15/3/2.
//
//

#ifndef __DDLIB__DDButton__
#define __DDLIB__DDButton__

#include "cocos2d.h"
USING_NS_CC;

#define ACCEPTABLEDIS 10

class DDButton: public Sprite
{
private:
    float _moveBeginPosY;
    
    CC_SYNTHESIZE(std::string, normalname, Normalname)
    CC_SYNTHESIZE(std::string, selname, Selname)
    CC_SYNTHESIZE(ccMenuCallback, callback, Callback)
    CC_SYNTHESIZE(bool, _enable, TouchEnable)
    CC_SYNTHESIZE(bool, _swallow, Swallow)
    CC_SYNTHESIZE(bool, _enableScroll, EnableScroll) //是否启用scrollview模式，false不启用，true启用
public:
    DDButton(std::string,std::string,bool);
    ~DDButton();
    
    static DDButton * createFromFile(std::string,std::string sel= "");
    static DDButton * createFromFrame(std::string,std::string sel ="");
public:
    bool init();
    void onEnter() override;
    void onExit() override;
public:
    bool onTouchBegan(Touch* ,Event *);
    void onTouchMoved(Touch* ,Event *);
    void onTouchEnded(Touch* ,Event *);
public:
    void addCallBackListener(const ccMenuCallback&);
    void setSwallowEnable(bool able);
private:
    bool flagMode;  //有两种模式：false代表从文件中获取，true代表从plist中
    EventListenerTouchOneByOne * _lis;
};

#endif /* defined(__DDLIB__DDButton__) */
