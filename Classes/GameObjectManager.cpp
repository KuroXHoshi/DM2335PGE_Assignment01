#include "GameObjectManager.h"

#include "Enemy.h"
#include "GameController.h"

GameObjectManager::GameObjectManager()
{
}

void GameObjectManager::Update(double dt)
{
    for (std::map<int, GameObject*>::iterator entry = gameObjectMap.begin(); entry!= gameObjectMap.end(); ++entry)
	{
		//If game object is inactive, skip
		if (entry->second->isDead())
			continue;

		if (!entry->second->hasStartedUpdate)
		{
			entry->second->Start();
			entry->second->hasStartedUpdate = true;
		}

		entry->second->Update(dt);
	}

	PostUpdate();
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
		if (Enemy* e = dynamic_cast<Enemy*>(it->second))
		{

			for (std::vector<GameObject*>::iterator eit = GameController::GetInstance()->activeEnemies.begin();
				eit != GameController::GetInstance()->activeEnemies.end(); ++eit)
			{
				if (e == (*eit))
				{
					eit = GameController::GetInstance()->activeEnemies.erase(eit);
					break;
				}
				
			}
		}
		it = gameObjectMap.erase(it);
	}

	//Delete them objs
    for (int i = 0; i < delList.size(); ++i)
        //GameObject* go in delList)
	{
        GameObject* go = delList[i];
		if (go->sprite != nullptr)
			go->sprite->removeFromParentAndCleanup(true);
		//delete go;
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
