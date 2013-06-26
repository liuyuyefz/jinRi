//
//  S1CompanyInfo.h
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#ifndef __GreTest__S1CompanyInfo__
#define __GreTest__S1CompanyInfo__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "JinRiShangPinScene.h"

class S1CompanyInfo : public JinRiShangPin, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S1CompanyInfo);
private:
    cocos2d::CCDictionary* plistDic;
    void companyMenuCallback(CCObject* pSender);
    std::map<std::string, std::string> showPicMap;
    std::map<std::string, std::string> showStrMap;
    cocos2d::extension::CCTableView * pTableView;
    
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
};

#endif /* defined(__GreTest__S1CompanyInfo__) */
