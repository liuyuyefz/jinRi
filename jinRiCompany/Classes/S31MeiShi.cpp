//
//  S31MeiShi.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#include "S31MeiShi.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"



#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S31MeiShi"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S31MeiShi::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S31MeiShi *layer = S31MeiShi::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S31MeiShi::initInfo2()
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
bool S31MeiShi::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        CCLayer *pLayer = CCLayer::create();
        pLayer->setAnchorPoint(CCPointZero);
        pLayer->setPosition(CCPointZero);
        
   
        CCSprite * wordPic = CCSprite::create(ScriptParser::getImageFromPlist(plistDic,"wordPic"));
        wordPic->setAnchorPoint(CCPointZero);
        wordPic->setPosition(ccp(0,0));
        pLayer->addChild(wordPic,zNum);
        
        scrollMaxSizeX = wordPic->getContentSize().width;
        scrollMaxSizeY = wordPic->getContentSize().height;
  
        showPicMap = ScriptParser::getGroupImageFromPlist(plistDic,"scrollPic");
        showStrMap = ScriptParser::getGroupStringFromPlist(plistDic,"picIntro");
         float titleEnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"picIntro");
        for (int i  = 0; i<showPicMap.size(); i++)
        {
            for (int j = 0; j<3; j++)
            {
                const char * imageName = showPicMap[PersonalApi::convertIntToString(i+1)].c_str();
                CCMenuItemImage * aItemImage = CCMenuItemImage::create(imageName,
                                                                       imageName,
                                                                       this,
                                                                       menu_selector(S31MeiShi::S31MeiShiCallback));
                aItemImage->setAnchorPoint(CCPointZero);
                aItemImage->setPosition(ccp(wordPic->getPosition().x,wordPic->getPosition().y-30));
                pLayer->addChild(aItemImage,zNum);
           
               
                const char * picIntr = showStrMap[PersonalApi::convertIntToString(i+1)].c_str();
                CCLabelTTF *titleEnLabel = CCLabelTTF::create(picIntr, s1FontName_macro, titleEnFontSize);
                titleEnLabel->setAnchorPoint(CCPointZero);
                titleEnLabel->setPosition(ccp(aItemImage->getPosition().x,aItemImage->getPosition().y-30));
                titleEnLabel->setColor(ccGRAY);
                pLayer->addChild(titleEnLabel,zNum);
                
                scrollMaxSizeY += titleEnLabel->getPosition().y+titleEnLabel->getContentSize().height;
            }
        }
        
        
     
        m_pScrollView = CCScrollView::create(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY), pLayer);
        m_pScrollView->setPosition(ScriptParser::getPositionFromPlist(plistDic,"scrollView"));
        m_pScrollView->setContentOffset(CCPointZero);
        m_pScrollView->setTouchEnabled(true);
        m_pScrollView->setDelegate(this);
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pScrollView->setContentSize(CCSizeMake(wordPic->getContentSize().width, wordPic->getContentSize().height));
        //ScriptParser::getSizeFromPlist(plistDic,"showSize")
        m_pScrollView->setContainer(pLayer);
        this->addChild(m_pScrollView,zNum);
        //S31Product_01.png
        //this->schedule(schedule_selector(S31MeiShi::timer),2.0f);
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S31MeiShi::S31MeiShiCallback(CCObject* pSender)
{
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            //newScene->addChild(S31MeiShi::create());
            
            break;
        case btnTag+1:
            //newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.3, newScene));//动画过场
    
}
bool S31MeiShi::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}
void S31MeiShi::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
void S31MeiShi::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
void S31MeiShi::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
void S31MeiShi::timer(CCTime dt)
{
    countOffSet -=OffSetY;
    m_pScrollView->setContentOffsetInDuration(CCPointMake(0,countOffSet),0.8);
    this->schedule(schedule_selector(S31MeiShi::timer2),0.0,false,0.9);
    //schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
   
}
void S31MeiShi::timer2(CCTime dt)
{
    countOffSet +=OffSetY;
    m_pScrollView->setContentOffset(CCPointMake(0, countOffSet),false);
    
}

