//
//  GRETestAppDelegate.cpp
//  GRETest
//
//  Created by lyy on 13-3-26.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"


#include "S11CompanyInfo.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
#define rate_macro 1.5

int AppDelegate::S1NaviSelected = 1;
int AppDelegate::S2LeftSelected = 1;
float AppDelegate::S2Alpha = 0.0;
int AppDelegate::S2SceneNum = 1;
int AppDelegate::S2SelectedScene = 1;
AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(pEGLView);
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    CCSize designSize = CCSizeMake(1024, 768);
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    
    if (screenSize.height > 320)
    {
        CCSize resourceSize = CCSizeMake(1024, 768);
        std::vector<std::string> searchPaths;
        searchPaths.push_back("ipad");
        pFileUtils->setSearchPaths(searchPaths);
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
    
    // turn on display FPS
    //pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    CCScene *pScene = S11CompanyInfo::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);//changeBackGroundDefautColor
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
