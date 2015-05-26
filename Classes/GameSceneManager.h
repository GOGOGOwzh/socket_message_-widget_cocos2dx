//
//  GameSceneManager.h
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//

#ifndef __DDLIB__GameSceneManager__
#define __DDLIB__GameSceneManager__

#include "DDLIB/Share/IncludeFile.h"
#include "ClickStartLayerCtr.h"
#include "ChoosePhotoLayerCtr.h"
#include "SelectSkillLayerCtr.h"
#include "GameStartLayerCtr.h"
#include "ShopLayerCtr.h"

USING_NS_CC;

class GameSceneManager : public MessageContrDelegate
{
    CC_SYNTHESIZE_RETAIN(Scene *, _mainScene, MainScene)
    CC_SYNTHESIZE_RETAIN(Layer *, _mainLayer, MainLayer)
private:
    static GameSceneManager * _inst;
public:
    static GameSceneManager * getInstance();
    GameSceneManager();

public:
    void initScene();
    void addListener();
    void dealRevMessageFromServer();   //这里只是作为中转站，将收到的信息解析，然后依据协议号将信息分发
    void getMessage(Message * message) override;
public:
    void changeToSelSkillLayer(std::string);
    void changeToGameStartLayer(std::string);
    void changeToShopLayer();
    void changeToClickStartLayer();
    void changeToChoosePhLayer(std::string);

};


#endif /* defined(__DDLIB__GameSceneManager__) */
