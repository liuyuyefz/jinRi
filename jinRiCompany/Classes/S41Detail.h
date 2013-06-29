//
//  S41Detail.h
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#ifndef __jinRiCompany__S41Detail__
#define __jinRiCompany__S41Detail__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S4HeZuo.h"

class S41Detail : public S4HeZuo, public cocos2d::extension::CCScrollViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S41Detail);
private:
    cocos2d::CCDictionary* plistDic;
    cocos2d::extension::CCScrollView *m_pScrollView;
    
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};

};

#endif /* defined(__jinRiCompany__S41Detail__) */
