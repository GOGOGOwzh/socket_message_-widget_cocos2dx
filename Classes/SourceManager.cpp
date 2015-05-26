//
//  SourceManager.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#include "SourceManager.h"

SourceManager * SourceManager::_inst = nullptr;

SourceManager::SourceManager():_score(0),_goldCount(0),_hisScore(0)
{
    _skillList.clear();
    _skillPrice.clear();
}

SourceManager * SourceManager::getInstance()
{
    if (_inst == nullptr) {
        _inst = new SourceManager();
        _inst->init();
        _inst->addPlist();
    }
    return _inst;
}

void SourceManager::init()
{
    bool exist = cocos2d::UserDefault::getInstance()->getBoolForKey("Existed");
    if (exist) {
        _hisScore = cocos2d::UserDefault::getInstance()->getIntegerForKey("score");
        _goldCount = cocos2d::UserDefault::getInstance()->getIntegerForKey("goldcount");
        for (int i = 0; i<6; i++) {
            bool skill = cocos2d::UserDefault::getInstance()->getBoolForKey(cocos2d::StringUtils::format("skill_%d",i).c_str());
            if (skill) {
                _skillList.push_back(i);
            }
        }
    }
    else{
        _score = 0;
        _goldCount = 0;
        _skillList.clear();
        cocos2d::UserDefault::getInstance()->setBoolForKey("Existed", true);
        cocos2d::UserDefault::getInstance()->setIntegerForKey("score", _score);
        cocos2d::UserDefault::getInstance()->setIntegerForKey("goldcount", _goldCount);
        
    }
    
    _skillPrice.push_back(100);
    _skillPrice.push_back(200);
    _skillPrice.push_back(150);
    _skillPrice.push_back(200);
    _skillPrice.push_back(300);
    _skillPrice.push_back(400);
    
}

void SourceManager::addPlist()
{
    _plistPath.push_back("alertandcombo.plist");
    _plistPath.push_back("background.plist");
    _plistPath.push_back("choosephoto.plist");
    _plistPath.push_back("chooseskill.plist");
    _plistPath.push_back("faceworm.plist");
    _plistPath.push_back("gamescene.plist");
    _plistPath.push_back("normalworm.plist");
    _plistPath.push_back("setting.plist");
    _plistPath.push_back("shop.plist");
    _plistPath.push_back("title.plist");
    _plistPath.push_back("bomb_effect.plist");
    _plistPath.push_back("skills.plist");
}

vector<std::string> SourceManager::getPlistPath()
{
    return _plistPath;
}

void SourceManager::addPlistToCache()
{
    for (int i = 0; i<_plistPath.size(); i++) {
        std::string path = _plistPath.at(i);
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path);
    }
}

void SourceManager::setHisScoreInfo(int score)
{
    _hisScore = score;
    cocos2d::UserDefault::getInstance()->setIntegerForKey("score", _score);
}

int SourceManager::getHisScoreInfo()
{
    return _hisScore;
}

void SourceManager::setScore(int score)
{
    _score += score;
}

int SourceManager::getScore()
{
    return _score;
}

void SourceManager::setGoldInfo(int goldcount)
{
    _goldCount += goldcount;
    cocos2d::UserDefault::getInstance()->setIntegerForKey("goldcount", _goldCount);
}

int SourceManager::getGoldInfo()
{
    return _goldCount;
}

void SourceManager::setSkillInfo(int skillId)
{
    _skillList.push_back(skillId);
    cocos2d::UserDefault::getInstance()->setBoolForKey(cocos2d::StringUtils::format("skill_%d",skillId).c_str() , true);
}

vector<int> & SourceManager::getSkillInfo()
{
//    _skillList.push_back(1);
//    _skillList.push_back(2);
    return _skillList;
}

vector<int> & SourceManager::getSkillPriceInfo()
{
    return _skillPrice;
}


void SourceManager::cleanupScore()
{
    _score = 0;
}




