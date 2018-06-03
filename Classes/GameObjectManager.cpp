#include "GameObjectManager.h"


GameObjectManager::GameObjectManager()
{
}

void GameObjectManager::Update(double dt)
{
	for each (auto entry in gameObjectMap)
	{
		//If game object is inactive, skip
		if (entry.second->isDead())
			continue;

		if (!entry.second->hasStartedUpdate)
		{
			entry.second->Start();
			entry.second->hasStartedUpdate = true;
		}

		entry.second->Update(dt);
	}

	//PostUpdate();
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
		delList.push_back(it->second);
		it = gameObjectMap.erase(it);
	}

	//Delete them objs
	for each (GameObject* go in delList)
	{
		delete go;
		go = nullptr;
	}

	if (!delList.empty())
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
