#include "Controls.h"

void Controls::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyHeld.find(keyCode) == keyHeld.end())
	{
		keyHeld[keyCode] = true;
	}
}

bool Controls::isKeyHeld(EventKeyboard::KeyCode keyCode)
{
	if (keyHeld.find(keyCode) != keyHeld.end())
	{
		return true;
	}
	return false;
}

void Controls::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	keyHeld.erase(keyCode);
}

bool Controls::anyKeyHeld()
{
	if (keyHeld.empty())
		return false;
	return true;
}

void Controls::keyboardInput(float dt_)
{
}

void Controls::onMouseUp(Event *)
{
}

void Controls::mouseInput(float dt_)
{
}
