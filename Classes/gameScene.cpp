#include "gameScene.h"
#include "startScene.h"
#include "backgroundLayer.h"
#include "planeLayer.h"
#include "bulletLayer.h"
#include "enemyLayer.h"
#include "ufoLayer.h"
#include "menuLayer.h"

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

	// ¹ö¶¯±³¾°²ã
	backgroundLayer *bg_layer = backgroundLayer::create();
	this->addChild(bg_layer, 0, nodeTag::background);
	// Ö÷·É»ú²ã
	planeLayer *plane_layer = planeLayer::create();
	this->addChild(plane_layer, 0, nodeTag::plane);

	// Ö÷·É»ú×Óµ¯²ã
 	bulletLayer *bullet_layer = bulletLayer::create();
 	this->addChild(bullet_layer, 0, nodeTag::bullet);

	// µÐ»ú²ã
	enemyLayer *enemy_layer = enemyLayer::create();
	this->addChild(enemy_layer, 0, nodeTag::enemy);

	ufoLayer *ufo = ufoLayer::create();
	this->addChild(ufo, 0, nodeTag::ufo);

 	menuLayer *menu = menuLayer::create();
 	this->addChild(menu, 0, nodeTag::menu_layer);

	// ÆÁÄ»´¥ÃþÊÂ¼þ 
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
	if ((Director::getInstance()->isPaused()))
	{
		return ;
	}
	Vec2 cur_pos = touch->getLocation();
	Vec2 pre_pos = touch->getPreviousLocation();
	Vec2 offset = cur_pos-pre_pos;	// Æ«ÒÆÁ¿
	Vec2 to_pos = ((Sprite *)(getChildByTag(nodeTag::plane)->getChildByTag(nodeTag::plane_sp)))->getPosition() + offset;
	((planeLayer *)getChildByTag(nodeTag::plane))->plane_move_to(to_pos); //ÒÆ¶¯·É»ú 

}

void gameScene::ufo_counts_update( int ncount /*= 1*/ )
{
	_ufo_counts += ncount;
	if (_ufo_counts < 0)
	{
		return ;
	}
	cocos2d::Node *sp_ufo = nullptr;
	if (!(sp_ufo = this->getChildByTag(nodeTag::ufo_counts)))
	{
		Sprite *sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb.png"));
		
		MenuItemSprite *menuitem = MenuItemSprite::create(
			sp,sp,CC_CALLBACK_0(gameScene::ufo_touch_callback, this) );
		menuitem->setPosition(Vec2(sp->getContentSize().width/2+10,sp->getContentSize().height/2+10));
		Menu *menu = Menu::create(menuitem, nullptr);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 0, nodeTag::ufo_counts);

		sp_ufo = menu;
	}
	cocos2d::Label *sp_count = nullptr;
	if (!(sp_count = (Label *)this->getChildByTag(nodeTag::ufo_counts_label)))
	{
		Sprite *sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb.png"));

		Label *label = Label::createWithBMFont("fonts/font.fnt", 
			String::createWithFormat("X%d",_ufo_counts)->getCString());
		label->setColor(Color3B(143,146,147));
		label->setAnchorPoint(Vec2(0,0.5));
		label->setPosition(Vec2(sp->getContentSize().width*1.2, sp->getContentSize().height/2 + 5));
		this->addChild(label, 0, nodeTag::ufo_counts_label);

		sp_count = label;
	}
	sp_count->setString(String::createWithFormat("X%d",_ufo_counts)->getCString());

	if (_ufo_counts == 0)
	{
		sp_ufo->runAction(Hide::create());
		sp_count->runAction(Hide::create());
	}
	else
	{
		sp_ufo->runAction(Show::create());
		sp_count->runAction(Show::create());
	}

}

void gameScene::ufo_touch_callback()
{
	enemyLayer *enemy = (enemyLayer *)this->getChildByTag(nodeTag::enemy);
	if (enemy && !(Director::getInstance()->isPaused()))
	{
		enemy->enemy_remove_all();
		ufo_counts_update(-1);
	}
	
}

void gameScene::game_over()
{
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1.f,
		gameoverScene::createScene(_game_score)) );
}

// void gameScene::update( float dt )
// {
// 
// }
