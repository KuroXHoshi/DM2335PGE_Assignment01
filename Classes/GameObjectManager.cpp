#include "GameObjectManager.h"


GameObjectManager::GameObjectManager()
{
}

void GameObjectManager::Update(double dt)
{
	for each (auto entry in gameObjectMap)
	{
		//If game object is inactive, skip
		if (!entry.second->active)
			continue;

		entry.second->Update(dt);
	}
}

void GameObjectManager::PostUpdate()
{
	std::vector<GameObject*> delList;
	//End of frame
	for (std::map<int, GameObject*>::iterator it = gameObjectMap.begin(); it != gameObjectMap.end(); )
	{
		//If game object is inactive, skip
		if (!it->second->isDead())
		{
			++it;
			continue;
		}

		//this->DeleteGameObject(it->first);
		it = gameObjectMap.erase(it);
		delList.push_back(it->second);
	}

	//Delete them objs
	for each (GameObject* go in delList)
	{
		delete go;
	}
	delList.clear();
}


void GameObjectManager::AddGameObject(GameObject * go)
{
	gameObjectMap.insert(std::make_pair(go->id, go));
}


void GameObjectManager::DeleteGameObject(int goID)
{
	GameObject* del = gameObjectMap[goID];
	gameObjectMap.erase(goID);
	delete del;
}
