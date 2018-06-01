#ifndef _LOAD_SCENE_H
#define _LOAD_SCENE_H

#include "cocos2d.h"

using namespace cocos2d;

class LoadScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void LoadTexture(Texture2D* texture);

	//function to get all the filepaths of type .[smth]
	std::vector<std::string> GetFilePaths();

	// implement the "static create()" method manually
	CREATE_FUNC(LoadScene);

	void update(float delta);

	std::vector<std::string> filepaths;
	int index;
	Label* textLabel;
};

#endif