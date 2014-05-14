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
	auto _nodeSysMenu = SceneReader::getInstance()->createNodeWithSceneFile("sysMenuScene.json");
	this->addChild(_nodeSysMenu);
	auto render = static_cast<ComRender*>(_nodeSysMenu->getChildByTag(10013)->getComponent("GUIComponent"));
	auto widget = static_cast<cocos2d::ui::Widget*>(render->getNode());
	auto btnGame = static_cast<Button*>(widget->getChildByName("btnGame"));
	btnGame->addTouchEventListener(this,toucheventselector(GoBang::touchEventButtonGame));
	auto btnSetting = static_cast<Button*>(widget->getChildByName("btnSetting"));
	btnSetting->addTouchEventListener(this,toucheventselector(GoBang::touchEventButtonSetting));
	auto btnAbout = static_cast<Button*>(widget->getChildByName("btnAbout"));
	btnAbout->addTouchEventListener(this,toucheventselector(GoBang::touchEventButtonAbout));
	
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
	auto scene = Scene::create();
	auto _nodeGame = SceneReader::getInstance()->createNodeWithSceneFile("gameScene.json");
	auto renderGame = static_cast<ComRender*>(_nodeGame->getChildByTag(10011)->getComponent("GUIComponent"));
	auto widgetGame = static_cast<cocos2d::ui::Widget*>(renderGame->getNode());
	auto btnBack = static_cast<Button*>(widgetGame->getChildByName("Button_3"));
	btnBack->addTouchEventListener(this, toucheventselector(GoBang::touchEventButtonBack));
	scene->addChild(_nodeGame);
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}

// btnSetting touch event
void GoBang::touchEventButtonSetting(Ref *pSender, TouchEventType type)
{

}

// btnAbout touch event
void GoBang::touchEventButtonAbout(Ref *pSender, TouchEventType type)
{

}
void GoBang::touchEventButtonBack(Ref *pSender, TouchEventType type)
{
	auto scene = Scene::create();
	auto _nodeSysMenu = SceneReader::getInstance()->createNodeWithSceneFile("sysMenuScene.json");
	auto render = static_cast<ComRender*>(_nodeSysMenu->getChildByTag(10013)->getComponent("GUIComponent"));
	auto widget = static_cast<cocos2d::ui::Widget*>(render->getNode());
	auto btnGame = static_cast<Button*>(widget->getChildByName("btnGame"));
	btnGame->addTouchEventListener(this, toucheventselector(GoBang::touchEventButtonGame));
	scene->addChild(_nodeSysMenu);
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		
		
		Director::getInstance()->replaceScene(scene);

		break;
	default:
		break;
	}
		
}
