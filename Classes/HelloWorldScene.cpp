#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

Animate* animateIdle;
Animate* animateMouse;

#include "Weapon.h"
Weapon* weapon;
Weapon* weapon2;
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "GameController.h"
#include "Projectile.h"
#include "Functions.h"
#include "Enemy.h"

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setGravity(Vec2(0, -98.0f)); //space game no gravity
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
	//return HelloWorld::createWithPhysics();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	if (!Layer::init() )
    {
        return false;
    }

	srand(0);
	//HelloWorld::createWithPhysics();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	int x = sprite->getContentSize().width;
	int numOftiles = playingSize.width / x;

	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems" + std::to_string(0));


	//auto joystick_bg_left_node = Node::create();
	//joystick_bg_left_node->setName("joystick_bg_left_node");
	//auto joystick_bg_left_sprite = Sprite::create("textures/ui_joystick_bg.tga");
	//joystick_bg_left_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	//joystick_bg_left_sprite->setPosition(playingSize.width * 0.1, playingSize.height * 0.1);
	//joystick_bg_left_sprite->setName("joystick_bg_left_sprite");

	//joystick_bg_left_sprite->retain();

	//joystick_bg_left_node->addChild(sprite, 1);

	/*auto bkgrnd = Sprite::create("textures/bg_sky2.tga");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2::ZERO);
	nodeItems->addChild(bkgrnd, 0);
	this->addChild(nodeItems, 1);*/
	
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	player = new Player();
	//this->addChild(player->spriteNode);
	//player->sprite->setPosition(playingSize.width / 2, playingSize.height / 2);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(player->GetKbListener(), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(player->GetMouseListener(), this);

	GameController::GetInstance()->Init(player);
	GameController::GetInstance()->scene = (Scene*)this;
	//add sprites of the bg to the node;
	for (int i = 0; i < 9; ++i)
	{
		nodeItems->addChild(GameController::GetInstance()->GetBackgroundSprites()[i], 0);
	}
	this->addChild(nodeItems);


	auto joystick_bg_left = Sprite::create("textures/ui_joystick_bg.tga");
	//joystick_bg_left->setPosition(Vec2(playingSize.width * 0.1, playingSize.height * 0.1));
	
	joystick_bg_left->setAnchorPoint(Vec2(0.5f, 0.5f));
	//joystick_bg_left->setTitleText("Button Text");
	
	//joystick_bg_left->runAction(Follow::createWithOffset(Camera::getDefaultCamera(), playingSize.width * 0.1, playingSize.height * 0.1));
	//Camera::getDefaultCamera()->addChild(joystick_bg_left, 2);
	joystick_bg_left->setName("joystick_bg_left");
	this->addChild(joystick_bg_left, 2);
	
	DrawNode* drawnode = DrawNode::create();
	drawnode->drawDot(Vec2(0, 0), 20, Color4F(2, 99, 2, 2));
	//drawnode->setPosition(Point(winSize.width / 2.1 + origin.x, winSize.height / 5 + origin.y));
	drawnode->setName("drawnode");
	this->addChild(drawnode,3);

	//auto spriteNode = Node::create();
	//spriteNode->setName("spriteNode");

	//auto mainSprite = Sprite::create("Blue_Front1.png");
	//mainSprite->setAnchorPoint(Vec2(0, 0));
	//mainSprite->setPosition(0, playingSize.height/2 + sprite->getContentSize().height);
	//mainSprite->setName("mainSprite");
	//
	//spriteNode->addChild(mainSprite, 1);
	//this->addChild(spriteNode, 1);

	auto moveEvent = MoveBy::create(5, Vec2(200, 0));
	////mainSprite->runAction(moveEvent);

	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//mainSprite->runAction(sequence);

	auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//auto mouseListener = EventListenerMouse::create();
	//mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMousePressed, this);
	//mouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	this->scheduleUpdate();

	cocos2d::Vector<SpriteFrame*> animFrames;
	animFrames.reserve(2);
	animFrames.pushBack(SpriteFrame::create("textures/player_2.tga", Rect(0, 0, 39, 43)));
	animFrames.pushBack(SpriteFrame::create("textures/player_3.tga", Rect(0, 0, 39, 40)));
	//animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
	//animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	animateIdle = Animate::create(animation);
	animateIdle->retain();	
	player->SetAnimFrames(animFrames, 0.5f);
	//player->sprite->runAction(RepeatForever::create(player->animate))->setTag(0);
	//mainSprite->runAction(RepeatForever::create(animateIdle))->setTag(0);

	cocos2d::Vector<SpriteFrame*> mouseAnimFrames;
	mouseAnimFrames.reserve(4);
	mouseAnimFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 82)));
	mouseAnimFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 64, 81)));
	mouseAnimFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 82)));
	mouseAnimFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));

	Animation* mouseanimation = Animation::createWithSpriteFrames(mouseAnimFrames, 0.5f);
	animateMouse = Animate::create(mouseanimation);
	animateMouse->retain();

	playerHealth = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
	if (playerHealth != nullptr)
	{
		this->addChild(playerHealth, 1);
	}
	
	//Sequence::create(MoveBy)

	//weapon = new Weapon();
	//weapon->Set(1, 10, 5, 0, 300, 0);
	//
	//weapon2 = new Weapon();
	//weapon2->Set(1, 10, 5, 0, 100, 0);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::OnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create(
    //                                       "CloseNormal.png",
    //                                       "CloseSelected.png",
    //                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    //if (closeItem == nullptr ||
    //    closeItem->getContentSize().width <= 0 ||
    //    closeItem->getContentSize().height <= 0)
    //{
    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    //}
    //else
    //{
    //    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    //    float y = origin.y + closeItem->getContentSize().height/2;
    //    closeItem->setPosition(Vec2(x,y));
    //}

    //// create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    ///////////////////////////////
    //// 3. add your codes below...

    //// add a label shows "Hello World"
    //// create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}

	audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("sounds/bgm.mp3");
	audio->playBackgroundMusic("sounds/bgm.mp3", true);
	audio->preloadEffect("sounds/shoot.mp3");
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveBy::create(5.0f, Vec2(1000.0f, 0.f));
		curSprite->runAction(moveEvent)->setTag(1);

		curSprite->stopActionByTag(0);
		curSprite->runAction(RepeatForever::create(animateIdle))->setTag(0);
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveBy::create(5.0f, Vec2(-1000.0f, 0.f));
		curSprite->runAction(moveEvent)->setTag(1);

		curSprite->stopActionByTag(0);
		curSprite->runAction(RepeatForever::create(animateIdle))->setTag(0);
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveBy::create(5.0f, Vec2(-1000.0f, 0.f));
		curSprite->runAction(moveEvent)->setTag(1);

		curSprite->stopActionByTag(0);
		curSprite->runAction(RepeatForever::create(animateIdle))->setTag(0);
	}
	else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveBy::create(5.0f, Vec2(-1000.0f, 0.f));
		curSprite->runAction(moveEvent)->setTag(1);

		curSprite->stopActionByTag(0);
		curSprite->runAction(RepeatForever::create(animateIdle))->setTag(0);
	}
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		curSprite->stopActionByTag(1);

	}

	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
	{
		GameController::GetInstance()->switchStates();
	}

}

//should store action if not using when created
//Vec2* moveDirPtr = nullptr;

void HelloWorld::onMousePressed(cocos2d::Event * event_)
{
	EventMouse* e = (EventMouse*)event_;
	//if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	//{
	//	//aka screem size
	//	auto visibleSize = Director::getInstance()->getVisibleSize();
	//	
	//	weapon->position.set(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	//	weapon->direction.set(e->getCursorX() - weapon->position.x, e->getCursorY() - weapon->position.y);
	//	weapon->direction.normalize();
	//	weapon->Discharge();
	//}

	//if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	//{
	//	//aka screem size
	//	auto visibleSize = Director::getInstance()->getVisibleSize();

	//	weapon2->position.set(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	//	weapon2->direction.set(e->getCursorX() - weapon2->position.x, e->getCursorY() - weapon2->position.y);
	//	weapon2->direction.normalize();
	//	weapon2->Discharge();
	//}
}

void HelloWorld::onMouseReleased(cocos2d::Event * event_)
{
	EventMouse* e = (EventMouse*)event_;
	if (e->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		curSprite->stopActionByTag(1);
		int displacement = e->getCursorX() - curSprite->getPositionX();

		auto moveEvent = MoveBy::create(abs(displacement) / 300.0f, Vec2(displacement, 0));

		auto callbackStop = CallFunc::create([curSprite]() {
			curSprite->stopAllActions();
			curSprite->runAction(RepeatForever::create(animateIdle))->setTag(0);
		});

		auto seq = Sequence::create(moveEvent, callbackStop, nullptr);

		curSprite->runAction(seq)->setTag(1);

		curSprite->stopActionByTag(0);
		curSprite->runAction(RepeatForever::create(animateMouse))->setTag(0);
	}
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	cocos2d::log("touch began");
	EventTouch* e = (EventTouch*)event;
	float distance = ((this->getChildByName("joystick_bg_left")->getPosition()).distance(touch->getLocation() + player->sprite->getPosition() - Director::getInstance()->getVisibleSize() * 0.5f));
	
	Vec2 theJoyPos = this->getChildByName("joystick_bg_left")->getPosition();
	CCPoint theTouchLoc = convertToWorldSpace(touch->getLocation());
	Vec2 thePlayerPos = player->sprite->getPosition();
	
	this->getChildByName("drawnode")->setPosition(touch->getLocation() + player->sprite->getPosition() - Director::getInstance()->getVisibleSize() * 0.5f);
	Vec2 theDotPos = this->getChildByName("drawnode")->getPosition();
	if (distance < 80)
	{
		cocos2d::log("button");
		return true;
	}
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d::log("touch ended");
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	cocos2d::log("touch moved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
	cocos2d::log("touch cancelled");
}

void HelloWorld::update(float delta)
{
	//auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
	//auto moveEvent = MoveBy::create(1.0f, Vec2(10,0));
	//curSprite->runAction(moveEvent);

	SceneManager::GetInstance()->Update(delta);
	GameObjectManager::GetInstance()->Update(delta);
	GameController::GetInstance()->Update(delta);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	//centering the camera on the player
	Camera* cam = Camera::getDefaultCamera();
	cam->setPosition(player->sprite->getPosition());
	this->getChildByName("joystick_bg_left")->setPosition(cam->getPosition() - Vec2(playingSize.width * 0.4, playingSize.height * 0.4));
	
	//player->LookAt();
	playerHealth->setString(std::to_string(player->GetHealth()));
	playerHealth->setPosition(player->sprite->getPosition().x, player->sprite->getPosition().y - 30);

	GameObjectManager::GetInstance()->PostUpdate();
}

bool HelloWorld::OnContactBegin(PhysicsContact & contact)
{
	
	PhysicsShape* shapeA = contact.getShapeA();
	PhysicsShape* shapeB = contact.getShapeB();

	//void* userDataA = shapeA->getBody()->getNode()->getUserData();
	//void* userDataB = shapeB->getBody()->getNode()->getUserData();
	////Projectile* proj = GetData<Projectile*>(userDataA, userDataB);
	//Projectile* a = reinterpret_cast<Projectile*>(userDataA);
	//Projectile* b = reinterpret_cast<Projectile*>(userDataB);


	GameObject* a = GameObjectManager::GetInstance()->GetGameObject(shapeA->getBody()->getTag());
	GameObject* b = GameObjectManager::GetInstance()->GetGameObject(shapeB->getBody()->getTag());
	Projectile* projA = dynamic_cast<Projectile*>(a);
	Projectile* projB = dynamic_cast<Projectile*>(b);

	Projectile* proj = nullptr;
	GameObject* other = nullptr;
	if (projA)
	{
		proj = projA;
		other = b;
	}
	else if (projB)
	{
		proj = projB;
		other = a;
	}

	if (proj)
	{
		if (proj->isDead())
			return false;

		Enemy* enemy = dynamic_cast<Enemy*>(other);
		if (enemy)
		{
			enemy->health -= proj->damage;
			if (enemy->health <= 0) {
				enemy->healthLabel->removeFromParentAndCleanup(true);
				enemy->Destroy();
				if (GameController::GetInstance()->currState == GAME_STATE::GS_WAVE)
				{
					GameController::GetInstance()->RemoveOneEnemy();
				}
			}
		}
		Player* player = dynamic_cast<Player*>(other);
		if (player)
		{
			player->SetHealth(player->GetHealth() - proj->damage);
		}

		proj->Destroy();
		return true;
	}

	return true;
}

