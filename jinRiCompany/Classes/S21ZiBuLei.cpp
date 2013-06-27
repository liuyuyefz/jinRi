//
//  S21ZiBuLei.cpp
//  JinRiCompany
//
//  Created by lyy on 13-6-24.
//
//

#include "S21ZiBuLei.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S22PicDetail.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S21ZiBuLei"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;

CCScene* S21ZiBuLei::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S21ZiBuLei *layer = S21ZiBuLei::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S21ZiBuLei::initInfo2()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = AppDelegate::S2SelectedScene;
        AppDelegate::S2SceneNum = 1;
        bRet = true;
	} while (0);
    
	return bRet;
}
bool S21ZiBuLei::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        picArray = CCArray::createWithCapacity(6);
        labelArray = CCArray::createWithCapacity(NULL);
        
        CCPoint lastPicPosition = ScriptParser::getPositionFromPlist(plistDic,"pic");
        
        float aFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"label");
        map<string, string> labelMap =  ScriptParser::getGroupStringFromPlist(plistDic,"label");
        int indexNum = 0;
        
        for (int i  = 0; i<2; i++)
        {
            for (int j = 0; j<3; j++)
            {
                string picName = "S21Display"+PersonalApi::convertIntToString(indexNum+1)+".png";
                
                CCSprite * aPicture = CCSprite::create(picName.c_str());
               
                
                aPicture->setPosition(ccp(lastPicPosition.x+(aPicture->getContentSize().width+20)*j,lastPicPosition.y-(aPicture->getContentSize().height+80)*i));
              
                this->addChild(aPicture,zNum);
                picArray->addObject(aPicture);
         
                CCSprite * sprite1 = CCSprite::create();
                CCSprite * sprite2 = CCSprite::create();
                
                CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                                   sprite1,
                                                                   sprite2,
                                                                   this,
                                                                   menu_selector(S21ZiBuLei::S21ZiBuLeiMenuCallback));
                aItem->setPosition(aPicture->getPosition());
                aItem->setContentSize(aPicture->getContentSize());
                aItem->setTag(btnTag+i);
                _menu ->addChild(aItem,zNum);
                
                CCSize dimensionsSize = CCSizeMake(aPicture->getContentSize().width, aFontSize);
                CCLabelTTF *aLabel = CCLabelTTF::create(labelMap[PersonalApi::convertIntToString(indexNum+1)].c_str(), s1FontName_macro, aFontSize, dimensionsSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
                aLabel->setPosition(ccp(aPicture->getPosition().x,aPicture->getPosition().y-aPicture->getContentSize().height/2-40));
                aLabel->setColor(ccc3(112.0,16.0,12.0));
                this->addChild(aLabel,zNum);
                labelArray->addObject(aLabel);
                
                indexNum++;
            }
        }
   
        
		bRet = true;
	} while (0);
    
	return bRet;
}
void S21ZiBuLei::S21ZiBuLeiMenuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    switch (aItem->getTag())
    {
        case btnTag+1:
            ;
            break;
        case btnTag+3:

            
            break;
        case btnTag+4:

            
            break;
            
            
        default:
            break;
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S22PicDetail::create());
    CCDirector::sharedDirector()->replaceScene(newScene);
}
