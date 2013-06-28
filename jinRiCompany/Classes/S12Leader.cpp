//
//  S12Leader.cpp
//  GreTest
//
//  Created by lihex on 6/23/13.
//
//

#include "S12Leader.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"


#define s1FontName_macro "Arial"
#define classPlistName_macro "S12Leader"


using namespace cocos2d;
using namespace std;

CCScene* S12Leader::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S12Leader *layer = S12Leader::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}


bool S12Leader::initInfo2()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        bRet = true;
	} while (0);
    
	return bRet;
}

bool S12Leader::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        CCSprite * showLeftPicture = CCSprite::create("S12GroundImg.png");
        showLeftPicture->setPosition( ScriptParser::getPositionFromPlist(plistDic,"S12LeftPic"));
        this->addChild(showLeftPicture);
        
        
        showPicMap = ScriptParser::getGroupImageFromPlist(plistDic, "showPicture");
        CCPoint showPosition = ScriptParser::getPositionFromPlist(plistDic, "showPicture");
        for(int i = 0; i < showPicMap.size(); i++){
            const char* picName = showPicMap[PersonalApi::convertIntToString(i+1)].c_str();
            CCSprite* pic = CCSprite::create(picName);
            pic->setPosition(ccpAdd(showPosition, ccp(0, -i * 150)));
            this->addChild(pic);
        }
        
        showStrMap = ScriptParser::getGroupStringFromPlist(plistDic, "rightContent");
        CCPoint showContentPos = ScriptParser::getPositionFromPlist(plistDic, "rightContent");
        CCSize demission = ScriptParser::getSizeFromPlist(plistDic, "rightContent");
        float fntSize = ScriptParser::getFontSizeFromPlist(plistDic, "rightContent");
        for(int i = 0; i < showStrMap.size(); i++){
            const char* ctntStr = showStrMap[PersonalApi::convertIntToString(i+1)].c_str();
            CCLabelTTF* label = CCLabelTTF::create(ctntStr, s1FontName_macro, fntSize, demission, kCCTextAlignmentLeft);
            label->setColor(ccc3(128.0,64.0,0.0));
            label->setPosition(ccpAdd(showContentPos, ccp(0, -i * 150)));
            this->addChild(label);
        }
        
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void S12Leader::menuCallback(CCObject* pSender)
{


}