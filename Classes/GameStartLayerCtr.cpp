//
//  GameStartLayerCtr.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#include "GameStartLayerCtr.h"

GameStartLayer * GameStartLayerCtr::_layer = nullptr;

GameStartLayerCtr::GameStartLayerCtr()
{
    this->registeMsg();
}

void GameStartLayerCtr::registeMsg()
{
    MessageCenter::getInstance()->addEventListener(this, MsgTable::SKILL_ICE);
    MessageCenter::getInstance()->addEventListener(this, MsgTable::SKILL_GUN);
    MessageCenter::getInstance()->addEventListener(this, MsgTable::SKILL_HOLE);
    MessageCenter::getInstance()->addEventListener(this, MsgTable::SKILL_LASER);
    MessageCenter::getInstance()->addEventListener(this, MsgTable::SKILL_MORE);
    
    MessageCenter::getInstance()->addEventListener(this, MsgTable::SCORE_CHANGE);
}

void GameStartLayerCtr::getMessage(Message * msg)
{
    if (msg->getMessageName() == MsgTable::SKILL_ICE) {
        _layer->skillCallback(SkillType::skill_ice);
    }
    if (msg->getMessageName() == MsgTable::SKILL_GUN) {
        _layer->skillCallback(SkillType::skill_gun);
    }
    if (msg->getMessageName() == MsgTable::SKILL_HOLE) {
        _layer->skillCallback(SkillType::skill_hole);
    }
    if (msg->getMessageName() == MsgTable::SKILL_LASER) {
        _layer->skillCallback(SkillType::skill_laser);
    }
    if (msg->getMessageName() == MsgTable::SKILL_MORE) {
        _layer->skillCallback(SkillType::skill_more);
    }
    if (msg->getMessageName() == MsgTable::SCORE_CHANGE) {
        _layer->changeScore(msg->getMessageBody());
    }
    
}

GameStartLayer * GameStartLayerCtr::createLayer(std::string path)
{
    _layer = GameStartLayer::createLayer(path);
    return _layer;
}