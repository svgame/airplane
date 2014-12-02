#include "gameScene.h"
#include "backgroundLayer.h"
#include "planeLayer.h"
#include "bulletLayer.h"
#include "enemyLayer.h"

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
	addChild(bg_layer, 0, 1);
	// ���ɻ���
	planeLayer *plane_layer = planeLayer::create();
	addChild(plane_layer, 0, 2);

	// ���ɻ��ӵ���
 	bulletLayer *bullet_layer = bulletLayer::create();
 	addChild(bullet_layer, 0, 3);

	// �л���
	enemyLayer *enemy_layer = enemyLayer::create();
	addChild(enemy_layer);

	// ��Ļ�����¼� 
	EventDispatcher *dispach = CCDirector::getInstance()->getEventDispatcher();
	auto *listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(gameScene::onTouchBegan, this);
	listen->onTouchMoved = CC_CALLBACK_2(gameScene::onTouchMoved, this);

	dispach->addEventListenerWithSceneGraphPriority(listen, this);

	//////////////////////////////////////////////////////////////////////////
	//scheduleUpdate();

	return true;
}


bool gameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void gameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	Vec2 cur_pos = touch->getLocation();
	Vec2 pre_pos = touch->getPreviousLocation();
	Vec2 offset = cur_pos-pre_pos;	// ƫ����
	Vec2 to_pos = ((Sprite *)(getChildByTag(2)->getChildByTag(10)))->getPosition() + offset;
	((planeLayer *)getChildByTag(2))->move_to(to_pos); //�ƶ��ɻ� 

}

// void gameScene::update( float dt )
// {
// 
// }
