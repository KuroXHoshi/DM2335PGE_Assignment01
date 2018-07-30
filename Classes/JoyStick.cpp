#include "JoyStick.h"


JoyStick* JoyStick::s_instance = nullptr;
JoyStick::JoyStick()
{
}


JoyStick::~JoyStick()
{
}

void JoyStick::init(cocos2d::Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->hudLayer = layer;
	
	joystick_bg_left = Node::create();
	joystick_bg_left->setName("joystick_bg_left");
	
	auto joystick_bg_leftSprite = Sprite::create("textures/ui_joystick_bg.tga");
	joystick_bg_leftSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	joystick_bg_leftSprite->setPosition(Vec2(visibleSize.width * 0.15, visibleSize.height * 0.2));
	joystick_bg_leftSprite->setName(joystick_bg_left->getName() + "sprite");
	joystick_bg_leftSprite->retain();
	joystick_bg_left->addChild(joystick_bg_leftSprite);

	layer->addChild(joystick_bg_left);

	eventListenerTouch = EventListenerTouchOneByOne::create();

	eventListenerTouch->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	eventListenerTouch->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	eventListenerTouch->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);
	eventListenerTouch->onTouchCancelled = CC_CALLBACK_2(JoyStick::onTouchCancelled, this);
	//layer->_eventDispatcher->addEventListenerWithSceneGraphPriority(JoyStick::GetInstance()->GetEventListenerTouch(), this);
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(JoyStick::GetInstance()->GetEventListenerTouch(), layer);

}

void JoyStick::AttachPlayer(Player* _player)
{
	player = _player;
}

JoyStick* JoyStick::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new JoyStick();
	}
	return s_instance;
}

bool JoyStick::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	cocos2d::log("touch began");
	EventTouch* e = (EventTouch*)event;
	float distance = ((joystick_bg_left->getChildByName("joystick_bg_leftsprite")->getPosition()).distance(touch->getLocation()));

	Vec2 hudpos = hudLayer->getPosition();
	Vec2 theJoyPos = joystick_bg_left->getChildByName("joystick_bg_leftsprite")->getPosition();
	//CCPoint theTouchLoc = convertToWorldSpace(touch->getLocation());
	//Vec2 thePlayerPos = player->sprite->getPosition();

	//this->getChildByName("drawnode")->setPosition(touch->getLocation() + player->sprite->getPosition() - Director::getInstance()->getVisibleSize() * 0.5f);
	//Vec2 theDotPos = this->getChildByName("drawnode")->getPosition();
	if (distance < 70)
	{
		cocos2d::log("button");
		return true;
	}
	return true;
}

void JoyStick::onTouchEnded(cocos2d::Touch *, cocos2d::Event *)
{
}

void JoyStick::onTouchMoved(cocos2d::Touch *, cocos2d::Event *)
{
}

void JoyStick::onTouchCancelled(cocos2d::Touch *, cocos2d::Event *)
{
}

EventListenerTouchOneByOne* JoyStick::GetEventListenerTouch()
{
	return eventListenerTouch;
}
