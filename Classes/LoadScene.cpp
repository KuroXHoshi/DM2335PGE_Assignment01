#include "LoadScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

#include <string>

USING_NS_CC;

Scene* LoadScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setGravity(Vec2(0, -98.0f));
	auto layer = LoadScene::create();
	scene->addChild(layer);
	return scene;
	//return LoadScene::createWithPhysics();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoadSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	filepaths = GetFilePaths();
	textLabel = Label::createWithTTF("0%", "fonts/Marker Felt.ttf", 24);
	if (textLabel != nullptr)
	{
		textLabel->setPosition(Vec2((int)visibleSize.width >> 1, ((int)visibleSize.height >> 1) - 30));
		this->addChild(textLabel, 1);
	}
	index = 0;
	Director::getInstance()->getTextureCache()->addImageAsync(filepaths[index], CC_CALLBACK_1(LoadScene::LoadTexture, this));

	return true;
}


void LoadScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void LoadScene::LoadTexture(Texture2D* texture)
{
	++index;
	auto director = Director::getInstance();

	if (!filepaths.empty())
	{
		int percentage = index * 100 / filepaths.size();
		textLabel->setString(CCString::createWithFormat("%d%%", percentage)->getCString());
		if (index < filepaths.size())
		{
			director->getTextureCache()->addImageAsync(filepaths[index], CC_CALLBACK_1(LoadScene::LoadTexture, this));
		}
		else
		{
			auto scene = HelloWorld::createScene();
			return director->replaceScene(scene);
		}
	}
	else
		return;
}

std::vector<std::string> LoadScene::GetFilePaths()
{
	//struct _finddata_t c_file;
	//intptr_t hFile;
	//std::vector<std::string> filepaths;

	////check if the directory existsS
	//if ((hFile = _findfirst("..\\Resources\\textures/*", &c_file)) == -1L)
	//{
	//	printf("no file found");
	//	if ((hFile = _findfirst("..\\..\\Resources\\textures/*", &c_file)) == -1L)
	//	{

	//	}
	//	else
	//	{
	//		do {
	//			filepaths.push_back(c_file.name);
	//		} while (_findnext(hFile, &c_file) == 0);
	//	}
	//}
	//else
	//{
	//	do {
	//		filepaths.push_back(c_file.name);
	//	} while (_findnext(hFile, &c_file) == 0);
	//}

	std::vector<std::string> filepaths;
	filepaths.push_back("background.tga");
	filepaths.push_back("bg_death_scene.tga");
	filepaths.push_back("bg_meteor.tga");
	filepaths.push_back("bg_sky.tga");
	filepaths.push_back("bg_sky2.tga");
	filepaths.push_back("blackattack.tga");
	filepaths.push_back("blackdragon.tga");
	filepaths.push_back("Blue_Back1.png");
	filepaths.push_back("Blue_Back2.png");
	filepaths.push_back("Blue_Back3.png");
	filepaths.push_back("Blue_Front1.png");
	filepaths.push_back("Blue_Front2.png");
	filepaths.push_back("Blue_Front3.png");
	filepaths.push_back("LightBlue_Front1.png");
	filepaths.push_back("Blue_Left1.png");
	filepaths.push_back("Blue_Left2.png");
	filepaths.push_back("Blue_Left3.png");
	filepaths.push_back("Blue_Right1.png");
	filepaths.push_back("Blue_Right2.png");
	filepaths.push_back("Blue_Right3.png");
	filepaths.push_back("CosmoCookie_Health.tga");
	filepaths.push_back("damage_up.tga");
	filepaths.push_back("enemy_harpyboss_attack.tga");
	filepaths.push_back("enemy_harpyboss_idle.tga");
	filepaths.push_back("enemy_harpyboss2_attack.tga");
	filepaths.push_back("enemy_harpyboss2_idle.tga");
	filepaths.push_back("Enemy_Oce_Side.tga");
	filepaths.push_back("Enemy_Oce_Top.tga");
	filepaths.push_back("enemy_wolf_attack.tga");
	filepaths.push_back("enemy_wolf_idle.tga");
	filepaths.push_back("EnemyBullet_01.tga");
	filepaths.push_back("EnemyBullet_02.tga");
	filepaths.push_back("EnemyBullet_03.tga");
	filepaths.push_back("firerate_up.tga");
	filepaths.push_back("Game_Title.tga");
	filepaths.push_back("greenhpbar.tga");
	filepaths.push_back("Mutton_Death.tga");
	filepaths.push_back("Protagonist_Bullet.tga");
	filepaths.push_back("Protagonist_fart.tga");
	filepaths.push_back("Protagonist_Laser.tga");
	filepaths.push_back("Reticle.tga");
	filepaths.push_back("redhpbar.tga");
	filepaths.push_back("Sheep_fire.tga");
	filepaths.push_back("Sheep_idle.tga");
	filepaths.push_back("ui_button.tga");
	filepaths.push_back("ui_button_exit.tga");
	filepaths.push_back("ui_button_start.tga");
	filepaths.push_back("ui_health1.tga");
	filepaths.push_back("ui_health2.tga");
	filepaths.push_back("ui_health11.tga");
	filepaths.push_back("ui_health22.tga");
	filepaths.push_back("ui_healthbar.tga");
	filepaths.push_back("ui_healthbar1.tga");
	filepaths.push_back("Water_Laser.tga");
	filepaths.push_back("Weed_Rage.tga");
	filepaths.push_back("White_Front1.tga");
	filepaths.push_back("ZigzagForest_Square.png");
	filepaths.push_back("ZigzagGrass_Mud_Round.png");
	filepaths.push_back("ui_joystick_bg");

	return filepaths;
}

void LoadScene::update(float delta)
{

}