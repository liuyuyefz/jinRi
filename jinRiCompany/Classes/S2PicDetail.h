//
//  S2PicDetail.h
//  JinRiCompany
//
//  Created by lyy on 13-6-25.
//
//

#ifndef __JinRiCompany__S2PicDetail__
#define __JinRiCompany__S2PicDetail__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S2ZiBu.h"

class S2PicDetail : public S2ZiBu, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S2PicDetail);
private:
    cocos2d::CCDictionary* plistDic;
   
    std::map<std::string, std::string> showPicMap;
    std::map<std::string, std::string> showStrMap;
    
    void S2menuCallback(CCObject* pSender);
    void S2back(CCObject* pSender);
    cocos2d::extension::CCTableView * pTableView;
    
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
};
#endif /* defined(__JinRiCompany__S2PicDetail__) */
