//
//  S31MeiShi.h
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#ifndef __jinRiCompany__S31MeiShi__
#define __jinRiCompany__S31MeiShi__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"
#include "S3SijiYangSheng.h"

class S31MeiShi : public S3SijiYangSheng, public cocos2d::extension::CCScrollViewDelegate//, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate//, public cocos2d::extension::CCScrollViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S31MeiShi);
private:
    cocos2d::CCDictionary* plistDic;
    cocos2d::CCMenu *imagemenu ;
    void S31MeiShiMenuCallback(CCObject* pSender);
    
    void timer(cocos2d::CCTime dt);
    void timer2(cocos2d::CCTime dt);
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    std::map<std::string, std::string> showPicMap;
    std::map<std::string, std::string> showStrMap;
    void S31MeiShiCallback(CCObject * pSender);
    
    float countOffSet;
    float OffSetY;
    cocos2d::extension::CCScrollView *m_pScrollView;
    
    
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    
    /*
    cocos2d::extension::CCTableView * pTableView;
    
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
    */
    
};

#endif /* defined(__jinRiCompany__S31MeiShi__) */
