//
//  S12Leader.h
//  GreTest
//
//  Created by lihex on 6/23/13.
//
//

#ifndef GreTest_S12Leader_h
#define GreTest_S12Leader_h

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S1JinRiShangPinScene.h"

class S12Leader : public S1JinRiShangPin
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S12Leader);
private:
    
    cocos2d::CCDictionary* plistDic;
    void menuCallback(CCObject* pSender);
    std::map<std::string, std::string> showPicMap;
    std::map<std::string, std::string> showStrMap;
    
};



#endif
