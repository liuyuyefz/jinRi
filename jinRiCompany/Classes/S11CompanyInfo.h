//
//  S11CompanyInfo.h
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#ifndef __GreTest__S11CompanyInfo__
#define __GreTest__S11CompanyInfo__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S1JinRiShangPinScene.h"

class S11CompanyInfo : public S1JinRiShangPin, public cocos2d::extension::CCScrollViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S11CompanyInfo);
private:
    cocos2d::CCDictionary* plistDic;
    std::map<std::string, std::string> showPicMap;
    std::map<std::string, std::string> showStrMap;
    
    std::vector<float> picWidthVec;
    std::map<std::string, std::string> allScrollPicMap;
    int picIndex;
    float onePicLineWidth;
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    float countOffSet;
    float OffSetX;
    float scrollViewWidth;
    void timer(cocos2d::CCTime dt);
    void timer2(cocos2d::CCTime dt);
    
    void S11companyMenuCallback(CCObject* pSender);

   
    cocos2d::extension::CCScrollView *m_pScrollView;
    
    
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
};

#endif /* defined(__GreTest__S11CompanyInfo__) */
