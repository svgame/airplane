#include "gameScene.h"
#include "backgroundLayer.h"
#include "planeLayer.h"
#include "bulletLayer.h"
#include "enemyLayer.h"
#include "ufoLayer.h"

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
	addChild(bg_layer, 0, 1);
	// Ö÷·É»ú²ã
	planeLayer *plane_layer = planeLayer::create();
	addChild(plane_layer, 0, 2);

	// Ö÷·É»ú×Óµ¯²ã
 	bulletLayer *bullet_layer = bulletLayer::create();
 	addChild(bullet_layer, 0, 3);

	// µÐ»ú²ã
	enemyLayer *enemy_layer = enemyLayer::create();
	addChild(enemy_layer, 0, 4);

	ufoLayer *ufo = ufoLayer::create();
	addChild(ufo);

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
	Vec2 cur_pos = touch->getLocation();
	Vec2 pre_pos = touch->getPreviousLocation();
	Vec2 offset = cur_pos-pre_pos;	// Æ«ÒÆÁ¿
	Vec2 to_pos = ((Sprite *)(getChildByTag(2)->getChildByTag(10)))->getPosition() + offset;
	((planeLayer *)getChildByTag(2))->plane_move_to(to_pos); //ÒÆ¶¯·É»ú 

}

void gameScene::ufo_counts_update( int ncount /*= 1*/ )
{
	_ufo_counts += ncount;
	if (_ufo_counts < 0)
	{
		return ;
	}
	cocos2d::Node *sp_ufo = nullptr;
	if (!(sp_ufo = this->getChildByTag(5)))
	{
		Sprite *sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("bomb.png"));
		
		MenuItemSprite *menuitem = MenuItemSprite::create(
			sp,sp,CC_CALLBACK_0(gameScene::ufo_touch_callback, this) );
		menuitem->setPosition(Vec2(sp->getContentSize().width/2+10,sp->getContentSize().height/2+10));
		Menu *menu = Menu::create(menuitem, nullptr);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 0, 5);

		sp_ufo = menu;
	}
	cocos2d::Label *sp_count = nullptr;
	if (!(sp_count = (Label *)this->getChildByTag(6)))
	{
		Sprite *sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("bomb.png"));

		Label *label = Label::createWithBMFont("fonts/font.fnt", 
			String::createWithFormat("X%d",_ufo_counts)->getCString());
		label->setColor(ccc3(143,146,147));
		label->setAnchorPoint(ccp(0,0.5));
		label->setPosition(Vec2(sp->getContentSize().width*1.2, sp->getContentSize().height/2 + 5));
		this->addChild(label, 0, 6);

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
	enemyLayer *enemy = (enemyLayer *)this->getChildByTag(4);
	if (enemy)
	{
		enemy->enemy_remove_all();
	}
	ufo_counts_update(-1);
}

// void gameScene::update( float dt )
// {
// 
// }
