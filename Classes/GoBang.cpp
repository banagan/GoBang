#include "GoBang.h"

using namespace cocostudio;
using namespace cocos2d::ui;

USING_NS_CC;
int board[15][15] = {0};
int toggleColor = 1;

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
	int tag = 10003;
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
	int tag = 10004;
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
	int tag = 10005;
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
	int tag = 10006;
	auto node = SceneReader::getInstance()->createNodeWithSceneFile(sceneFileName);

	if (node == nullptr)
	{
		return nullptr;
	}

	auto render = static_cast<ComRender*>(node->getChildByTag(tag)->getComponent("GUIComponent"));
	auto widget = static_cast<Widget*>(render->getNode());
	auto imgBoard = static_cast<ImageView*>(widget->getChildByName("imgBoard"));
	auto btnBack = static_cast<Button*>(widget->getChildByName("btnBack"));
	for (int i = 0; i <= 14; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			board[i][j] = 0;
		}
	}
	imgBoard->addTouchEventListener(imgBoard, toucheventselector(GoBang::touchEventImageBoard));
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

// btnBack touch event
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
// imgBoard touch event
void GoBang::touchEventImageBoard(Ref *pSender, TouchEventType type)
{
	auto imgBoard = static_cast<ImageView*>(pSender);
	auto point = imgBoard->getTouchStartPos();
	auto spriteBlack = Sprite::create("black.png");
	auto spriteWhite = Sprite::create("white.png");
	int x = (int)(point.x / 30 + 0.5) * 30;
	int y = (int)(point.y / 30 + 0.5) * 30;
	int i = (x - 30) / 30;
	int j = (y - 90) / 30;
	int result = 0;
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		if (board[i][j] == 0 && toggleColor == 1)//no chess piece
		{
			addChild(spriteBlack);
			spriteBlack->setPosition(Point(x - 30, y - 90));
			toggleColor = -1;
			board[i][j] = 1;
			CCLog("%f,%f,%d,%d,%d,%d,%d", point.x, point.y, x, y, i, j, board[i][j]);
			for (int k = 0; board[i][j + k] == 1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k <= 4 && result < 5; k++)
			{
				result = result + board[i][j + k];
			}
			for (int k = -1; board[i][j + k] == 1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k >= -4 && result < 5; k--)
			{
				result = result + board[i][j + k];
			}
			// ˙≈≈ºÏ≤‚
			if (result < 5)
			{
				result = 0;
				for (int k = 0; board[i + k][j] == 1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k <= 4 && result < 5; k++)
				{
					result = result + board[i + k][j];
				}
				for (int k = -1; board[i + k][j] == 1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k >= -4 && result != 5; k--)
				{
					result = result + board[i + k][j];
				}

				//∫·≈≈º‡≤‚
				if (result < 5)
				{
					result = 0;
					for (int k = 0; board[i + k][j + k] == 1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k <= 4 && result < 5; k++)
					{
						result = result + board[i + k][j + k];
					}
					for (int k = -1; board[i + k][j + k] == 1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k >= -4 && result < 5; k--)
					{
						result = result + board[i + k][j + k];
					}
					if (result <5)
					{
						result = 0;
						for (int k = 0; board[i + k][j - k] == 1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k <= 4 && result < 5; k++)
						{
							result = result + board[i + k][j - k];
						}
						for (int k = -1; board[i + k][j - k] == 1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k >= -4 && result < 5; k--)
						{
							result = result + board[i + k][j - k];
						}
					}
				}
			}
			//∂‘Ω«œﬂº‡≤‚

			if (result >= 5)
			{
				auto spriteBlackWin = Sprite::create("blackWin.png");
				addChild(spriteBlackWin);
				spriteBlackWin->setPosition(Point(240,300));
				CCLog("win");

			}
			else 
			{
				CCLog("continue");
			}
			break;
		}
		if (board[i][j] == 0 && toggleColor == -1)
		{
			addChild(spriteWhite);
			spriteWhite->setPosition(Point(x - 30, y - 90));
			toggleColor = 1;
			board[i][j] = -1;
			CCLog("%f,%f,%d,%d,%d,%d,%d", point.x, point.y, x, y, i, j, board[i][j]);
			for (int k = 0; board[i][j + k] == -1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k <= 4 && result > -5; k++)
			{
				result = result + board[i][j + k];
			}
			for (int k = -1; board[i][j + k] == -1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k >= -4 && result > -5; k--)
			{
				result = result + board[i][j + k];
			}
			// ˙≈≈ºÏ≤‚
			if (result > -5)
			{
				result = 0;
				for (int k = 0; board[i + k][j] == -1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k <= 4 && result > -5; k++)
				{
					result = result + board[i + k][j];
				}
				for (int k = -1; board[i + k][j] == -1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k >= -4 && result > -5; k--)
				{
					result = result + board[i + k][j];
				}

				//∫·≈≈º‡≤‚
				if (result > -5)
				{
					result = 0;
					for (int k = 0; board[i + k][j + k] == -1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k <= 4 && result > -5; k++)
					{
						result = result + board[i + k][j + k];
					}
					for (int k = -1; board[i + k][j + k] == -1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k >= -4 && result > -5; k--)
					{
						result = result + board[i + k][j + k];
					}
					if (result > -5)
					{
						result = 0;
						for (int k = 0; board[i + k][j - k] == -1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k <= 4 && result > -5; k++)
						{
							result = result + board[i + k][j - k];
						}
						for (int k = -1; board[i + k][j - k] == -1 && i <= 14 && i >= 0 && j <= 14 && j >= 0 && k >= -4 && result > -5; k--)
						{
							result = result + board[i + k][j - k];
						}
					}
				}
			}
			//∂‘Ω«œﬂº‡≤‚
			if (result <= -5)
			{
				CCLog("win");
				auto spriteWhiteWin = Sprite::create("whiteWin.png");
				addChild(spriteWhiteWin);
				spriteWhiteWin->setPosition(Point(240,300));
			}
			else
			{
				CCLog("continue");
			}
			break;
		}
	default:
		break;
	}
}
