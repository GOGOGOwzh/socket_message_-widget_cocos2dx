//
//  GameSceneManager.cpp
//  DDLIB
//
//  Created by wzh on 14-10-26.
//
//

#include "GameSceneManager.h"
#include "SourceManager.h"
#include "MsgTable.h"
GameSceneManager * GameSceneManager::_inst = nullptr;

GameSceneManager::GameSceneManager():_mainScene(nullptr),_mainLayer(nullptr)
{
    this->addListener();
    this->initScene();
}

GameSceneManager * GameSceneManager::getInstance()
{
    if (!_inst) {
        _inst = new GameSceneManager();
    }
    return _inst;
}

void GameSceneManager::initScene()
{
    SourceManager::getInstance()->addPlistToCache();
    this->setMainScene(Scene::create());
    this->setMainLayer(Layer::create());
    this->getMainScene()->addChild(this->getMainLayer());
    
 //   this->changeToClickStartLayer();
    this->changeToChoosePhLayer("2");
}

void GameSceneManager::addListener()
{
    MessageCenter::getInstance()->addEventListener(this, MsgTable::CHANGE_TO_CHOOSEPHOTO_LAYER);
    MessageCenter::getInstance()->addEventListener(this, MsgTable::CHANGE_TO_CLICKSTART_LAYER);
    MessageCenter::getInstance()->addEventListener(this, MsgTable::CHANGE_TO_SELSKILL_LAYER);
    MessageCenter::getInstance()->addEventListener(this, MsgTable::CHANGE_TO_GAMESTART_LAYER);
    MessageCenter::getInstance()->addEventListener(this, MsgTable::CHANGE_TO_SHOP_LAYER);

}

void GameSceneManager::changeToClickStartLayer()
{
    ClickStartLayerCtr * ctr  = new ClickStartLayerCtr();
    ctr->autorelease();
    
    this->getMainLayer()->addChild(ctr->getLayer());
}

void GameSceneManager::changeToChoosePhLayer(std::string path)
{
    ChoosePhotoLayerCtr * ctr = new ChoosePhotoLayerCtr();
    ctr->autorelease();
    
    this->getMainLayer()->addChild(ctr->createLayer(path));
}

void GameSceneManager::changeToShopLayer()
{
    ShopLayerCtr * ctr = new ShopLayerCtr();
    ctr->autorelease();
    
    this->getMainLayer()->addChild(ctr->getLayer());
}

void GameSceneManager::changeToGameStartLayer(std::string path)
{
    GameStartLayerCtr * ctr = new GameStartLayerCtr();
    ctr->autorelease();
    
    this->getMainLayer()->addChild(ctr->createLayer(path));
}

void GameSceneManager::changeToSelSkillLayer(std::string path)
{
    SelectSkillLayerCtr * ctr = new SelectSkillLayerCtr();
    ctr->autorelease();
    
    this->getMainLayer()->addChild(ctr->createLayer(path));
}

void GameSceneManager::dealRevMessageFromServer()
{
    
}

void GameSceneManager::getMessage(Message *message)
{
    if (message->getMessageName() == MsgTable::CHANGE_TO_CLICKSTART_LAYER) {
        this->changeToClickStartLayer();
    }
    if (message->getMessageName() == MsgTable::CHANGE_TO_CHOOSEPHOTO_LAYER) {
        this->changeToChoosePhLayer(message->getMessageBody());
    }
    if (message->getMessageName() == MsgTable::CHANGE_TO_SELSKILL_LAYER) {
        this->changeToSelSkillLayer(message->getMessageBody());
    }
    if (message->getMessageName() == MsgTable::CHANGE_TO_GAMESTART_LAYER) {
        this->changeToGameStartLayer(message->getMessageBody());
    }
    if (message->getMessageName() == MsgTable::CHANGE_TO_SHOP_LAYER) {
        this->changeToShopLayer();
    }
}
