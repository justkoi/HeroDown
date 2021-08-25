#include "stdafx.h"


USING_NS_CC;

CCSize g_PhoneSize;

typedef struct tagResource

{

    cocos2d::CCSize size;

    char directory[100];

}Resource;




static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };

static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };

static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };





static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(D_PHONE_WIDTH, D_PHONE_HEIGHT);


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

	//glview->setFrameSize((D_SCREEN_SCALE_WIDTH(100)), (D_SCREEN_SCALE_HEIGHT(100)));
	
	srand((unsigned int)time(NULL));
	g_PhoneSize = glview->getFrameSize();

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(D_PHONE_WIDTH * 1.0, D_PHONE_HEIGHT * 1.0);
#endif
	glview->setDesignResolutionSize(D_SCREEN_SCALE_WIDTH(100), D_SCREEN_SCALE_HEIGHT(100),kResolutionNoBorder);
	
    // turn on display FPS
    director->setDisplayStats(true);
	//director->set



    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
