//
//  S111Intro.h
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#ifndef __jinRiCompany__S111Intro__
#define __jinRiCompany__S111Intro__

#include "cocos2d.h"
#include <string.h>
#include "S3SijiYangSheng.h"

class S111Intro : public S3SijiYangSheng
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S111Intro);
private:
    cocos2d::CCDictionary* plistDic;
    cocos2d::CCMenu *imagemenu ;
    
    std::map<std::string, std::string> showPicMap;
    std::map<std::string, std::string> showStrMap;
    void S111IntroCallback(CCObject * pSender);
    
};

#endif /* defined(__jinRiCompany__S111Intro__) */

