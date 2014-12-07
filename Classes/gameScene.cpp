#include "gameScene.h"
#include "startScene.h"
#include "backgroundLayer.h"
#include "planeLayer.h"
#include "bulletLayer.h"
#include "enemyLayer.h"
#include "ufoLayer.h"
#include "controlLayer.h"

using namespace cocos2d;

Scene* gameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = gameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool gameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	// ����������
	backgroundLayer *bg_layer = backgroundLayer::create();
	this->addChild(bg_layer, 0, nodeTag::background);
	// ���ɻ���
	planeLayer *plane_layer = planeLayer::create();
	this->addChild(plane_layer, 0, nodeTag::plane);

	// ���ɻ��ӵ���
 	bulletLayer *bullet_layer = bulletLayer::create();
 	this->addChild(bullet_layer, 0, nodeTag::bullet);

	// �л���
	enemyLayer<enemySmall> *enemy_small = enemyLayer<enemySmall>::create();
	this->addChild(enemy_small, 0, nodeTag::enemy_small);

	enemyLayer<enemyMedium> *enemy_medium = enemyLayer<enemyMedium>::create();
	this->addChild(enemy_medium, 0, nodeTag::enemy_medium);
	
	enemyLayer<enemyLarge> *enemy_large = enemyLayer<enemyLarge>::create();
	this->addChild(enemy_large, 0, nodeTag::enemy_large);

	// ufo
	ufoLayer *ufo = ufoLayer::create();
	this->addChild(ufo, 0, nodeTag::ufo);

 	menuLayer *menu = menuLayer::create();
 	this->addChild(menu, 0, nodeTag::menu_layer);

	// ��Ļ�����¼� 
	EventDispatcher *dispach = CCDirector::getInstance()->getEventDispatcher();
	auto *listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(gameScene::onTouchBegan, this);
	listen->onTouchMoved = CC_CALLBACK_2(gameScene::onTouchMoved, this);

	dispach->addEventListenerWithSceneGraphPriority(listen, this);

	//////////////////////////////////////////////////////////////////////////
	// �ƶ��豸���̰�����Ӧ�¼�
	auto keyboardlisten = EventListenerKeyboard::create();
	keyboardlisten->onKeyPressed = CC_CALLBACK_2(gameScene::onKeyPressed, this);
	keyboardlisten->onKeyReleased = CC_CALLBACK_2(gameScene::onKeyReleased, this);

	dispach->addEventListenerWithSceneGraphPriority(keyboardlisten,this);

	return true;
}


bool gameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void gameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	if ((Director::getInstance()->isPaused()))
	{
		return ;
	}
	Vec2 cur_pos = touch->getLocation();
	Vec2 pre_pos = touch->getPreviousLocation();
	Vec2 offset = cur_pos-pre_pos;	// ƫ����
	Vec2 to_pos = ((Sprite *)(getChildByTag(nodeTag::plane)->getChildByTag(nodeTag::plane_sp)))->getPosition() + offset;
	((planeLayer *)getChildByTag(nodeTag::plane))->plane_move_to(to_pos); //�ƶ��ɻ� 

}

// �����¼� 
void gameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
}

void gameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		CCLOG("exit game. ");
		Director::getInstance()->end();
	}
}

void gameScene::game_over()
{
	Director::getInstance()->replaceScene(
		TransitionSlideInR::create( 1.f, gameoverScene::createScene( 
			((menuLayer *)this->getChildByTag(nodeTag::menu_layer))->get_game_scores() ) )
		);
}

