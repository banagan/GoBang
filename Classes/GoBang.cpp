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
	
	do
	{
		Node *root = createSysMenuScene();
		CC_BREAK_IF(!root);
		this->addChild(root);
	} while (0);
	
	return true;
}

cocos2d::Node* GoBang::createSysMenuScene()
{
	std::string sceneFileName = "sysMenuScene.json";
	int tag = 10017;
	auto node = SceneReader::getInstance()->createNodeWithSceneFile(sceneFileName);

	if (node == nullptr)
	{
		return nullptr;
	}

	auto render = static_cast<ComRender*>(node->getChildByTag(tag) -> getComponent("GUIComponent"));
	auto widget = static_cast<Widget*>(render->getNode());

	// Button
	auto btnGame = static_cast<Button*>(widget->getChildByName("btnGame"));
	auto btnSetting = static_cast<Button*>(widget->getChildByName("btnSetting"));
	auto btnAbout = static_cast<Button*>(widget->getChildByName("btnAbout"));

	// touchEvent
	btnGame->addTouchEventListener(btnGame, toucheventselector(GoBang::touchEventButtonGame));
	btnSetting->addTouchEventListener(btnSetting, toucheventselector(GoBang::touchEventButtonSetting));
	btnAbout->addTouchEventListener(btnAbout, toucheventselector(GoBang::touchEventButtonAbout));

	return node;
}

cocos2d::Node* GoBang::createSettingScene()
{
	std::string sceneFileName = "settingScene.json";
	int tag = 10018;
	auto node = SceneReader::getInstance()->createNodeWithSceneFile(sceneFileName);

	if (node == nullptr)
	{
		return nullptr;
	}

	auto render = static_cast<ComRender*>(node->getChildByTag(tag)->getComponent("GUIComponent"));
	auto widget = static_cast<Widget*>(render->getNode());

	return node;
}

cocos2d::Node* GoBang::createAboutScene()
{
	std::string sceneFileName = "aboutScene.json";
	int tag = 10015;
	auto node = SceneReader::getInstance()->createNodeWithSceneFile(sceneFileName);

	if (node == nullptr)
	{
		return nullptr;
	}

	auto render = static_cast<ComRender*>(node->getChildByTag(tag)->getComponent("GUIComponent"));
	auto widget = static_cast<Widget*>(render->getNode());

	return node;
}

cocos2d::Node* GoBang::createGameScene()
{
	std::string sceneFileName = "gameScene.json";
	int tag = 10016;
	auto node = SceneReader::getInstance()->createNodeWithSceneFile(sceneFileName);

	if (node == nullptr)
	{
		return nullptr;
	}

	auto render = static_cast<ComRender*>(node->getChildByTag(tag)->getComponent("GUIComponent"));
	auto widget = static_cast<Widget*>(render->getNode());
	auto btnBack = static_cast<Button*>(widget->getChildByName("btnBack"));
	btnBack->addTouchEventListener(btnBack,toucheventselector(GoBang::touchEventButtonBack));

	return node;
}

// btnGame touch event
void GoBang::touchEventButtonGame(Ref *pSender, TouchEventType type)
{
	auto scene = Scene::create();
	auto node = createGameScene();
	scene->addChild(node);
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
	auto node = createSysMenuScene();
	scene->addChild(node);
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}
