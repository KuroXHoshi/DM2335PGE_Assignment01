#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Controls
{
private:
	std::map<EventKeyboard::KeyCode, bool> keyHeld;
	struct Mouse
	{
		Vec2 destination;
		Vec2 direction;
		bool move;
	} mouse;
public:
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool isKeyHeld(EventKeyboard::KeyCode keyCode);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool anyKeyHeld();
	virtual void keyboardInput(float dt_);
	virtual void onMouseUp(Event*);
	virtual void mouseInput(float dt_);
};