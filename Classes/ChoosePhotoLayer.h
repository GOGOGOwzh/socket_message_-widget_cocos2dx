//
//  ChoosePhotoLayer.h
//  PressBug_0.1
//
//  Created by wzh on 15/3/7.
//
//

#ifndef __PressBug_0_1__ChoosePhotoLayer__
#define __PressBug_0_1__ChoosePhotoLayer__

#include "DDLIB/Share/IncludeFile.h"
USING_NS_CC;

class ChoosePhotoLayer:public Layer
{
private:
    std::string _path;
public:
    ChoosePhotoLayer(std::string path = "");
    static ChoosePhotoLayer * createLayer(std::string);
public:
    bool init() override;
    void createUI();
    void endLayer();
    void randPath();
public:
    void beginBtnCallback(Ref*);
    void shopBtnCallback(Ref*);
    void backBtnCallback(Ref*);
    
    void chooseFirstPhBtnCallback(Ref*);
    void chooseSecBtnCallback(Ref*);
    void chooseThirdPhBtnCallback(Ref*);
};

#endif /* defined(__PressBug_0_1__ChoosePhotoLayer__) */
