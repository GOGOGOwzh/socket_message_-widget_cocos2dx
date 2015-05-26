//
//  GameStartLayer.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#ifndef __PressBug_0_1__GameStartLayer__
#define __PressBug_0_1__GameStartLayer__

#include "DDLIB/Share/IncludeFile.h"
#include "MsgTable.h"
#include "BugManager.h"
#include "SkillLayer.h"
#include "SkillManager.h"
#include "GunBangSp.h"

class GameStartLayer:public Layer
{
private:
    std::string _path;
    std::string _evaluatePath;
    int _bulletCount;
    int _score;
    int _level;
    int _target;
    bool _touchEnable;
    bool _pause;
    
    Vector<Bug*> _norBugList;
    Vector<Bug*> _spBugList;
    
    Sprite * _bgSprite;
    Sprite * _holeSkill;
    Sprite * _gunSkillSp;
    
    SkillLayer * _skillLayer;
    
    EventListener * _listener;
    
    LabelAtlas * _scoreLabel;
    LabelAtlas * _levelLabel;
    LabelAtlas * _targetLabel;
    ProgressTimer * _timer;
    
private:
    Vector<Sprite*> _iceSpList;
    Vector<SpriteFrame*> _holeFrameList;
    Vector<Sprite*> _bulletFrameList;
public:
    GameStartLayer(std::string);
    static GameStartLayer * createLayer(std::string);
public:
    bool init() override;
    void onEnter() override;
    void onExit() override;
    void update(float) override;
public:
    void createUI();
    void createSpecialBug(float);
    void createNorBug(float);
    void createMoreNorBug();
    void createPassLevelLayer(int);
    void removePassLevelLayer();
    void createPauseLayer();
    void createGameOverLayer();
    void cleanUp();
    void createEventListener();
    void removeEventListener();
    void createGunSkill();
    void destoryGunSkill();
public:
    void pauseBtnCallback(Ref *);
    void soundBtnCallback(Ref *);
    void continueBtnCallback(Ref*);
    void endBtnCallback(Ref*);
    void endGameBtnCallback(Ref*);
public:
    void removeNorBugFromList(Bug*);
    void removeSpBugFromList(Bug*);
    void dieAllNorBlueBug();
    void bombBugEffect(Vec2 & position ,Size & size);
public:
    void skillCallback(int);
    
    void startSkillIce();
    void endSkillIce(float);
    
    void startSkillLaser();
    void endSkillLaser();
    
    void startSkillHole();
    void endSkillHole(float);
    
    void startSkillGun();
    void endSkillGun();
    
    void startSkillMore();
    void endSkillMore();
public:
    void gunSkillCallback(Touch * ,Event*);
public:
    void changeScore(std::string);
    void changeScore();
    void changeLevelAndTarget();
    void changeTime(float);
public:
    void readyBeginAnimation();
    void gameStart();
    void resetData();
    void setEvaluatePath();
};

#endif /* defined(__PressBug_0_1__GameStartLayer__) */
