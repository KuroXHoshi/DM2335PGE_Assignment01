#pragma once

#include "SingletonTemplate.h"
#include "cocos2d.h"
#include <deque>

USING_NS_CC;

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;
	std::deque<Node*> queuedNode;
public:
	void AddNodeToCurrentScene(Node* node);
	void Update(double dt);
};