//
//  S22PicDetail.cpp
//  JinRiCompany
//
//  Created by lyy on 13-6-25.
//
//

#include "S22PicDetail.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S22PicDetail"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S22PicDetail::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S22PicDetail *layer = S22PicDetail::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S22PicDetail::initInfo2()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
         selectedScene = AppDelegate::S2SelectedScene;
        AppDelegate::S2SceneNum = 2;
        bRet = true;
	} while (0);
    
	return bRet;
}
bool S22PicDetail::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        const char* S22BigImgStr = ScriptParser::getImageFromPlist(plistDic,"S22BigImg");
        CCPoint S22BigImgPosition = ScriptParser::getPositionFromPlist(plistDic,"S22BigImg");
        CCSprite * S22BigImgSp = CCSprite::create(S22BigImgStr);
        S22BigImgSp->setPosition(S22BigImgPosition);
        this->addChild(S22BigImgSp,zNum);
        
        CCPoint productNamePosition = ScriptParser::getPositionFromPlist(plistDic,"productName");
        const char* productNameStr = ScriptParser::getStringFromPlist(plistDic,"productName");
        float productNameFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"productName");
        CCLabelTTF *productNameLabel = CCLabelTTF::create(productNameStr, s1FontName_macro, productNameFontSize);
        productNameLabel->setPosition(productNamePosition);
        productNameLabel->setColor(ccc3(112.0,16.0,12.0));
        this->addChild(productNameLabel,zNum);
        
        {
            CCSprite * aSprite = CCSprite::create("S22DisplayPrevBtn.png");
            aSprite->setRotation(180.0);
            
            CCPoint backPosition = ScriptParser::getPositionFromPlist(plistDic,"back");
            aSprite->setPosition(backPosition);
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S22PicDetail::S2back));
			aItem->setTag(btnTag+1);
			aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setScale(2.0);
			_menu ->addChild(aItem,zNum);
        }
        
        CCSprite * tableViewBackGroundSp = CCSprite::create("S22DisplayBackground.png");
        tableViewBackGroundSp->setAnchorPoint(ccp(0.0,1.0));
        tableViewBackGroundSp->setPosition(ccp(S22BigImgSp->getPosition().x-S22BigImgSp->getContentSize().width/2,S22BigImgSp->getPosition().y-S22BigImgSp->getContentSize().height/2-10));
        this->addChild(tableViewBackGroundSp,zNum);
        
        
        
        
        {
            CCSprite * aSprite = CCSprite::create("S22DisplayPrevBtn.png");
            aSprite->setPosition(ccp(tableViewBackGroundSp->getPosition().x+20,tableViewBackGroundSp->getPosition().y-tableViewBackGroundSp->getContentSize().height/2));
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S22PicDetail::S2menuCallback));
			aItem->setTag(btnTag);
			aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setScale(2.0);
			_menu ->addChild(aItem,zNum);
        }
        
        {
            CCSprite * aSprite = CCSprite::create("S22DisplayPrevBtn.png");
            aSprite->setRotation(180.0);
            aSprite->setPosition(ccp(tableViewBackGroundSp->getPosition().x+tableViewBackGroundSp->getContentSize().width-20,tableViewBackGroundSp->getPosition().y-tableViewBackGroundSp->getContentSize().height/2));
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S22PicDetail::S2menuCallback));
			aItem->setTag(btnTag+1);
			aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setScale(2.0);
			_menu ->addChild(aItem,zNum);
        }
        
        showPicMap = ScriptParser::getGroupImageFromPlist(plistDic,"scrollPic");
        showStrMap = ScriptParser::getGroupStringFromPlist(plistDic,"scrollPic");
        
        
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
        
        
        for (int i = 0; i<showPicMap.size(); i++)
        {
            CCSprite *pSprite = CCSprite::create(showPicMap[PersonalApi::convertIntToString(i+1)].c_str());
            pSprite->setTag(123);
            pSprite->setPosition(ccp(scrollPicPosition.x+pSprite->getContentSize().width*i,scrollPicPosition.y));
            this->addChild(pSprite,zNum+1);
            
            const char * labelStr = showStrMap[PersonalApi::convertIntToString(i+1)].c_str();
            float fontSize = ScriptParser::getFontSizeFromPlist(plistDic,"scrollStr");
            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
            pLabel->setTag(234);
            pLabel->setPosition(ccp(pSprite->getPosition().x,pSprite->getPosition().y-pSprite->getContentSize().height/2-10));
            this->addChild(pLabel,zNum+1);
        }
        
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S22PicDetail::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

CCSize S22PicDetail::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
  
    CCSprite *pSprite = CCSprite::create(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str());
    
    const char * labelStr = showStrMap[PersonalApi::convertIntToString(idx)].c_str();
    float fontSize = pSprite->getContentSize().height;
    CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
    
    float size1 = pLabel->getContentSize().height;
    float size2 = pSprite->getContentSize().height;
    return CCSizeMake(table->getContentSize().width, size1+size2);
  
}

CCTableViewCell* S22PicDetail::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCLOG("%s",showPicMap[PersonalApi::convertIntToString(idx+1)].c_str());
        CCSprite *pSprite = CCSprite::create(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str());
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setTag(123);
        pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        
        const char * labelStr = showStrMap[PersonalApi::convertIntToString(idx)].c_str();
        float fontSize = pSprite->getContentSize().height;
        CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
        //pLabel->setAnchorPoint(CCPointZero);
        pLabel->setTag(234);
        pLabel->setPosition(CCPointZero);
        pCell->addChild(pLabel);
    }
    else
    {
        
        CCSprite *pSprite = (CCSprite*)pCell->getChildByTag(123);
        //cocos2d-x 动态修改图片
        pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str()));
        
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(234);
        pLabel->setString(showStrMap[PersonalApi::convertIntToString(idx)].c_str());
        
    }
    
    
    return pCell;
}

unsigned int S22PicDetail::numberOfCellsInTableView(CCTableView *table)
{
    return showPicMap.size();
}

void S22PicDetail::S2menuCallback(CCObject* pSender)
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

void S22PicDetail::S2back(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
  
}
