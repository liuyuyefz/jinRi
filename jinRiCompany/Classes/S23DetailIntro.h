//
//  S23DetailIntro.h
//  JinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#ifndef __JinRiCompany__S23DetailIntro__
#define __JinRiCompany__S23DetailIntro__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S2ZiBu.h"

class S23DetailIntro : public S2ZiBu, public cocos2d::extension::CCScrollViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S23DetailIntro);
private:
    cocos2d::CCDictionary* plistDic;
    
    cocos2d::extension::CCScrollView *m_pScrollView;
    
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
    std::map<std::string, std::string> showPicMap;
    std::map<std::string, std::string> showStrMap;
    
    void S2menuCallback(CCObject* pSender);
    void showBigPic(CCObject* pSender);
    void S2back(CCObject* pSender);

    
};
#endif /* defined(__JinRiCompany__S23DetailIntro__) */
