//
//  S2ZiBu.cpp
//  JinRiCompany
//
//  Created by lyy on 13-6-24.
//
//

#include "S2ZiBu.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"


#include "S21ZiBuLei.h"
#include "S22PicDetail.h"
#include "S23DetailIntro.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S2ZiBu"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;

bool S2ZiBu::initInfo()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        /*
        if (2 != CCUserDefault::sharedUserDefault()->getIntegerForKey("firstIn"))
        {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("leftSelected",1);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("firstIn", 2);
        }
        else
        {
            leftSelected = CCUserDefault::sharedUserDefault()->getStringForKey("leftSelected");
        }
        */
        
        CC_BREAK_IF(!initInfo2());
        
        bRet = true;
	} while (0);
    
	return bRet;
}
bool S2ZiBu::setUpSubClass()
{
	bool bRet = false;
	do
	{
        float firstStrFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"firstTitle");
        CCLabelTTF *firstTitleLabel = CCLabelTTF::create(ScriptParser::getStringFromPlist(plistDic,"firstTitle"), s1FontName_macro, firstStrFontSize);
        firstTitleLabel->setColor(ccc3(193.0,159.0,113.0));
        firstTitleLabel->setPosition(ScriptParser::getPositionFromPlist(plistDic,"firstTitle"));
         this->addChild(firstTitleLabel,zNum+1);
        
        CCSprite * S1PSubBottomSprite = CCSprite::create("S1PSubBottom.png");
        S1PSubBottomSprite->setPosition( ccp(origin.x+visibleSize.width/2,firstTitleLabel->getPosition().y-firstTitleLabel->getContentSize().height/2-10));
        this->addChild(S1PSubBottomSprite,zNum);
        
        
        map<string, string> naviGroupStrMap =  ScriptParser::getGroupStringFromPlist(plistDic,"naviTitle");
        float naviFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"naviTitle");
        CCPoint naviStrPosition = ScriptParser::getPositionFromPlist(plistDic,"naviTitle");
        
        for (int i=0; i<naviGroupStrMap.size(); i++)
        {
            const char * labelStr = naviGroupStrMap[PersonalApi::convertIntToString(i+1)].c_str();

            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, naviFontSize);
            pLabel->setPosition(ccp(naviStrPosition.x+(pLabel->getContentSize().width+80)*i,naviStrPosition.y));
            pLabel->setColor(ccc3(128.0,128.0,128.0));
            this->addChild(pLabel,zNum+1);
            
            if (AppDelegate::S2SelectedScene == i+1)
            {
                pLabel->setColor(ccc3(255.0,255.0,255.0));
                CCSprite * selectFrameSprite = CCSprite::create("PSubNavBackground.png");
                selectFrameSprite ->setPosition(pLabel->getPosition());
                this->addChild(selectFrameSprite,zNum);
            }

            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S2ZiBu::menuCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(pLabel->getPosition());
            aItem->setContentSize(pLabel->getContentSize());
            aItem->setTag(btnTag+i+1);
			_menu ->addChild(aItem,zNum);
           
        }
        
       leftNaviGroupStrMap =  ScriptParser::getGroupStringFromPlist(plistDic,"leftNaviTitle");
        map<string, string> leftNaviTitlePicGroupStrMap =  ScriptParser::getGroupImageFromPlist(plistDic,"leftNaviTitlePic");
        float leftNaviTitleFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"leftNaviTitle");
        CCPoint leftNaviTitlePosition = ScriptParser::getPositionFromPlist(plistDic,"leftNaviTitle");
        CCPoint leftNaviTitlePicPosition = ScriptParser::getPositionFromPlist(plistDic,"leftNaviTitlePic");
  
        
        for (int i=0; i<leftNaviGroupStrMap.size(); i++)
        {
            const char * labelStr = leftNaviGroupStrMap[PersonalApi::convertIntToString(i+1)].c_str();
            
            float fontSize = leftNaviTitleFontSize;
            
            CCLabelTTF *leftNaviTitleLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
            leftNaviTitleLabel->setPosition(ccp(leftNaviTitlePosition.x,leftNaviTitlePosition.y-(leftNaviTitleLabel->getContentSize().height+20)*i));
           
            leftNaviTitleLabel->setColor(ccc3(117.0,117.0,116.0));
           
            this->addChild(leftNaviTitleLabel,zNum+1);
            
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S2ZiBu::leftMenuCallback));
			aItem->setTag(btnTag+i+1);
			aItem->setPosition(leftNaviTitleLabel->getPosition());
            aItem->setContentSize(leftNaviTitleLabel->getContentSize());
			_menu ->addChild(aItem,zNum);
            
            
            const char * imageName = leftNaviTitlePicGroupStrMap[PersonalApi::convertIntToString(i+1)].c_str();
            
            CCSprite * leftNaviTitlePicSprite = CCSprite::create(imageName);
            leftNaviTitlePicSprite->setPosition(ccp(leftNaviTitlePicPosition.x-40,leftNaviTitleLabel->getPosition().y));
            this->addChild(leftNaviTitlePicSprite,zNum+1);
            
            if (AppDelegate::S2LeftSelected-1 == i)
            {
                selectedSprite = CCSprite::create("S21SideNavBackground.png");
                selectedSprite->setPosition(leftNaviTitleLabel->getPosition());
                this->addChild(selectedSprite,zNum+1);
            }
            
        }
       
        {
            CCSprite * aSprite = CCSprite::create("S2PSideNavBottomImg.png");
            aSprite->setPosition(ScriptParser::getPositionFromPlist(plistDic,"S2PSideNavBottomImg"));
            this->addChild(aSprite,zNum);
        }
       
        float lastIntrTitleFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"lastIntrTitle");
        shangPinLabel = CCLabelTTF::create("介绍", s1FontName_macro, lastIntrTitleFontSize);
        shangPinLabel->setColor(ccc3(128.0,128.0,128.0));
        shangPinLabel->setAnchorPoint(ccp(1.0,0.5));
        shangPinLabel->setPosition(ccp(S1PSubBottomSprite->getPosition().x+ S1PSubBottomSprite->getContentSize().width/2, firstTitleLabel->getPosition().y-firstTitleLabel->getContentSize().height/4));
        this->addChild(shangPinLabel,zNum+1);
        
        std::string selectedStr = leftNaviGroupStrMap[PersonalApi::convertIntToString(AppDelegate::S2LeftSelected+1)];//"冬虫夏草";
        colorLabel = CCLabelTTF::create(selectedStr.c_str(), s1FontName_macro, lastIntrTitleFontSize);
        colorLabel->setColor(ccc3(193.0,159.0,113.0));
        colorLabel->setAnchorPoint(ccp(1.0,0.5));
        colorLabel->setPosition(ccp(shangPinLabel->getPosition().x-shangPinLabel->getContentSize().width, shangPinLabel->getPosition().y));
        this->addChild(colorLabel,zNum+1);
        
        {
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S2ZiBu::introCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(colorLabel->getPosition());
            aItem->setContentSize(colorLabel->getContentSize());
            aItem->setScale(2.0);
			_menu ->addChild(aItem,zNum);
        }
        
        introLabel = CCLabelTTF::create("尚品", s1FontName_macro, lastIntrTitleFontSize);
        introLabel->setColor(ccc3(128.0,128.0,128.0));
        introLabel->setAnchorPoint(ccp(1.0,0.5));
        introLabel->setPosition(ccp(colorLabel->getPosition().x-colorLabel->getContentSize().width, colorLabel->getPosition().y));
        this->addChild(introLabel,zNum+1);
        
         introSeleSprite = CCSprite::create("PSubNavBackground.png");
        introSeleSprite ->setPosition(ccp(introLabel->getPosition().x+20,introLabel->getPosition().y));
        introSeleSprite->setOpacity(AppDelegate::S2Alpha);
         this->addChild(introSeleSprite,zNum);
        
        
        CC_BREAK_IF(! setUpSubClass2());
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S2ZiBu::menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
     AppDelegate::S2Alpha = 0.0;
    

    switch (aItem->getTag())
    {
        case btnTag+1:
            if (1==AppDelegate::S2SceneNum)
            {
                newScene->addChild(S21ZiBuLei::create());
            }
            else if(2==AppDelegate::S2SceneNum)
            {
                newScene->addChild(S22PicDetail::create());
                
            }
            else
            {
                newScene->addChild(S23DetailIntro::create());
            }
            AppDelegate::S2SelectedScene = 1;
            break;
        case btnTag+2:
            if (1==AppDelegate::S2SceneNum)
            {
                newScene->addChild(S21ZiBuLei::create());
            }
            else if(2==AppDelegate::S2SceneNum)
            {
                newScene->addChild(S22PicDetail::create());
                
            }
            else
            {
                newScene->addChild(S23DetailIntro::create());
            }
            AppDelegate::S2SelectedScene = 2;
            break;
        case btnTag+3:
            if (1==AppDelegate::S2SceneNum)
            {
                newScene->addChild(S21ZiBuLei::create());
            }
            else if(2==AppDelegate::S2SceneNum)
            {
                newScene->addChild(S22PicDetail::create());
                
            }
            else
            {
                newScene->addChild(S23DetailIntro::create());
            }
            AppDelegate::S2SelectedScene = 3;
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.5, newScene));//动画过场
}


void S2ZiBu::leftMenuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;

    AppDelegate::S2LeftSelected = aItem->getTag()-btnTag;
    CCMoveTo* moveLeft=CCMoveTo::create(0.08, aItem->getPosition());
    selectedSprite->runAction(moveLeft);
    
    for (int i = 0; i<leftNaviGroupStrMap.size(); i++)
    {
        if (aItem->getTag() == btnTag+i+1)
        {
            std::string selectedStr = leftNaviGroupStrMap[PersonalApi::convertIntToString(i+1)];//"冬虫夏草";
            colorLabel ->setString(selectedStr.c_str());
            colorLabel->setPosition(ccp(shangPinLabel->getPosition().x-shangPinLabel->getContentSize().width, shangPinLabel->getPosition().y));
            
            introLabel->setPosition(ccp(colorLabel->getPosition().x-colorLabel->getContentSize().width, colorLabel->getPosition().y));
            return;
        }
    }
 
}

void S2ZiBu::introCallback(CCObject* pSender)
{
    AppDelegate::S2Alpha = 255.0;
    CCScene *newScene = CCScene::create();
    newScene->addChild(S23DetailIntro::create());
    CCDirector::sharedDirector()->replaceScene(newScene);//动画过场  
}

