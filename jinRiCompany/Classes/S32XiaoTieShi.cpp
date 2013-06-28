//
//  S32XiaoTieShi.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#include "S32XiaoTieShi.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S311Detail.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S32XiaoTieShi"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S32XiaoTieShi::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S32XiaoTieShi *layer = S32XiaoTieShi::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S32XiaoTieShi::initInfo2()
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
bool S32XiaoTieShi::setUpSubClass2()
{
	bool bRet = false;
	do
	{
   
        showStrMap=ScriptParser::getGroupStringFromPlist(plistDic,"picIntro");
         showPicMap = ScriptParser::getGroupImageFromPlist(plistDic,"scrollPic");
         CCSize scrollPicSize = ScriptParser::getSizeFromPlist(plistDic,"scrollPic");
         CCPoint scrollPicPosition = ScriptParser::getPositionFromPlist(plistDic,"scrollPic");
         pTableView = CCTableView::create(this, scrollPicSize);
         pTableView->setDirection(kCCScrollViewDirectionVertical);
         pTableView->setAnchorPoint(ccp(0.0,1.0));
         pTableView->setPosition(scrollPicPosition);
         pTableView->setDelegate(this);
         pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
         this->addChild(pTableView,zNum+1);
         pTableView->reloadData();
         
         
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S32XiaoTieShi::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

CCSize S32XiaoTieShi::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
    
    CCSprite *pSprite = CCSprite::create(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str());
    
    const char * labelStr = showStrMap[PersonalApi::convertIntToString(idx)].c_str();
    float fontSize = 40;//ScriptParser::getFontSizeFromPlist(plistDic,"picIntro");
    CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
    
    float size1 = pLabel->getContentSize().height;
    float size2 = pSprite->getContentSize().height;
    return CCSizeMake(table->getContentSize().width, size1+size2+5);
    
}

CCTableViewCell* S32XiaoTieShi::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
        
        const char * labelStr = showStrMap[PersonalApi::convertIntToString(idx+1)].c_str();
        float fontSize = 40;//ScriptParser::getFontSizeFromPlist(plistDic,"picIntro");
        CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
        pLabel->setPosition(ccp(pSprite->getContentSize().width+300,pSprite->getContentSize().height/2));
        pLabel->setTag(246);
        pLabel->setColor(ccBLACK);
        pCell->addChild(pLabel,zNum+1);
        
        CCSprite *BottomLineSprite = CCSprite::create("s131RightWordBottom.png");
        BottomLineSprite->setAnchorPoint(CCPointZero);
        BottomLineSprite->setPosition(ccp(0,pSprite->getContentSize().height-5));
        pCell->addChild(BottomLineSprite);
        
    }
    else
    {
        
        CCSprite *pSprite = (CCSprite*)pCell->getChildByTag(123);
        //cocos2d-x 动态修改图片
         pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str()));
        
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(246);
        pLabel->setString(showStrMap[PersonalApi::convertIntToString(idx+1)].c_str());
        
    }
    
    
    return pCell;
}

unsigned int S32XiaoTieShi::numberOfCellsInTableView(CCTableView *table)
{
    CCLOG("xx==%d",showPicMap.size());
    return showPicMap.size();
}

void S32XiaoTieShi::S2menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    newScene->addChild(S311Detail::create());
    switch (aItem->getTag())
    {
        case btnTag:
            ;
            break;
        case btnTag+1:
            
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.5, newScene));//动画过场
}

void S32XiaoTieShi::S2back(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    
}