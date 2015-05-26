//
//  ChoosePhotoLayer.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#include "ChoosePhotoLayer.h"
#include "MsgTable.h"
ChoosePhotoLayer::ChoosePhotoLayer(std::string path):_path(path)
{
}

ChoosePhotoLayer * ChoosePhotoLayer::createLayer(std::string path)
{
    ChoosePhotoLayer * layer = new ChoosePhotoLayer(path);
    {
        if (layer && layer->init()) {
            layer->autorelease();
            return layer;
        }
        CC_SAFE_DELETE(layer);
        return nullptr;
    }
}

bool ChoosePhotoLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->createUI();
    return true;
}

void ChoosePhotoLayer::createUI()
{
    this->randPath();
    
    auto bgSprite = Sprite::create(_path);
    bgSprite->setPosition(VisibleRect::center());
    this->addChild(bgSprite);
    
    auto selBg = Sprite::createWithSpriteFrameName("selectPhoto.png");
    selBg->setPosition(VisibleRect::center());
    this->addChild(selBg);
    
    auto beginBtn = DDButton::createFromFrame("beginGame.png","");
    beginBtn->setPosition(VisibleRect::center().x,VisibleRect::center().y-100);
    beginBtn->addCallBackListener(CC_CALLBACK_1(ChoosePhotoLayer::beginBtnCallback, this));
    this->addChild(beginBtn);
    
    auto shopBtn = DDButton::createFromFrame("shop.png","");
    shopBtn->setPosition(VisibleRect::center().x,VisibleRect::center().y-250);
    shopBtn->addCallBackListener(CC_CALLBACK_1(ChoosePhotoLayer::shopBtnCallback, this));
    this->addChild(shopBtn);
    
    auto backBtn = DDButton::createFromFrame("return.png","");
    backBtn->setPosition(VisibleRect::center().x,VisibleRect::center().y-400);
    backBtn->addCallBackListener(CC_CALLBACK_1(ChoosePhotoLayer::backBtnCallback, this));
    this->addChild(backBtn);
    
    auto firstBtn = DDButton::createFromFrame("avatar.png","");
    firstBtn->setPosition(VisibleRect::center().x-firstBtn->getContentSize().width - 50,VisibleRect::center().y + 160);
    firstBtn->addCallBackListener(CC_CALLBACK_1(ChoosePhotoLayer::chooseFirstPhBtnCallback, this));
    this->addChild(firstBtn);
    
    auto secBtn = DDButton::createFromFrame("avatar.png","");
    secBtn->setPosition(VisibleRect::center().x,VisibleRect::center().y + 160);
    secBtn->addCallBackListener(CC_CALLBACK_1(ChoosePhotoLayer::chooseSecBtnCallback, this));
    this->addChild(secBtn);
    
    auto thirdBtn = DDButton::createFromFrame("avatar.png","");
    thirdBtn->setPosition(VisibleRect::center().x+thirdBtn->getContentSize().width+50,VisibleRect::center().y + 160);
    thirdBtn->addCallBackListener(CC_CALLBACK_1(ChoosePhotoLayer::chooseThirdPhBtnCallback, this));
    this->addChild(thirdBtn);
    
    auto wordSp = Sprite::createWithSpriteFrameName("no_photo_tip.png");
    wordSp->setPosition(VisibleRect::center().x,secBtn->getPositionY() + thirdBtn->getContentSize().height/2+20);
    this->addChild(wordSp);
}

void ChoosePhotoLayer::randPath()
{
    CCLOG("path: %s",_path.c_str());
    if (_path == "") {
        int num = rand()%5;
        _path = StringUtils::format("%d.png",num);
    }
}

void ChoosePhotoLayer::endLayer()
{
    this->removeFromParent();
}

void ChoosePhotoLayer::beginBtnCallback(Ref * pSender)
{
    Message * msg = Message::create(MsgTable::CHANGE_TO_SELSKILL_LAYER,_path);
    MessageCenter::getInstance()->postMessage(msg);
    this->endLayer();
}

void ChoosePhotoLayer::shopBtnCallback(Ref * pSender)
{
    Message * msg = Message::create(MsgTable::CHANGE_TO_SHOP_LAYER);
    MessageCenter::getInstance()->postMessage(msg);
    
    this->endLayer();
}

void ChoosePhotoLayer::backBtnCallback(Ref * pSender)
{
    Message * msg = Message::create(MsgTable::CHANGE_TO_CLICKSTART_LAYER);
    MessageCenter::getInstance()->postMessage(msg);
    this->endLayer();
}

void ChoosePhotoLayer::chooseFirstPhBtnCallback(Ref * pSender)
{
    
}

void ChoosePhotoLayer::chooseSecBtnCallback(Ref * pSender)
{
    
}

void ChoosePhotoLayer::chooseThirdPhBtnCallback(Ref * pSender)
{
    
}