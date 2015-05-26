//
//  GameStartLayer.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#include "GameStartLayer.h"

#define PAUSE_LAYER  1000
#define GAMEOVER_LAYER  1001
#define PAUSE_LAYER_CONTIMUE_BTN 900
#define PASS_LEVEL_LAYER 1002
#define BEGIN_SPRITE  901

GameStartLayer::GameStartLayer(std::string path):
_path(path),
_bgSprite(nullptr),
_holeSkill(nullptr),
_skillLayer(nullptr),
_listener(nullptr),
_gunSkillSp(nullptr),
_bulletCount(0),
_score(0),
_level(1),
_target(20),
_scoreLabel(nullptr),
_levelLabel(nullptr),
_targetLabel(nullptr),
_timer(nullptr),
_pause(false)
{
    _norBugList.clear();
    _spBugList.clear();
    _iceSpList.clear();
    _bulletCount  = SkillManager::getInstance()->getGunCount();
}

GameStartLayer * GameStartLayer::createLayer(std::string path)
{
    GameStartLayer * layer = new GameStartLayer(path);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool GameStartLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->createUI();
    this->readyBeginAnimation();
    return true;
}


void GameStartLayer::onEnter()
{
    Layer::onEnter();
    
}

void GameStartLayer::onExit()
{
    
    Layer::onExit();
}

void GameStartLayer::createUI()
{
    _bgSprite = Sprite::create(_path);
    _bgSprite->setPosition(VisibleRect::center());
    this->addChild(_bgSprite);

//////////////----------SKILL---------------//////////////////////////////
    /// SKIL_ICE
    auto bgIce = Sprite::createWithSpriteFrameName("iced_0.png");
    bgIce->setVisible(false);
    bgIce->setPosition(VisibleRect::center());
    this->addChild(bgIce);
    _iceSpList.pushBack(bgIce);
    
    auto leftIce = Sprite::createWithSpriteFrameName("left.png");
    leftIce->setVisible(false);
    leftIce->setAnchorPoint(Vec2(0, 0.5));
    leftIce->setPosition(VisibleRect::left());
    this->addChild(leftIce,100);
    _iceSpList.pushBack(leftIce);
    
    auto bottomIce = Sprite::createWithSpriteFrameName("down.png");
    bottomIce->setVisible(false);
    bottomIce->setAnchorPoint(Vec2(0.5, 0));
    bottomIce->setPosition(VisibleRect::bottom());
    this->addChild(bottomIce,100);
    _iceSpList.pushBack(bottomIce);
    
    auto rightIce = Sprite::createWithSpriteFrameName("right.png");
    rightIce->setVisible(false);
    rightIce->setAnchorPoint(Vec2(1, 0.5));
    rightIce->setPosition(VisibleRect::right());
    this->addChild(rightIce,100);
    _iceSpList.pushBack(rightIce);
    
    auto topIce = Sprite::createWithSpriteFrameName("up.png");
    topIce->setVisible(false);
    topIce->setAnchorPoint(Vec2(0.5, 1));
    topIce->setPosition(VisibleRect::top());
    this->addChild(topIce,100);
    _iceSpList.pushBack(topIce);
    ///
    
    
    ///HOLE_SKILL
    _holeSkill = Sprite::createWithSpriteFrameName("black_hole_0.png");
    _holeSkill->setVisible(false);
    _holeSkill->setPosition(VisibleRect::center());
    this->addChild(_holeSkill);
    
    for (int i =0; i<4; i++) {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("black_hole_%d.png",i));
        _holeFrameList.pushBack(frame);
    }
    ///

////////////////////////////////////////////
    
    auto skillbgSp = Sprite::createWithSpriteFrameName("skill_bg.png");
    skillbgSp->setPosition(VisibleRect::center().x,VisibleRect::height()/12-10);
    this->addChild(skillbgSp);
    
    auto targetLevelScoreBgSp = Sprite::createWithSpriteFrameName("header.png");
    targetLevelScoreBgSp->setPosition(VisibleRect::center().x,VisibleRect::height()-targetLevelScoreBgSp->getContentSize().height/2-5);
    this->addChild(targetLevelScoreBgSp);
    
    auto timeBg = Sprite::createWithSpriteFrameName("time_bg.png");
    timeBg->setPosition(VisibleRect::center().x,targetLevelScoreBgSp->getPositionY()-timeBg->getContentSize().height+12);
    this->addChild(timeBg);
  
    auto  progress = Sprite::createWithSpriteFrameName("time_line.png");
    _timer = ProgressTimer::create(progress);
    _timer->setType(ProgressTimer::Type::BAR);
    _timer->setMidpoint(Vec2(0, 0));
    _timer->setBarChangeRate(Vec2(1, 0));
    _timer->setPercentage(100);
    _timer->setPosition(VisibleRect::center().x,timeBg->getPositionY() - 10);
    this->addChild(_timer);
    
    auto timeBox = Sprite::createWithSpriteFrameName("time_fg.png");
    timeBox->setPosition(VisibleRect::center().x,targetLevelScoreBgSp->getPositionY()-timeBox->getContentSize().height);
    this->addChild(timeBox);
    
    auto pauseBtn = DDButton::createFromFrame("menu.png");
    pauseBtn->setPosition(skillbgSp->getContentSize().width-150, pauseBtn->getContentSize().height/2+20);
    pauseBtn->addCallBackListener(CC_CALLBACK_1(GameStartLayer::pauseBtnCallback, this));
    skillbgSp->addChild(pauseBtn);
    
    auto soundBtn = DDButton::createFromFrame("music_on.png");
    soundBtn->setPosition(skillbgSp->getContentSize().width-50, pauseBtn->getContentSize().height/2+20);
    soundBtn->addCallBackListener(CC_CALLBACK_1(GameStartLayer::soundBtnCallback, this));
    skillbgSp->addChild(soundBtn);
    
    auto arry = SkillManager::getInstance()->getSelectedSkill();

    _skillLayer = SkillLayer::create(arry);
    this->addChild(_skillLayer,100);
    
// //   this->schedule(schedule_selector(GameStartLayer::createNorBug), 0.4);
//    this->schedule(schedule_selector(GameStartLayer::createSpecialBug), 1);
    
 //   this->addChild(BugManager::getInstance()->createBug(BugType::norCarpenterBug));
//    this->addChild(BugManager::getInstance()->createBug(BugType::norMosquito));
  //  this->addChild(BugManager::getInstance()->createBug(BugType::norRedBeetle));
  //  this->addChild(BugManager::getInstance()->createBug(BugType::norYellowBeetle));
 //   this->addChild(BugManager::getInstance()->createBug(BugType::norYellowBeetle));
 //   this->addChild(BugManager::getInstance()->createBug(BugType::bombBug));
    
    /////scroe level target  timer
    _scoreLabel = LabelAtlas::create("0", "num_ttf.png", 18, 24, '0');
    _scoreLabel->setPosition(VisibleRect::width()/2 - 45, VisibleRect::height() - 45);
    this->addChild(_scoreLabel);
    _levelLabel = LabelAtlas::create("1", "num_ttf.png", 18, 24, '0');
    _levelLabel->setPosition(VisibleRect::width()/7 + 5, VisibleRect::height() - 45);
    this->addChild(_levelLabel);
    
    _targetLabel = LabelAtlas::create(StringUtils::format("%d",_target).c_str(), "num_ttf.png", 18, 24, '0');
    _targetLabel->setPosition(VisibleRect::width() - 130, VisibleRect::height() - 45);
    this->addChild(_targetLabel);
    
}

void GameStartLayer::pauseBtnCallback(Ref * pSender)
{
    this->createPauseLayer();
}

void GameStartLayer::soundBtnCallback(Ref * pSender)
{
    
}

void GameStartLayer::continueBtnCallback(Ref* pSender)
{
    int tag = ((DDButton*)pSender)->getTag();
    ((DDButton*)pSender)->getParent()->removeFromParent();
    auto pauseLayer = this->getChildByTag(PAUSE_LAYER);
    if (pauseLayer) {
        pauseLayer->removeFromParent();
    }
    if (tag != PAUSE_LAYER_CONTIMUE_BTN) {
        _pause = true;
        this->readyBeginAnimation();
    }
    else
    {
        _pause = false;
    }

}

void GameStartLayer::endBtnCallback(Ref* pSender)
{
    _pause = true;
    this->createGameOverLayer();
}

void GameStartLayer::endGameBtnCallback(Ref* pSender)
{
    this->cleanUp();
    Message * msg = Message::create(MsgTable::CHANGE_TO_CLICKSTART_LAYER);
    MessageCenter::getInstance()->postMessage(msg);
}

void GameStartLayer::createNorBug(float dt)
{
    if (!_pause) {
        int bugNum = rand()%4+1;
        auto bug = BugManager::getInstance()->createBug(bugNum);
        this->addChild(bug);
        
        _norBugList.pushBack(bug);
    }
}

void GameStartLayer::createSpecialBug(float dt)
{
    if (!_pause) {
        int probability = rand()%100;
        if (probability > 40) {
            int bugNum = rand()%5+5;
            auto bug = BugManager::getInstance()->createBug(bugNum);
            this->addChild(bug);
            _spBugList.pushBack(bug);
        }
    }
}

void GameStartLayer::createMoreNorBug()
{
    auto buglist = BugManager::getInstance()->createMoreBug();
    for (int i=0; i<buglist.size(); i++) {
        auto bug = buglist.at(i);
        _norBugList.pushBack(bug);
        this->addChild(bug);
    }
    this->endSkillMore();
}

void GameStartLayer::update(float dt)
{
    if (!_pause) {
        this->changeScore();
        
        if (_norBugList.size() >0) {
            for (int i= 0; i<_norBugList.size(); i++) {
                if (_norBugList.at(i) == nullptr) {
                    _norBugList.erase(i);
                }
            }
        }
        
        if (_spBugList.size() >0 ) {
            for (int i= 0; i<_spBugList.size(); i++) {
                if (_spBugList.at(i) == nullptr) {
                    _spBugList.erase(i);
                }
            }
        }
        
        auto extraScore = this->getChildByTag(20);
        if (extraScore && extraScore->isVisible() == false) {
            extraScore->removeFromParent();
        }
        
        if (SkillManager::getInstance()->getLaserSkill()) {
            auto laser = _skillLayer->getLaserSkill();
            if (laser != nullptr) {
                auto box = _skillLayer->getLaserSkill()->getBoundingBox();
                for (int i = 0; i <_norBugList.size(); i++) {
                    auto bug = _norBugList.at(i);
                    auto bugBox = bug->getBoundingBox();
                    if (bugBox.intersectsRect(box)) {
                        bug->directDieAction();
                    }
                }
                for (int i = 0; i<_spBugList.size(); i++) {
                    auto bug = _spBugList.at(i);
                    auto bugBox = bug->getBoundingBox();
                    if (bugBox.intersectsRect(box)) {
                        bug->directDieAction();
                    }
                }
            }
        }
    }

}

void GameStartLayer::cleanUp()
{
    SourceManager::getInstance()->cleanupScore();
    this->removeFromParent();
}

void GameStartLayer::createPauseLayer()
{
    _pause = true;
    auto pauseLayer = LayerColor::create(Color4B(0, 0, 0, 144));
    pauseLayer->setTag(PAUSE_LAYER);
    this->addChild(pauseLayer,101);
    
    auto continueBtn = DDButton::createFromFrame("continue.png");
    continueBtn->setTag(PAUSE_LAYER_CONTIMUE_BTN);
    continueBtn->setPosition(VisibleRect::center().x,VisibleRect::center().y+100);
    continueBtn->addCallBackListener(CC_CALLBACK_1(GameStartLayer::continueBtnCallback,this));
    pauseLayer->addChild(continueBtn);
    
    auto endBtn = DDButton::createFromFrame("end_game.png");
    endBtn->setPosition(VisibleRect::center().x,VisibleRect::center().y-100);
    endBtn->addCallBackListener(CC_CALLBACK_1(GameStartLayer::endBtnCallback, this));
    pauseLayer->addChild(endBtn);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch,Event*event){
        return true;
    };
    
    pauseLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pauseLayer);
}

void GameStartLayer::createGameOverLayer()
{

    auto gameOverLayer = Layer::create();
    gameOverLayer->setTag(GAMEOVER_LAYER);
    this->addChild(gameOverLayer,101);
    
    auto bg = Sprite::create("gameover_bg.png");
    bg->setPosition(VisibleRect::center());
    gameOverLayer->addChild(bg);
    
    auto againBtn = DDButton::createFromFrame("tryAgain.png");
    againBtn->setPosition(VisibleRect::center().x -150,VisibleRect::height()/7);
    againBtn->addCallBackListener(CC_CALLBACK_1(GameStartLayer::continueBtnCallback,this));
    gameOverLayer->addChild(againBtn);
    
    auto endBtn = DDButton::createFromFrame("endgame.png");
    endBtn->setPosition(VisibleRect::center().x + 150,VisibleRect::height()/7);
    endBtn->addCallBackListener(CC_CALLBACK_1(GameStartLayer::endGameBtnCallback,this));
    gameOverLayer->addChild(endBtn);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch,Event*event){
        return true;
    };
    
    auto scoreLabel = LabelAtlas::create(StringUtils::format("%d",_score).c_str(),"num_ttf.png", 18, 24, '0');
    scoreLabel->setPosition(bg->getContentSize().width/2 - 50, bg->getContentSize().height/2 + bg->getContentSize().height / 5 - 10);
    scoreLabel->setScale(2.2);
    bg->addChild(scoreLabel);
    
    auto hisScore = SourceManager::getInstance()->getHisScoreInfo();
    auto hisScoreLabel = LabelAtlas::create(StringUtils::format("%d",hisScore).c_str(),"num_ttf.png", 18, 24, '0');
    hisScoreLabel->setScale(1.5);
    hisScoreLabel->setPosition(bg->getContentSize().width/2, bg->getContentSize().height/2 + 70);
    bg->addChild(hisScoreLabel);
    
    this->setEvaluatePath();
    
    auto evaluateSp = Sprite::createWithSpriteFrameName(_evaluatePath.c_str());
    evaluateSp->setPosition(bg->getContentSize().width/2 + 20, bg->getContentSize().height/2 + 15);
    bg->addChild(evaluateSp);
    
    if(hisScore < _score)
    {
        SourceManager::getInstance()->setHisScoreInfo(_score);
        auto newRecoredSp = Sprite::create("newMax.png");
        newRecoredSp->setPosition(scoreLabel->getPositionX() + 80,scoreLabel->getPositionY() + 100);
        bg->addChild(newRecoredSp);
    }
    
    int gold = _score/10;
    auto goldLabel = LabelAtlas::create(StringUtils::format("%d",gold).c_str(),"num_ttf.png", 18, 24, '0');
    goldLabel->setScale(3);
    goldLabel->setPosition(VisibleRect::center().x - 50,VisibleRect::center().y - 200);
    bg->addChild(goldLabel);
    
    SourceManager::getInstance()->setGoldInfo(gold);
    
    gameOverLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, gameOverLayer);
}

void GameStartLayer::removeSpBugFromList(Bug *bug)
{
    this->_spBugList.eraseObject(bug);
}

void GameStartLayer::removeNorBugFromList(Bug * bug)
{
    this->_norBugList.eraseObject(bug);
}

void GameStartLayer::dieAllNorBlueBug()
{
    this->unschedule(schedule_selector(GameStartLayer::createNorBug));
    for (int i= 0; i<_norBugList.size(); i++) {
        auto bug = _norBugList.at(i);
        if (bug != nullptr && bug->getType() == BugType::normalBlueBug) {
            bug->directDieAction();
            _norBugList.erase(i);
        }
    }
    this->schedule(schedule_selector(GameStartLayer::createNorBug), 0.25);
}

void GameStartLayer::bombBugEffect(Vec2 &position, Size &size)
{
    this->unschedule(schedule_selector(GameStartLayer::createNorBug));
    Rect rect = Rect(position.x - size.width/2, position.y - size.height/2, size.width, size.height);
    for (int i= 0; i<_norBugList.size(); i++) {
        auto bug = _norBugList.at(i);
        if (bug != nullptr && rect.containsPoint(bug->getPosition())) {
            bug->directDieAction();
            _norBugList.erase(i);
        }
    }
    this->schedule(schedule_selector(GameStartLayer::createNorBug), 0.25);
}

void GameStartLayer::createEventListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch,Event*event)
    {
        return true;
    };
    
    if (SkillManager::getInstance()->getGunSkill()) {
        listener->onTouchEnded = [=](Touch * touch,Event * event)
        {
            this->gunSkillCallback(touch, event);
        };
    }
    
    _listener = listener;
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameStartLayer::removeEventListener()
{
    this->getEventDispatcher()->removeEventListener(_listener);
}

void GameStartLayer::createGunSkill()
{
    this->createEventListener();
    
    _gunSkillSp = Sprite::createWithSpriteFrameName("shoot_bg.png");
    _gunSkillSp->setScaleY(1.1);
    for (int i =0; i<5; i++) {
        auto bullet = Sprite::createWithSpriteFrameName("tama.png");
        bullet->setScale(0.8);
        bullet->setTag(i);
        bullet->setPosition(_gunSkillSp->getContentSize().width/5 + i*bullet->getContentSize().width, _gunSkillSp->getContentSize().height/2);
        _gunSkillSp->addChild(bullet);
        
        _bulletFrameList.pushBack(bullet);
    }
    _gunSkillSp->setAnchorPoint(Vec2(0.5, 1));
    _gunSkillSp->setPosition(VisibleRect::bottom());
    this->addChild(_gunSkillSp,100);
    
    auto moveAct = MoveBy::create(1, Vec2(0, _gunSkillSp->getContentSize().height + 15));
    _gunSkillSp->runAction(moveAct);
}

void GameStartLayer::destoryGunSkill()
{
    SkillManager::getInstance()->setGunSkill(false);
    
    auto moveAct = MoveTo::create(2, VisibleRect::bottom());
    
    auto seq = Sequence::create(moveAct,CCCallFunc::create(CC_CALLBACK_0(GameStartLayer::removeEventListener, this)), NULL);
    _gunSkillSp->runAction(seq);
    
    this->removeEventListener();
}

void GameStartLayer::skillCallback(int skillNum)
{
    if (skillNum == SkillType::skill_ice) {
        this->startSkillIce();
    }
    if (skillNum == SkillType::skill_gun) {
        this->startSkillGun();
    }
    if (skillNum == SkillType::skill_hole) {
        this->startSkillHole();
    }
    if (skillNum == SkillType::skill_laser) {
        this->startSkillLaser();
    }
    if (skillNum == SkillType::skill_more) {
        this->startSkillMore();
    }
}

void GameStartLayer::startSkillIce()
{
    SkillManager::getInstance()->setIceSkill(true);
    
    for (int i =0 ; i<_iceSpList.size(); i++) {
        auto iceSp = _iceSpList.at(i);
        iceSp->setVisible(true);
    }
    this->scheduleOnce(schedule_selector(GameStartLayer::endSkillIce), 4);
}

void GameStartLayer::endSkillIce(float dt)
{
    SkillManager::getInstance()->setIceSkill(false);
    
    for (int i =0 ; i<_iceSpList.size(); i++) {
        auto iceSp = _iceSpList.at(i);
        iceSp->setVisible(false);
    }
}

void GameStartLayer::startSkillGun()
{
    SkillManager::getInstance()->setGunSkill(true);
    this->createGunSkill();
}

void GameStartLayer::endSkillGun()
{
    this->destoryGunSkill();
}

void GameStartLayer::startSkillHole()
{
    SkillManager::getInstance()->setHoleSkill(true);
    
    _holeSkill->setVisible(true);
    auto animation = Animation::createWithSpriteFrames(_holeFrameList,0.1);
    auto animate = Animate::create(animation);
    _holeSkill->runAction(RepeatForever::create(animate));
    
    this->scheduleOnce(schedule_selector(GameStartLayer::endSkillHole), 4);
}

void GameStartLayer::endSkillHole(float dt)
{
    SkillManager::getInstance()->setHoleSkill(false);

    _holeSkill->stopAllActions();
    _holeSkill->setVisible(false);
}

void GameStartLayer::startSkillLaser()
{
    SkillManager::getInstance()->setLaserSkill(true);
    _skillLayer->createTouchEvent();
}

void GameStartLayer::endSkillLaser()
{
    
}

void GameStartLayer::startSkillMore()
{
    SkillManager::getInstance()->setMoreSkill(true);
    this->createMoreNorBug();
}

void GameStartLayer::endSkillMore()
{
    if (SkillManager::getInstance()->getGunCount() <= 0) {
        
    }
    SkillManager::getInstance()->setMoreSkill(false);
}

void GameStartLayer::gunSkillCallback(Touch* touch, Event * event)
{
    auto pos = touch->getLocation();
    auto gunSp = GunBangSp::create(pos);
    auto box = gunSp->getBoundingBox();
    
    this->addChild(gunSp);

    
    for (int i = 0; i< _norBugList.size(); i++) {
        auto sp = _norBugList.at(i);
        auto bugBox = sp->getBoundingBox();
        if (box.intersectsRect(bugBox) && sp != nullptr){
            sp->directDieAction();
            _norBugList.eraseObject(sp);
        }
    }
    
    for (int i = 0 ; i< _spBugList.size(); i++) {
        auto sp = _spBugList.at(i);
        auto bugBox = sp->getBoundingBox();
        if (box.intersectsRect(bugBox) && sp != nullptr) {
            sp->directDieAction();
            _spBugList.eraseObject(sp);
        }

    }
    
    _bulletCount--;
    if (_bulletCount >=0) {
        auto bullet = _bulletFrameList.at(_bulletCount);
        _bulletFrameList.eraseObject(bullet);
        bullet->removeFromParent();
        if (_bulletCount == 0) {
            this->endSkillGun();
            _bulletCount = SkillManager::getInstance()->getGunCount();
        }
    }
}

void GameStartLayer::changeScore(std::string scr)
{
    int s;
    sscanf(scr.c_str(), "%d",&s);
    
    _score += s;
    
    if (_score < 0) {
        _score = 0;
    }
    _scoreLabel->setString(StringUtils::format("%d",_score).c_str());
}

void GameStartLayer::changeScore()
{
    _score = SourceManager::getInstance()->getScore();
    
    if (_score < 0) {
        _score = 0;
    }
    _scoreLabel->setString(StringUtils::format("%d",_score).c_str());
    
    if (_score >= _target) {
        this->createPassLevelLayer(0);
        this->_timer->setPercentage(100);
        this->changeLevelAndTarget();
    }
}

void GameStartLayer::changeLevelAndTarget()
{
    _target =_target + _level * 5;
    _level++;
    
    _levelLabel->setString(StringUtils::format("%d",_level).c_str());
    _targetLabel->setString(StringUtils::format("%d",_target).c_str());
}

void GameStartLayer::changeTime(float dt)
{
    if (_pause) {
        
    }
    else
    {
        auto percentage = _timer->getPercentage();
        _timer->setPercentage(percentage - 20);
        if (percentage <= 0) {
            if (_score < _target) {
                _pause = true;
                this->createGameOverLayer();
            }
        }
    }
}

void GameStartLayer::resetData()
{
    this->unscheduleUpdate();
    this->unschedule(schedule_selector(GameStartLayer::changeTime));
    this->unschedule(schedule_selector(GameStartLayer::createNorBug));
    this->unschedule(schedule_selector(GameStartLayer::createSpecialBug));
    
    _score = 0;
    _target = 20;
    _level = 1;
    
    _scoreLabel->setString("0");
    _levelLabel->setString("1");
    _targetLabel->setString("25");
    
    _pause = false;
    
    for (int i =0 ; i < _norBugList.size(); i++) {
        auto bug = _norBugList.at(i);
        if (bug) {
            bug->removeFromParentAndCleanup(true);
        }
    }
    
    for (int i =0 ; i < _spBugList.size(); i++) {
        auto bug = _spBugList.at(i);
        if (bug) {
            bug->removeFromParentAndCleanup(true);
        }
    }
    
    _timer->setPercentage(100);
    
    _norBugList.clear();
    _spBugList.clear();

}

void GameStartLayer::setEvaluatePath()
{
    if (_score  <=10) {
        _evaluatePath = "0.png";
    }
    else if(_score > 10 && _score <= 30)
    {
        _evaluatePath = "1.png";
    }
    else if(_score > 30 && _score <= 60)
    {
        _evaluatePath = "2.png";
    }
    else if(_score > 60 && _score <= 90)
    {
        _evaluatePath = "3.png";
    }
    else if(_score > 90 && _score <= 120)
    {
        _evaluatePath = "4.png";
    }
    else if(_score > 120 && _score <= 150)
    {
        _evaluatePath = "5.png";
    }
    else if(_score > 150 && _score <= 180)
    {
        _evaluatePath = "6.png";
    }
    else if(_score > 180 && _score <= 210)
    {
        _evaluatePath = "7.png";
    }
    else if(_score > 210 && _score <= 240)
    {
        _evaluatePath = "8.png";
    }
    else if(_score > 240 && _score <= 270)
    {
        _evaluatePath = "9.png";
    }
    else if(_score > 270)
    {
        _evaluatePath = "10.png";
    }

}

void GameStartLayer::readyBeginAnimation()
{
    this->resetData();
    
    auto beginSp = Sprite::createWithSpriteFrameName("level_tip_1.png");
    beginSp->setPosition(VisibleRect::width()/2, VisibleRect::height() + beginSp->getContentSize().height + 20);
    beginSp->setTag(BEGIN_SPRITE);
    this->addChild(beginSp);
    
    auto moveToCenter = MoveTo::create(1, VisibleRect::center());
    
    Vector<SpriteFrame*> anim;
    char spName[100] = {0};
    for (int i = 2; i<=5; i++) {
        sprintf(spName,"level_tip_%d.png",i);
        anim.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(spName));
    }
    auto animation = Animation::createWithSpriteFrames(anim,0.5);
    auto animate = Animate::create(animation);
    
    auto delay = DelayTime::create(1);
    
    auto seq = Sequence::create(moveToCenter,delay,animate, CallFunc::create(CC_CALLBACK_0(GameStartLayer::gameStart, this)),NULL);
    
    beginSp->runAction(seq);
    
}

void GameStartLayer::gameStart()
{
    this->getChildByTag(BEGIN_SPRITE)->removeFromParentAndCleanup(true);
    
    this->scheduleUpdate();
    this->schedule(schedule_selector(GameStartLayer::changeTime), 1);
    this->schedule(schedule_selector(GameStartLayer::createNorBug), 0.4);
    this->schedule(schedule_selector(GameStartLayer::createSpecialBug), 1);
}

void GameStartLayer::createPassLevelLayer(int type)
{
    auto passLevelLayer = Layer::create();
    passLevelLayer->setTag(PASS_LEVEL_LAYER);
    this->addChild(passLevelLayer,101);
    
    auto passSp = Sprite::createWithSpriteFrameName("level_tip_30.png");
    passSp->setPosition(VisibleRect::width()+passSp->getContentSize().width,VisibleRect::width());
    passLevelLayer->addChild(passSp);
    
    auto move = MoveTo::create(1, Vec2(-passSp->getContentSize().width, VisibleRect::width()));
    auto seq = Sequence::create(move,CallFunc::create(CC_CALLBACK_0(GameStartLayer::removePassLevelLayer, this)), NULL);
    passSp->runAction(seq);
}

void GameStartLayer::removePassLevelLayer()
{
    this->getChildByTag(PASS_LEVEL_LAYER)->removeFromParent();
}