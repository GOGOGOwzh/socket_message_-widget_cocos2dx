//
//  SourceManager.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#ifndef __PressBug_0_1__SourceManager__
#define __PressBug_0_1__SourceManager__

#include <stdio.h>
#include "cocos2d.h"
using namespace std;

class SourceManager
{
private:
    int _score;
    int _hisScore;
    float _goldCount;
    vector<int> _skillList;
    vector<int> _skillPrice;
private:
    static SourceManager * _inst;
    SourceManager();
private:
    vector<std::string> _plistPath;
    void init();
public:
    static SourceManager * getInstance();
public:
    void addPlist();
    void addPlistToCache();
    vector<std::string> getPlistPath();
public:
    void setHisScoreInfo(int score);
    int getHisScoreInfo();
    
    void setScore(int score);
    int getScore();
    
    void setGoldInfo(int goldcount);
    int getGoldInfo();
    
    void setSkillInfo(int skillId);
    vector<int> &getSkillInfo();
    vector<int> &getSkillPriceInfo();
    
    void cleanupScore();
};
#endif /* defined(__PressBug_0_1__SourceManager__) */
