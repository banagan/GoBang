#ifndef __SYSMENU_SCENE_H__
#define __SYSMENU_SCENE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

class SysMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::TouchEventType type);
    
    // implement the "static create()" method manually
	CREATE_FUNC(SysMenu);
};

#endif // __HELLOWORLD_SCENE_H__
