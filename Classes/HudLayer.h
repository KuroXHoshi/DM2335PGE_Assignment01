#ifndef HUD_LAYER_H
#define HUD_LAYER_H

#include "cocos2d.h"

class HudLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(HudLayer);
};

#endif