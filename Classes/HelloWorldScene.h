#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Player.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
	std::vector<GameObject*> gameObjList;
	Player* player;
	Label* playerHealth;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event_);
	virtual void onMousePressed(cocos2d::Event* event_);
	virtual void onMouseReleased(cocos2d::Event* event_);

	void update(float delta);

	bool OnContactBegin(PhysicsContact& contact);
};

#endif // __HELLOWORLD_SCENE_H__
