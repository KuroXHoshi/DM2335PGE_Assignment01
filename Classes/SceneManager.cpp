#include "SceneManager.h"

void SceneManager::AddNodeToCurrentScene(Node * node)
{
	Scene* curr = Director::getInstance()->getRunningScene();
	if (curr == nullptr)
	{
		node->retain();
		queuedNode.push_back(node);
		return;
	}
	curr->addChild(node);
}

void SceneManager::Update(double dt)
{
	if (queuedNode.size())
	{
		Scene* curr = Director::getInstance()->getRunningScene();
		if (curr)
		{
			while (queuedNode.size())
			{
				Node* node = queuedNode.front();
				curr->addChild(node);
				queuedNode.pop_front();
				node->release();
			}
		}
	}
}
