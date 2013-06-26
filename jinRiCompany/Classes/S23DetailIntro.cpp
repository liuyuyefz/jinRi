//
//  S23DetailIntro.cpp
//  JinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#include "S23DetailIntro.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S23DetailIntro"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S23DetailIntro::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S23DetailIntro *layer = S23DetailIntro::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S23DetailIntro::initInfo2()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
         selectedScene = AppDelegate::S2SelectedScene;
        AppDelegate::S2SceneNum =3;
        bRet = true;
	} while (0);
    
	return bRet;
}
bool S23DetailIntro::setUpSubClass2()
{
	bool bRet = false;
	do
	{
    
        
        CCSprite * aSprite = CCSprite::create(ScriptParser::getImageFromPlist(plistDic,"S23DetailPage"));
        
        CCPoint backPosition = ScriptParser::getPositionFromPlist(plistDic,"S23DetailPage");
        aSprite->setPosition(backPosition);
        this->addChild(aSprite,zNum);
        
        
       /*
        showPicMap = ScriptParser::getGroupImageFromPlist(plistDic,"scrollPic");
        CCSize scrollPicSize = ScriptParser::getSizeFromPlist(plistDic,"scrollPic");
        CCPoint scrollPicPosition = ScriptParser::getPositionFromPlist(plistDic,"scrollPic");
        pTableView = CCTableView::create(this, scrollPicSize);
		pTableView->setDirection(kCCScrollViewDirectionHorizontal);
		pTableView->setAnchorPoint(ccp(0.0,1.0));
        pTableView->setPosition(scrollPicPosition);
		pTableView->setDelegate(this);
		pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(pTableView,zNum+1);
		pTableView->reloadData();
        
        */
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S23DetailIntro::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

CCSize S23DetailIntro::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
    
    CCSprite *pSprite = CCSprite::create(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str());
    
    const char * labelStr = showStrMap[PersonalApi::convertIntToString(idx)].c_str();
    float fontSize = pSprite->getContentSize().height;
    CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
    
    float size1 = pLabel->getContentSize().height;
    float size2 = pSprite->getContentSize().height;
    return CCSizeMake(table->getContentSize().width, size1+size2);
    
}

CCTableViewCell* S23DetailIntro::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CCSprite *pSprite = CCSprite::create(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str());
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setTag(123);
        pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        
    }
    else
    {
        
        CCSprite *pSprite = (CCSprite*)pCell->getChildByTag(123);
        //cocos2d-x 动态修改图片
        // pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str()));
        
    }
    
    
    return pCell;
}

unsigned int S23DetailIntro::numberOfCellsInTableView(CCTableView *table)
{
    CCLOG("xx==%d",showPicMap.size());
    return showPicMap.size();
}

void S23DetailIntro::S2menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    switch (aItem->getTag())
    {
        case btnTag:
            ;
            break;
        case btnTag+1:
            //newScene->addChild(S13News::create());
            
            break;
            
        default:
            break;
    }
}

void S23DetailIntro::S2back(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    
}