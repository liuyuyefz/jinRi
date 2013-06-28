//
//  S111Intro.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#include "S111Intro.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"



#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S111Intro"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;

CCScene* S111Intro::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S111Intro *layer = S111Intro::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S111Intro::initInfo2()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 1;
        
        bRet = true;
	} while (0);
    
	return bRet;
}
bool S111Intro::setUpSubClass2()
{
	bool bRet = false;
	do
	{
       
        CCSprite * LogoPic = CCSprite::create(ScriptParser::getImageFromPlist(plistDic,"LogoPic"));
        LogoPic->setPosition(ScriptParser::getPositionFromPlist(plistDic,"LogoPic"));
        this->addChild(LogoPic,zNum);
        
        CCSprite * wordPic = CCSprite::create(ScriptParser::getImageFromPlist(plistDic,"intro"));
        wordPic->setPosition(ScriptParser::getPositionFromPlist(plistDic,"intro"));
        this->addChild(wordPic,zNum);
        
        
        
        CCSprite * bigPic = CCSprite::create(ScriptParser::getImageFromPlist(plistDic,"bigPic"));
        bigPic->setPosition(ScriptParser::getPositionFromPlist(plistDic,"bigPic"));
        this->addChild(bigPic,zNum);
     
        bRet = true;
	} while (0);
    
	return bRet;
}

void S111Intro::S111IntroCallback(CCObject* pSender)
{
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            //newScene->addChild(S111Intro::create());
            
            break;
        case btnTag+1:
            //newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.3, newScene));//动画过场
    
}


