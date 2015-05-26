//
//  ShopLayer.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/8.
//
//

#ifndef __PressBug_0_1__ShopLayer__
#define __PressBug_0_1__ShopLayer__

#include "DDLIB/Share/IncludeFile.h"
#include "SourceManager.h"
class ShopLayer:public Layer
{
private:
    vector<int> _skillPrice;
    ui::ScrollView * scrollview;
    LabelAtlas * _goldCount;
    int _chooseSkillId;
public:
    bool init() override;
public:
    void createUI();
public:
    void backCallback(Ref*);
    void skillBtnCallback(Ref*);
    void scrollviewCallback(Ref*,ui::ScrollView::EventType);
    void sureBtnCallback(Ref*);
    void cancelBtnCallback(Ref*);
public:
    void createPurchaseLayer();
    void removeNoMoneySp();
    CREATE_FUNC(ShopLayer);
};

#endif /* defined(__PressBug_0_1__ShopLayer__) */
