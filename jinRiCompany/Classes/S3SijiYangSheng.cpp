//
//  S3SijiYangSheng.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#include "S3SijiYangSheng.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S31MeiShi.h"
#include "S32XiaoTieShi.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S3SijiYangSheng"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;

bool S3SijiYangSheng::initInfo()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());

        CC_BREAK_IF(!initInfo2());
        
        bRet = true;
	} while (0);
    
	return bRet;
}
bool S3SijiYangSheng::setUpSubClass()
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
                selectFrameSprite->setScaleX(pLabel->getContentSize().width/selectFrameSprite->getContentSize().width);
                this->addChild(selectFrameSprite,zNum);
            }
            
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S3SijiYangSheng::menuCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(pLabel->getPosition());
            aItem->setContentSize(pLabel->getContentSize());
            aItem->setTag(btnTag+i+1);
			_menu ->addChild(aItem,zNum);
            
        }
        
        const char * imageName = "S31Back.png";
        CCMenuItemImage * aItemImage = CCMenuItemImage::create(imageName,
                                                               imageName,
                                                               this,
                                                               menu_selector(S3SijiYangSheng::back));
        
        aItemImage->setPosition(ScriptParser::getPositionFromPlist(plistDic, "back"));
        _menu->addChild(aItemImage,zNum);
        
        
        CC_BREAK_IF(! setUpSubClass2());
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S3SijiYangSheng::menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    AppDelegate::S2Alpha = 0.0;
    
    
    switch (aItem->getTag())
    {
        case btnTag+1:
            newScene->addChild(S31MeiShi::create());
            break;
        case btnTag+2:
            newScene->addChild(S32XiaoTieShi::create());
            break;
        case btnTag+3:
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.5, newScene));//动画过场
}

void S3SijiYangSheng::back(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();

    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.5, newScene));//动画过场
}
