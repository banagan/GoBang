#include "GoBang.h"

using namespace cocostudio;
using namespace cocos2d::ui;

USING_NS_CC;

Scene* GoBang::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GoBang::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GoBang::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    return true;
}


void GoBang::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// btnGame touch event
void GoBang::touchEventButtonGame(Ref *pSender, TouchEventType type)
{

}

// btnSetting touch event
void GoBang::touchEventButtonSetting(Ref *pSender, TouchEventType type)
{

}

// btnAbout touch event
void GoBang::touchEventButtonAbout(Ref *pSender, TouchEventType type)
{

}
