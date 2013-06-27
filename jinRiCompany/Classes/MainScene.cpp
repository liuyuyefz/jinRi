#include "MainScene.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S11CompanyInfo.h"
#include "S21ZiBuLei.h"
#include "S31MeiShi.h"
#include "S41Detail.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"
#define classPlistName_macro "Main"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;


bool Main::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
        
        
		//每个项目都要创建的东西

		_menu = CCMenu::create(NULL);
		_menu->setPosition(CCPointZero);

		this->addChild(_menu, zNum+1);
        
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        CC_BREAK_IF(!initInfo());
        
		//控件
        CCSprite * NaviBg = CCSprite::create("PNavBar.png");
        NaviBg->setAnchorPoint(ccp(0.0,1.0));
        NaviBg->setPosition(ccp(origin.x,origin.y+visibleSize.height-20));
        this->addChild(NaviBg,zNum);
        
        CCSprite * footBar = CCSprite::create("PFootBar.png");
        footBar->setAnchorPoint(ccp(0.0,0.0));
        footBar->setPosition(ccp(origin.x,origin.y));
        this->addChild(footBar,zNum);
        
        {
            const char * labelStr = ScriptParser::getStringFromPlist(plistDic,"PFootBar");
            float fontSize = ScriptParser::getFontSizeFromPlist(plistDic,"PFootBar");
            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
            CCPoint labelPoint = ScriptParser::getPositionFromPlist(plistDic,"PFootBar");
            pLabel->setPosition(ccp(origin.x+visibleSize.width/2,labelPoint.y));
            pLabel->setColor(ccc3(255.0,255.0,255.0));
            this->addChild(pLabel,zNum);
        }
		
        {
			CCSprite * aSprite = CCSprite::create("PLogoOne.png");
			aSprite->setPosition( ScriptParser::getPositionFromPlist(plistDic,"PLogoOne"));
			this->addChild(aSprite,zNum);
		}
        {
			CCSprite * aSprite = CCSprite::create("PLogoTwo.png");
			aSprite->setPosition( ScriptParser::getPositionFromPlist(plistDic,"PLogoTwo"));
			this->addChild(aSprite,zNum);
		}
        
        map<string, string> naviGroupStrMap =  ScriptParser::getGroupStringFromPlist(plistDic,"naviTitle");
        float fontSize = ScriptParser::getFontSizeFromPlist(plistDic,"naviTitle");
        CCPoint naviStrPosition = ScriptParser::getPositionFromPlist(plistDic,"naviTitle");
        
        for (int i=0; i<naviGroupStrMap.size(); i++)
        {
            const char * labelStr = naviGroupStrMap[PersonalApi::convertIntToString(i+1)].c_str();
        
            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
            //(labelStr, s1FontName_macro, fontSize, dimensions, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            pLabel->setPosition(ccp(naviStrPosition.x+pLabel->getContentSize().width*1.6*i,naviStrPosition.y));
            if (AppDelegate::S1NaviSelected == i+1)
            {
                 pLabel->setColor(ccc3(199.0,195.0,0.0));
                
            }
            else
            {
               pLabel->setColor(ccc3(255.0,255.0,255.0));
            }
            
            this->addChild(pLabel,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(Main::menuCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(pLabel->getPosition());
            aItem->setContentSize(pLabel->getContentSize());
            aItem->setTag(btnTag+i);
			_menu ->addChild(aItem,zNum);

            
            
            if(i!=naviGroupStrMap.size()-1)
            {
                CCSprite * aSprite = CCSprite::create("PNavStall.png");
                aSprite->setPosition(ccp(pLabel->getPosition().x+pLabel->getContentSize().width/2+10,pLabel->getPosition().y));
                this->addChild(aSprite,zNum);
            }
        }
        
       CC_BREAK_IF(! setUpSubClass());
        
		bRet = true;
	} while (0);

	return bRet;
}



void Main::menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            AppDelegate::S1NaviSelected = 1;
            AppDelegate::S2LeftSelected = 1;
            newScene->addChild(S11CompanyInfo::create());
            
            break;
        case btnTag+1:
            AppDelegate::S1NaviSelected = 2;
            newScene->addChild(S21ZiBuLei::create());
            
            break;
            
        case btnTag+2:
            AppDelegate::S2LeftSelected = 1;
             AppDelegate::S1NaviSelected = 3;
             newScene->addChild(S31MeiShi::create());
            
            break;
            
        case btnTag+3:
            AppDelegate::S2LeftSelected = 1;
            AppDelegate::S1NaviSelected = 4;
            newScene->addChild(S41Detail::create());
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(newScene);//动画过场

}
