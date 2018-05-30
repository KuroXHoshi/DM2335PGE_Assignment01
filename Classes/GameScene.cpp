#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

cocos2d::Scene * GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	return true;
}

void GameScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event_)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{

	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{

	}
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event_)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
	}
}

void GameScene::onMousePressed(cocos2d::Event * event_)
{
	EventMouse* e = (EventMouse*)event_;
	if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
	}
}

void GameScene::onMouseReleased(cocos2d::Event * event_)
{
	EventMouse* e = (EventMouse*)event_;
	if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{

	}
}

void GameScene::update(float delta)
{
}
