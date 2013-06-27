//
//  S21ZiBuLei.h
//  JinRiCompany
//
//  Created by lyy on 13-6-24.
//
//

#ifndef __JinRiCompany__S21ZiBuLei__
#define __JinRiCompany__S21ZiBuLei__

#include "cocos2d.h"
#include <string.h>

#include "S2ZiBu.h"

class S21ZiBuLei : public S2ZiBu
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    cocos2d::CCArray * picArray;
    cocos2d::CCArray * labelArray;
    CREATE_FUNC(S21ZiBuLei);
private:
    cocos2d::CCDictionary* plistDic;
    std::map<std::string, std::string> titleMap;
    void S21ZiBuLeiMenuCallback(CCObject* pSender);
    
};
#endif /* defined(__JinRiCompany__S21ZiBuLei__) */
