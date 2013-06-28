//
//  S311Detail.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#include "S311Detail.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"


#include "S111Intro.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S311Detail"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S311Detail::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S311Detail *layer = S311Detail::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S311Detail::initInfo2()
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
bool S311Detail::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        
        m_pScrollView = CCScrollView::create();
        
        CCSprite * wordPic = CCSprite::create(ScriptParser::getImageFromPlist(plistDic,"S31TitleImg"));
        wordPic->setPosition(ScriptParser::getPositionFromPlist(plistDic,"scrollView"));
        this->addChild(wordPic,zNum);
        
        scrollMaxSizeX = wordPic->getContentSize().width;
        scrollMaxSizeY = wordPic->getContentSize().height;
        
        
        
        m_pScrollView->setPosition(ScriptParser::getPositionFromPlist(plistDic,"scrollView")); //这一步是1.0版本没有的，重要！
        m_pScrollView->setContentOffset(ccp(0,0));
        CCSize showSize = wordPic->getContentSize();//ScriptParser::getSizeFromPlist(plistDic,"showSize");
        m_pScrollView->setViewSize(CCSizeMake(scrollMaxSizeX, showSize.height));//大小要设置得比图片的小
        m_pScrollView->setContentSize(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY));
        
        //设置滚动方向，
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pScrollView->setDelegate(this);
        this->addChild(m_pScrollView);
        
        
        showPicMap = ScriptParser::getGroupImageFromPlist(plistDic,"scrollPic");
        showStrMap = ScriptParser::getGroupStringFromPlist(plistDic,"picIntro");
        float titleEnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"picIntro");
        int indexNum = 1;
        imagemenu = CCMenu::create(NULL);
        imagemenu->setPosition(CCPointZero);
        for (int i  = 0; i<showPicMap.size()/3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                const char * imageName = showPicMap[PersonalApi::convertIntToString(indexNum)].c_str();
                CCMenuItemImage * aItemImage = CCMenuItemImage::create(imageName,
                                                                       imageName,
                                                                       this,
                                                                       menu_selector(S311Detail::S311DetailCallback));
                
                aItemImage->setPosition(ccp(170+(aItemImage->getContentSize().width+110)*j,wordPic->getPosition().y-90-wordPic->getContentSize().height-(aItemImage->getContentSize().height+70)*i));
                _menu->addChild(aItemImage,zNum);
                aItemImage->setTag(btnTag+indexNum);
                
                const char * picIntr = showStrMap[PersonalApi::convertIntToString(indexNum)].c_str();
                CCLabelTTF *titleEnLabel = CCLabelTTF::create(picIntr, s1FontName_macro, titleEnFontSize);
                titleEnLabel->setPosition(ccp(aItemImage->getPosition().x,aItemImage->getPosition().y-100));
                titleEnLabel->setColor(ccc3(112,16,12));
                this->addChild(titleEnLabel,zNum);
                
                scrollMaxSizeY += aItemImage->getContentSize().height + 70 + aItemImage->getPosition().y-50;
                
                indexNum++;
                if (indexNum == showPicMap.size())
                {
                    scrollMaxSizeY = -(titleEnLabel->getPosition().y-titleEnLabel->getContentSize().height);
                }
                
            }
        }
        
        
        //S31Product_01.png
        //this->schedule(schedule_selector(S311Detail::timer),2.0f);
        /*
         showPicMap = ScriptParser::getGroupImageFromPlist(plistDic,"scrollPic");
         showStrMap = ScriptParser::getGroupStringFromPlist(plistDic,"picIntro");
         
         
         CCSize scrollPicSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
         CCPoint scrollPicPosition = ScriptParser::getPositionFromPlist(plistDic,"scrollView");
         pTableView = CCTableView::create(this, scrollPicSize);
         pTableView->setDirection(kCCScrollViewDirectionVertical);
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

void S311Detail::S311DetailCallback(CCObject* pSender)
{
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag+1:
            newScene->addChild(S111Intro::create());
            
            break;
        case btnTag+2:
            newScene->addChild(S111Intro::create());
            
            break;
            
        default:
            break;
    }
    newScene->addChild(S111Intro::create());
    CCDirector::sharedDirector()->replaceScene(newScene);//动画过场
    
}

bool S311Detail::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}
void S311Detail::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
void S311Detail::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
void S311Detail::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
void S311Detail::timer(CCTime dt)
{
    countOffSet -=OffSetY;
    m_pScrollView->setContentOffsetInDuration(CCPointMake(0,countOffSet),0.8);
    this->schedule(schedule_selector(S311Detail::timer2),0.0,false,0.9);
    //schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
    
}
void S311Detail::timer2(CCTime dt)
{
    countOffSet +=OffSetY;
    m_pScrollView->setContentOffset(CCPointMake(0, countOffSet),false);
    
}

/*
 void S311Detail::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
 {
 CCLog("cell touched at index: %i", cell->getIdx());
 }
 
 CCSize S311Detail::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
 {
 
 CCSprite * wordPic = CCSprite::create(ScriptParser::getImageFromPlist(plistDic,"wordPic"));
 scrollMaxSizeX = wordPic->getContentSize().width;
 scrollMaxSizeY = wordPic->getContentSize().height;
 
 float titleEnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"picIntro");
 int indexNum = 1;
 imagemenu = CCMenu::create(NULL);
 imagemenu->setPosition(CCPointZero);
 for (int i  = 0; i<showPicMap.size()/3; i++)
 {
 for (int j = 0; j<3; j++)
 {
 const char * imageName = showPicMap[PersonalApi::convertIntToString(indexNum+1)].c_str();
 CCMenuItemImage * aItemImage = CCMenuItemImage::create(imageName,
 imageName,
 this,
 menu_selector(S311Detail::S311DetailCallback));
 
 aItemImage->setPosition(ccp(wordPic->getPosition().x+aItemImage->getContentSize().width*j,wordPic->getPosition().y-wordPic->getContentSize().height-(aItemImage->getContentSize().height+70)*i));
 //m_pScrollView->addChild(aItemImage,zNum);
 
 
 const char * picIntr = showStrMap[PersonalApi::convertIntToString(indexNum+1)].c_str();
 CCLabelTTF *titleEnLabel = CCLabelTTF::create(picIntr, s1FontName_macro, titleEnFontSize);
 titleEnLabel->setPosition(ccp(aItemImage->getPosition().x,aItemImage->getPosition().y-50));
 titleEnLabel->setColor(ccc3(112,16,12));
 //m_pScrollView->addChild(titleEnLabel,zNum);
 
 //scrollMaxSizeY += aItemImage->getContentSize().height + 70 + aItemImage->getPosition().y-50;
 
 indexNum++;
 
 if (indexNum == showPicMap.size())
 {
 scrollMaxSizeY = (titleEnLabel->getPosition().y-titleEnLabel->getContentSize().height);
 }
 
 }
 }
 CCLOG("%d",scrollMaxSizeY);
 return CCSizeMake(scrollMaxSizeX, 100);
 
 }
 
 CCTableViewCell* S311Detail::tableCellAtIndex(CCTableView *table, unsigned int idx)
 {
 
 CCTableViewCell *pCell = table->dequeueCell();
 if (!pCell)
 {
 
 pCell = new CCTableViewCell();
 pCell->autorelease();
 CCSprite * wordPic = CCSprite::create(ScriptParser::getImageFromPlist(plistDic,"wordPic"));
 wordPic->setPosition(CCPointZero);
 pCell->addChild(wordPic,zNum);
 
 float titleEnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"picIntro");
 int indexNum = 1;
 imagemenu = CCMenu::create(NULL);
 imagemenu->setPosition(CCPointZero);
 for (int i  = 0; i<showPicMap.size()/3; i++)
 {
 for (int j = 0; j<3; j++)
 {
 const char * imageName = showPicMap[PersonalApi::convertIntToString(indexNum+1)].c_str();
 CCMenuItemImage * aItemImage = CCMenuItemImage::create(imageName,
 imageName,
 this,
 menu_selector(S311Detail::S311DetailCallback));
 
 aItemImage->setPosition(ccp(wordPic->getPosition().x+aItemImage->getContentSize().width*j,wordPic->getPosition().y-wordPic->getContentSize().height-(aItemImage->getContentSize().height+70)*i));
 pCell->addChild(aItemImage,zNum);
 
 
 const char * picIntr = showStrMap[PersonalApi::convertIntToString(indexNum+1)].c_str();
 CCLabelTTF *titleEnLabel = CCLabelTTF::create(picIntr, s1FontName_macro, titleEnFontSize);
 titleEnLabel->setPosition(ccp(aItemImage->getPosition().x,aItemImage->getPosition().y-50));
 titleEnLabel->setColor(ccc3(112,16,12));
 pCell->addChild(titleEnLabel,zNum);
 //scrollMaxSizeY += aItemImage->getContentSize().height + 70 + aItemImage->getPosition().y-50;
 
 indexNum++;
 
 if (indexNum == showPicMap.size())
 {
 scrollMaxSizeY = -(titleEnLabel->getPosition().y-titleEnLabel->getContentSize().height);
 }
 
 }
 }
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
 
 unsigned int S311Detail::numberOfCellsInTableView(CCTableView *table)
 {
 return 1;
 }
 */
