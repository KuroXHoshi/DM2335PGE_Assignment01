#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "ui\UIButton.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
	std::vector<GameObject*> gameObjList;
	Player* player;
	Label* playerHealth;
	CocosDenshion::SimpleAudioEngine *audio;
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


	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);


	void update(float delta);

	bool OnContactBegin(PhysicsContact& contact);
};

#endif // __HELLOWORLD_SCENE_H__
