//
//  SelectSkillLayer.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#include "SelectSkillLayer.h"
#include "MsgTable.h"

SelectSkillLayer::SelectSkillLayer(std::string path):_path(path),_showListCount(0)
{
    
}

SelectSkillLayer * SelectSkillLayer::createLayer(std::string path)
{
    SelectSkillLayer * layer = new SelectSkillLayer(path);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool SelectSkillLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->createUI();
    return true;
}

void SelectSkillLayer::createUI()
{
    auto bgSprite = Sprite::create(_path);
    bgSprite->setPosition(VisibleRect::center());
    this->addChild(bgSprite);
    
    auto curSleSp = Sprite::createWithSpriteFrameName("selected.png");
    curSleSp->setPosition(VisibleRect::center().x,VisibleRect::center().y + curSleSp->getContentSize().height);
    this->addChild(curSleSp);
    
    auto selTipSp = Sprite::createWithSpriteFrameName("select_tip.png");
    selTipSp->setPosition(VisibleRect::center().x,VisibleRect::center().y+30);
    this->addChild(selTipSp);
    
    auto sureBtn = DDButton::createFromFrame("sure.png");
    sureBtn->setPosition(VisibleRect::center().x,VisibleRect::height()/10);
    sureBtn->addCallBackListener(CC_CALLBACK_1(SelectSkillLayer::sureBtnCallback, this));
    this->addChild(sureBtn);
    
    this->createSkillIconPos();
    
}

void SelectSkillLayer::createSkillIconPos()
{
    auto skilllist = SourceManager::getInstance()->getSkillInfo();
    
    if (skilllist.size() == 0) {
        return;
    }
    
    int k = 0;
    if (skilllist.size() > 0) {
        for (int i = 0; i<skilllist.size() ; i++) {
            int skillID = skilllist.at(i);
            DDButton * skillIcon = DDButton::createFromFrame(cocos2d::StringUtils::format("skill_%d.png",skillID).c_str());
            skillIcon->setTag(i);
            skillIcon->setPosition((k %3 +1) *(skillIcon->getContentSize().width + 20),VisibleRect::center().y - skillIcon->getContentSize().height/2 - 30 - (floor((i + 1)/4))*skillIcon->getContentSize().height*1.2);
            skillIcon->addCallBackListener(CC_CALLBACK_1(SelectSkillLayer::skillIconCallback, this));
            this->addChild(skillIcon);
            
            k++;
            if (k == 3) {
                k = 0;
            }
        }
    }
}

void SelectSkillLayer::endLayer()
{
    this->removeFromParent();
}

void SelectSkillLayer::skillIconCallback(cocos2d::Ref * pSender)
{
    int i = ((DDButton*)pSender)->getTag();
    DDButton * skillIcon = (DDButton*)this->getChildByTag(i);
    float beforePosY = VisibleRect::center().y - skillIcon->getContentSize().height/2 - 30 - (floor((i + 1)/4))*skillIcon->getContentSize().height*1.2;
    float nowPosy = skillIcon->getPositionY();
    if (nowPosy == beforePosY) {
        if (_showListCount <= 2) {
            float posY = VisibleRect::center().y + skillIcon->getContentSize().height * 1.5;
            float posX = (_showListCount + 1) * (skillIcon->getContentSize().width + 20);
            skillIcon->setPosition(posX, posY);
            SkillManager::getInstance()->getSelectedSkill().push_back(i);
            _showListCount++;
        }
    }
    else
    {
        float posY = VisibleRect::center().y - skillIcon->getContentSize().height/2 - 30 - (floor((i + 1)/4))*skillIcon->getContentSize().height*1.2;
        if (i >= 3) {
            i = i -3;
        }
        float posX = (i %3 +1) *(skillIcon->getContentSize().width + 20);
        skillIcon->setPosition(posX, posY);

        for (std::vector<int>::iterator it = SkillManager::getInstance()->getSelectedSkill().begin(); it != SkillManager::getInstance()->getSelectedSkill().end();) {
            if (*it == i) {
                SkillManager::getInstance()->getSelectedSkill().erase(it);
                break;
            }
            else
            {
                it++;
            }
        }
        _showListCount--;
      
    }
}
void SelectSkillLayer::sureBtnCallback(Ref * pSender)
{
    Message * msg = Message::create(MsgTable::CHANGE_TO_GAMESTART_LAYER,_path);
    MessageCenter::getInstance()->postMessage(msg);
    this->endLayer();
}