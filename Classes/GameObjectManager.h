#pragma once

#include "SingletonTemplate.h"
#include "GameObject.h"
#include <map>

class GameObjectManager : public Singleton<GameObjectManager>
{
	friend Singleton<GameObjectManager>;
	std::map<int, GameObject*> gameObjectMap;

	void DeleteGameObject(int goID);
public:
	void AddGameObject(GameObject * go);
	void Update(double dt);
	void PostUpdate();

	GameObject* GetGameObject(int id) { return gameObjectMap[id]; }
protected:
	GameObjectManager();
};