//
//  ShopLayer.cpp
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#include "ShopLayer.h"
#include "MsgTable.h"

#define PURCHASE_LAYER 100
#define NO_MONEY 101
bool ShopLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    _chooseSkillId = 0;
    _skillPrice.clear();
    
    _skillPrice.push_back(100);
    _skillPrice.push_back(200);
    _skillPrice.push_back(150);
    _skillPrice.push_back(200);
    _skillPrice.push_back(300);
    
    this->createUI();
    return true;
}

void ShopLayer::createUI()
{
    auto titleSp = Sprite::createWithSpriteFrameName("shop_bg.png");
    titleSp->setPosition(VisibleRect::center().x,VisibleRect::height()-titleSp->getContentSize().height/2);
    this->addChild(titleSp);
    
    scrollview = ui::ScrollView::create();
    scrollview->setAnchorPoint(Vec2(0.5, 0.5));
    scrollview->setBounceEnabled(true);
    scrollview->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    scrollview->setContentSize(Size(VisibleRect::width(),VisibleRect::height()-(titleSp->getContentSize().height+ VisibleRect::height()/10 + 120)));
    scrollview->setInnerContainerSize(Size(VisibleRect::width(), scrollview->getContentSize().height+140));
    scrollview->setPosition(Vec2(VisibleRect::center().x,VisibleRect::center().y));
    scrollview->addEventListener(CC_CALLBACK_2(ShopLayer::scrollviewCallback, this));
    this->addChild(scrollview);
    
    auto skillList = SourceManager::getInstance()->getSkillInfo();
    auto skillPriceList = SourceManager::getInstance()->getSkillPriceInfo();
    auto flag = false;
    for (int i= 0; i<6; i++) {
        flag = false;
        
        DDButton * skillBtn = DDButton::createFromFrame(StringUtils::format("skill_shop_%d.png",i));
        skillBtn->setSwallowEnable(false);
        skillBtn->setTag(i);
        skillBtn->setPosition(Vec2(scrollview->getInnerContainerSize().width/2, scrollview->getInnerContainerSize().height - (skillBtn->getContentSize().height*(i+0.6))));
        skillBtn->addCallBackListener(CC_CALLBACK_1(ShopLayer::skillBtnCallback, this));
        scrollview->addChild(skillBtn);
        for (int j = 0; j < skillList.size(); j++) {
            auto skillID = skillList.at(j);
            if (skillID == i) {
                auto hasPurchSp = Sprite::createWithSpriteFrameName("unlock.png");
                hasPurchSp->setPosition(skillBtn->getContentSize().width - hasPurchSp->getContentSize().width/2- 15,skillBtn->getContentSize().height/2 + 10);
                skillBtn->addChild(hasPurchSp);
                flag = true;
                break;
            }
        }
        if (flag == false) {
            auto noPurchSp = Sprite::createWithSpriteFrameName("money_bg.png");
            noPurchSp->setPosition(skillBtn->getContentSize().width - noPurchSp->getContentSize().width/2- 15,skillBtn->getContentSize().height/2 + 10);
            skillBtn->addChild(noPurchSp);
            
            auto price = LabelAtlas::create(StringUtils::format("%d",skillPriceList.at(i)).c_str(),"num_ttf.png",18,24,'0');
            price->setPosition(noPurchSp->getPositionX() - 45,noPurchSp->getPositionY() - 10);
            skillBtn->addChild(price);
        }
    }
    
    auto backBtn = DDButton::createFromFrame("return.png");
    backBtn->setPosition(VisibleRect::center().x,VisibleRect::height()/10);
    backBtn->addCallBackListener(CC_CALLBACK_1(ShopLayer::backCallback,this));
    this->addChild(backBtn);
    
    _goldCount = LabelAtlas::create(StringUtils::format("%d",SourceManager::getInstance()->getGoldInfo()).c_str(), "num_ttf.png",18,24,'0');
    _goldCount->setPosition(VisibleRect::center().x + VisibleRect::center().x/2.5 ,VisibleRect::height()-70 );
    _goldCount->setScale(1.1);
    this->addChild(_goldCount);
}

void ShopLayer::scrollviewCallback(Ref * ref,ui::ScrollView::EventType type)
{
//    CCLOG("The type is : %d",type);
    
}

void ShopLayer::skillBtnCallback(Ref * pSender)
{
    int tag = ((DDButton*)pSender)->getTag();
    auto skillList = SourceManager::getInstance()->getSkillInfo();
    auto skillID = -1;
    for (int i = 0; i < skillList.size(); i++) {
        auto skillid = skillList.at(i);
        if (skillid == tag) {
            skillID = tag;
            break;
        }
    }
    if (skillID != -1) {
        CCLOG("已经购买%d",skillID);
    }
    else
    {
        CCLOG("还没购买");
        _chooseSkillId = tag;
        this->createPurchaseLayer();
    }
//    std::string skill = "";
//    if (tag == 0) {
//        skill = "skill_0";
//    }
//    else if (tag == 1)
//    {
//        skill = "skill_1";
//    }
//    else if (tag == 2)
//    {
//        skill = "skill_2";
//    }
//    else if (tag == 3)
//    {
//        skill = "skill_3";
//    }
//    else if (tag == 4)
//    {
//        skill = "skill_4";
//    }
//    else if (tag == 5)
//    {
//        skill = "skill_5";
//    }
//        CCLOG("%s",skill.c_str());

    
}

void ShopLayer::createPurchaseLayer()
{
    auto purLayer = LayerColor::create(Color4B(144,144,144,1));
    purLayer->setTag(PURCHASE_LAYER);
    auto lis = EventListenerTouchOneByOne::create();
    lis->setSwallowTouches(true);
    
    lis->onTouchBegan =[=] (Touch*,Event*)
    {
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, purLayer);
    this->addChild(purLayer);
    
    auto purbg = Sprite::create("purbg.png");

    purbg->setPosition(VisibleRect::center());
    purLayer->addChild(purbg);
    
    auto sureBtn = DDButton::createFromFrame("sure.png");
    sureBtn->setPosition(purbg->getContentSize().width/2,purbg->getContentSize().height/2 - 20);
    sureBtn->addCallBackListener(CC_CALLBACK_1(ShopLayer::sureBtnCallback, this));
    purbg->addChild(sureBtn);
    
    auto cancelBtn = DDButton::createFromFrame("cancel.png");
    cancelBtn->setPosition(purbg->getContentSize().width/2,sureBtn->getPositionY() - cancelBtn->getContentSize().height - 10);
    cancelBtn->addCallBackListener(CC_CALLBACK_1(ShopLayer::cancelBtnCallback, this));
    purbg->addChild(cancelBtn);
    
    auto purLogo = Sprite::createWithSpriteFrameName("sure_tip.png");
    purLogo->setPosition(purbg->getContentSize().width/2,sureBtn->getPositionY() + sureBtn->getContentSize().height + 30);
    purbg->addChild(purLogo);
    
    
}

void ShopLayer::backCallback(Ref *pSender)
{
    Message * msg = Message::create(MsgTable::CHANGE_TO_CHOOSEPHOTO_LAYER,StringUtils::format("%d",rand()%5));
    MessageCenter::getInstance()->postMessage(msg);
    this->removeFromParent();
}

void ShopLayer::sureBtnCallback(Ref * pSender)
{
    int goldCount = SourceManager::getInstance()->getGoldInfo();
    int skillPrice = _skillPrice.at(_chooseSkillId);
    if (goldCount < skillPrice) {
        auto noMoneySp = Sprite::createWithSpriteFrameName("no_money_tip.png");
        noMoneySp->setTag(NO_MONEY);
        noMoneySp->setPosition(VisibleRect::center());
        this->addChild(noMoneySp);
        
        auto scale = ScaleTo::create(1.5, 0);
        auto seq = Sequence::create(scale,CallFunc::create(CC_CALLBACK_0(ShopLayer::removeNoMoneySp, this)), NULL);
        
        noMoneySp->runAction(seq);
    }
    else
    {
        SourceManager::getInstance()->setGoldInfo(-skillPrice);
        _goldCount->setString(StringUtils::format("%d",goldCount-skillPrice).c_str());
    }
    ((DDButton*)pSender)->getParent()->getParent()->removeFromParent();
}

void ShopLayer::cancelBtnCallback(Ref * pSender)
{
    this->getChildByTag(100)->removeFromParent();
}

void ShopLayer::removeNoMoneySp()
{
    this->getChildByTag(NO_MONEY)->removeFromParent();
}