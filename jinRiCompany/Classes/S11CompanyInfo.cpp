//
//  S11CompanyInfo.cpp
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#include "S11CompanyInfo.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"



#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S11CompanyInfo"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S11CompanyInfo::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S11CompanyInfo *layer = S11CompanyInfo::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S11CompanyInfo::initInfo2()
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
bool S11CompanyInfo::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        
        CCSprite * showbigPicture = CCSprite::create("S11BigPic.png");
        showbigPicture->setPosition( ScriptParser::getPositionFromPlist(plistDic,"S11BigPic"));
        this->addChild(showbigPicture,zNum);
		
         m_pScrollView = CCScrollView::create();
        
        showPicMap = ScriptParser::getGroupImageFromPlist(plistDic,"scrollPic");
    
        for (int i  = 0; i<showPicMap.size(); i++)
        {
            allScrollPicMap[PersonalApi::convertIntToString(i+1)]=showPicMap[PersonalApi::convertIntToString(i+1)];
            CCMenuItemImage * aItem = CCMenuItemImage::create(allScrollPicMap[PersonalApi::convertIntToString(i+1)].c_str()
                                                              , allScrollPicMap[PersonalApi::convertIntToString(i+1)].c_str()
                                                              ,this
                                                              ,menu_selector(S11CompanyInfo::S11companyMenuCallback));
            
            aItem->setAnchorPoint(CCPointZero);
            aItem->setPosition(ccp(scrollMaxSizeX,0));
            CCMenu * aMenu = CCMenu::create(NULL);
            aMenu->setPosition(CCPointZero);
            aMenu->addChild(aItem);
            m_pScrollView->addChild(aMenu);
            
            scrollMaxSizeX += aItem->getContentSize().width;
            onePicLineWidth = scrollMaxSizeX;
            picWidthVec.push_back(aItem->getContentSize().width);
            
        }
        for (int i  = 0; i<showPicMap.size(); i++)
        {
            allScrollPicMap[PersonalApi::convertIntToString(i+1)]=showPicMap[PersonalApi::convertIntToString(i+1)];
            CCMenuItemImage * aItem = CCMenuItemImage::create(allScrollPicMap[PersonalApi::convertIntToString(i+1)].c_str()
                                                              , allScrollPicMap[PersonalApi::convertIntToString(i+1)].c_str()
                                                              ,this
                                                              ,menu_selector(S11CompanyInfo::S11companyMenuCallback));
            
            aItem->setAnchorPoint(CCPointZero);
            aItem->setPosition(ccp(scrollMaxSizeX,0));
            CCMenu * aMenu = CCMenu::create(NULL);
            aMenu->setPosition(CCPointZero);
            aMenu->addChild(aItem);
            m_pScrollView->addChild(aMenu);
            
            scrollMaxSizeX += aItem->getContentSize().width;
            picWidthVec.push_back(aItem->getContentSize().width);
        }
        
        picIndex = 0;
        countOffSet = 0;
        OffSetX = 0;
        
        CCSprite * rulerSprite = CCSprite::create(showPicMap["1"].c_str());
      
        m_pScrollView->setPosition(ccp(showbigPicture->getPosition().x-showbigPicture->getContentSize().width/2,showbigPicture->getPosition().y-showbigPicture->getContentSize().height/2-110));//ScriptParser::getPositionFromPlist(plistDic,"scrollView")); //这一步是1.0版本没有的，重要！
        
        CCSize showSize = CCSizeMake(showbigPicture->getContentSize().width, rulerSprite->getContentSize().height);//ScriptParser::getSizeFromPlist(plistDic,"showSize");
        scrollViewWidth = showSize.width;
        m_pScrollView->setViewSize(showSize);//大小要设置得比图片的小
        m_pScrollView->setContentOffset(ccp(0,0));
        m_pScrollView->setContentSize(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY));
        
        //设置滚动方向，
        m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
        m_pScrollView->setDelegate(this);
        this->addChild(m_pScrollView);
        this->schedule(schedule_selector(S11CompanyInfo::timer),2.0);
        
        
        map<string, string> naviGroupStrMap =  ScriptParser::getGroupStringFromPlist(plistDic,"leftDownTitle");
        float fontSize = ScriptParser::getFontSizeFromPlist(plistDic,"leftDownTitle");
        CCSize dimensionsSize = ScriptParser::getSizeFromPlist(plistDic,"leftDownTitle");
        float lastLabelHeight;
        float lastLabelPositionY;
        
        int k = 1;
        for (int i=0; i<naviGroupStrMap.size()/2; i++)
        {
            for (int j = 0; j<2; j++)
            {
                const char * labelStr = naviGroupStrMap[PersonalApi::convertIntToString(k)].c_str();
                
                
                CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize, dimensionsSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
                pLabel->setAnchorPoint(ccp(0.0,1.0));
                pLabel->setPosition(ccp(m_pScrollView->getPosition().x+showbigPicture->getContentSize().width/2*j,m_pScrollView->getPosition().y-pLabel->getContentSize().height*1.2*i-10));
                pLabel->setColor(ccc3(112.0,16.0,12.0));
                this->addChild(pLabel,zNum);
                
                k++;
            }
        }
        
        
         
        showStrMap = ScriptParser::getGroupStringFromPlist(plistDic,"rightTitleTableView");
        
        const char * titleStr = showStrMap[PersonalApi::convertIntToString(1)].c_str();
        float titleFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"rightFirstTitle");
        CCLabelTTF *titleLabel = CCLabelTTF::create(titleStr, s1FontName_macro, titleFontSize);
        titleLabel->setAnchorPoint(ccp(0.0,0.5));
        CCPoint titleLabelPosition = ScriptParser::getPositionFromPlist(plistDic,"rightTitleTableView");
        titleLabel->setPosition(ccp(titleLabelPosition.x+10,showbigPicture->getPosition().y+showbigPicture->getContentSize().height/2-25));
        titleLabel->setColor(ccc3(112.0,16.0,12.0));
        this->addChild(titleLabel,zNum);
        
        dimensionsSize = ScriptParser::getSizeFromPlist(plistDic,"rightTitleTableView");
        lastLabelHeight = titleLabel->getContentSize().height;
        lastLabelPositionY = titleLabel->getPosition().y;
        
        for (int i  = 1; i<showStrMap.size(); i++)
        {
            CCSprite *pSprite = CCSprite::create("S11triangle.png");
            if (1 == i)
            {
                pSprite->setPosition(ccp(titleLabel->getPosition().x+10,lastLabelPositionY-lastLabelHeight-10));
            }
            else
            {
                pSprite->setPosition(ccp(titleLabel->getPosition().x+10,lastLabelPositionY-lastLabelHeight-20));
            }
            
            this->addChild(pSprite,zNum);
            
         
            string spaceStr = " ";
            string labelNoSpaceStr = showStrMap[PersonalApi::convertIntToString(i+1)];
            for (int j = 0; j<3; j++)
            {
                labelNoSpaceStr = spaceStr + labelNoSpaceStr;
            }
            
            const char * labelStr = labelNoSpaceStr.c_str();
            float fontSize = pSprite->getContentSize().height;
            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize, dimensionsSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            pLabel->setAnchorPoint(ccp(0.0,1.0));
            pLabel->setPosition(ccp(pSprite->getPosition().x-5,pSprite->getPosition().y+10));
            pLabel->setColor(ccBLACK);
            this->addChild(pLabel,zNum);
            
            lastLabelHeight = pLabel->getContentSize().height;
            lastLabelPositionY = pLabel->getPosition().y;
        }
        
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S11CompanyInfo::S11companyMenuCallback(CCObject* pSender)
{
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            newScene->addChild(S11CompanyInfo::create());
            
            break;
        case btnTag+1:
            //newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.3, newScene));//动画过场
    
}


void S11CompanyInfo::timer(CCTime dt)
{
    
    OffSetX -= picWidthVec[countOffSet];
    countOffSet++;
   
    m_pScrollView->setContentOffsetInDuration(CCPointMake(OffSetX,0),0.5);

    
    if (countOffSet==picWidthVec.size()/2+1)//OffSetX == -onePicLineWidth)
    {
         m_pScrollView->setContentOffset(ccp(picWidthVec[0],0),true);
        OffSetX = 0;
        countOffSet = 0;
        
        //this->schedule(schedule_selector(S11CompanyInfo::timer),2.0,false,2.0);
    }
   
}
void S11CompanyInfo::timer2(CCTime dt)
{
    /*countOffSet +=OffSetX;
    m_pScrollView->setContentOffset(CCPointMake(0, countOffSet),false);
     */
    
    
}

