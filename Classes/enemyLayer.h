#pragma once
#include "cocos2d.h"
#include "enemySprite.h"

#include "bulletLayer.h"
#include "planeLayer.h"
#include "gameScene.h"
#include "controlLayer.h"

#include "SimpleAudioEngine.h"
using namespace cocos2d;

//Large,medium or small
/**
 *	敌机实例基类<模板>
 */
class enemyType
{
public:
	enemyType(){};
	~enemyType(){};
	//virtual void init() {};	//敌机涉及的所有动画均在init() 中预加载
	virtual int get_enemy_hp() = 0;		// 敌机生命值
	virtual int get_score_ratio() = 0;	// 敌机分数比例 <实际分数=ration*100>
	virtual float get_refresh_interval() = 0;	// 敌机刷新时间间隔
	virtual float get_move_speed() = 0;	// 敌机飞行速度<返回飞行完所需时间>
	virtual std::string get_enemy_sprite_name() = 0;	// 敌机精灵名称
	virtual std::string get_bomb_animation_name() =0;	// 敌机爆炸动画名称
	virtual std::string get_move_animation_name() = 0;	// 敌机移动动画名称，没有动画直接返回空字符串
};
/*
 *  敌机实例定义
 */
class enemySmall:public enemyType
{
public:
	enemySmall();
	~enemySmall(){};

	int get_enemy_hp(){ return enemy_hp; };
	int get_score_ratio() { return get_enemy_hp()*5; };
	float get_refresh_interval() {return refresh_interval;}
	std::string get_enemy_sprite_name() { return enemy_sprite_name; };
	std::string get_bomb_animation_name() {  return bomb_animation_name;};
	std::string get_move_animation_name() { return enemy_move_animation_name; };
	float get_move_speed() { return 3.f*cocos2d::random<float>(0.5f,1.2f); }
private:
	void init();

	int enemy_hp;
	float refresh_interval;	// 刷新时间间隔
	std::string bomb_animation_name;
	std::string enemy_sprite_name;
	std::string enemy_move_animation_name;
};

class enemyMedium:public enemyType
{
public:
	enemyMedium();
	~enemyMedium(){};

	int get_enemy_hp(){ return enemy_hp; };
	int get_score_ratio() { return get_enemy_hp()*10; };
	float get_refresh_interval() {return refresh_interval;}
	std::string get_enemy_sprite_name() { return enemy_sprite_name; };
	std::string get_bomb_animation_name() {  return bomb_animation_name;};
	std::string get_move_animation_name() { return enemy_move_animation_name; };
	float get_move_speed() { return 4.f*cocos2d::random<float>(0.5f,1.2f); }
private:
	void init();

	int enemy_hp;
	float refresh_interval;	// 刷新时间间隔
	std::string bomb_animation_name;
	std::string enemy_sprite_name;
	std::string enemy_move_animation_name;
};

class enemyLarge:public enemyType
{
public:
	enemyLarge();
	~enemyLarge(){};

	int get_enemy_hp(){ return enemy_hp; };
	int get_score_ratio() { return get_enemy_hp()*25; };
	float get_refresh_interval() {return refresh_interval;}
	std::string get_enemy_sprite_name() { return enemy_sprite_name; };
	std::string get_bomb_animation_name() {  return bomb_animation_name;};
	std::string get_move_animation_name() { return enemy_move_animation_name; };
	float get_move_speed() { return 10.f; }

private:
	void init();

	int enemy_hp;
	float refresh_interval;	// 刷新时间间隔
	std::string bomb_animation_name;
	std::string enemy_sprite_name;
	std::string enemy_move_animation_name;
};

/** 
 *  敌机模板定义
 */
template<class enemyType>
class enemyLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(enemyLayer);
	virtual bool init();

	void enemy_remove_all();	// 清屏。让所有屏幕上的敌机发生爆炸
protected:
	enemyLayer() { sp_enemy_list.clear(); };
	~enemyLayer() { sp_enemy_list.clear(); };

	void enemy_insert(float dt);
	void enemy_remove(enemySprite *sp);	// 移除指定敌机

	void enemy_bomb(enemySprite *enemy); // 指定敌机发生爆炸
	void enemy_bomb_clean(enemySprite *sp);	// 指定敌机爆炸后的清除操作。

	void enemy_shoot_update(float dt);	/* schedule update 子弹击中判定 */
	void enemy_shoot_judge();	/* 敌机被子弹击中判定 */

	std::list<enemySprite *> sp_enemy_list;
	
	// 敌机实例
	enemyType enemy_type;
};

/** 
 *  敌机模板实现
 */
template<class enemyType>
bool enemyLayer<enemyType>::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size xsize = Director::getInstance()->getVisibleSize();

	//add_enemy();
	schedule(schedule_selector(enemyLayer::enemy_insert), enemy_type.get_refresh_interval());

	// 加入 敌机是否被击中判定 调度器
	schedule(schedule_selector(enemyLayer::enemy_shoot_update), 0.05f);

	return true;
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_insert(float dt)
{
	float rand_fn = cocos2d::random<float>(0.05f,0.95f);

	Size xsize = Director::getInstance()->getVisibleSize();
	enemySprite *sp_enemy = enemySprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(enemy_type.get_enemy_sprite_name() ) );
	
	sp_enemy->set_hp(enemy_type.get_enemy_hp());	// 显式设置敌机生命值. 不设置默认=1 
	sp_enemy->setPosition(Vec2(xsize.width*rand_fn, xsize.height));
	this->addChild(sp_enemy);

	sp_enemy_list.push_back(sp_enemy);

	float xheight = xsize.height;
	float xspeed = enemy_type.get_move_speed(); //xheight/320*(cocos2d::random<float>(0.5f,1.2f)); /* 计算敌机需飞行的时间 */

	MoveTo *move = MoveTo::create(xspeed, Vec2(sp_enemy->getPositionX(), 0));
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(enemyLayer::enemy_remove, this, sp_enemy));
	sp_enemy->runAction(Sequence::create(move, callback, nullptr));

	// -..
	if (!enemy_type.get_move_animation_name().empty())
	{
		// 执行爆炸动画
		Animation *animation = AnimationCache::getInstance()->getAnimation(enemy_type.get_move_animation_name());
		Animate *animate = Animate::create(animation);
		sp_enemy->runAction(RepeatForever::create(animate));
	}
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_remove( enemySprite *sp )
{
	if (sp != nullptr)
	{
		sp_enemy_list.remove(sp);
		this->removeChild(sp);
	}
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_bomb_clean( enemySprite *sp )
{
	if (sp != nullptr)
	{
		//sp_enemy_list.remove(sp); // 这步操作提前到爆炸动画播放前完成
		this->removeChild(sp);
	}
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_bomb(enemySprite* enemy)  
{  
	// 爆炸动作播放前，先将该敌机从敌机列表中踢出
	sp_enemy_list.remove(enemy);
	// 敌机被击中，先停止该敌机的所有动作，然后播放爆炸动作特效
	enemy->stopAllActions();

	//播放音效
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy1_down.mp3");

	// 执行爆炸动画
	Animation *animation = AnimationCache::getInstance()->getAnimation(enemy_type.get_bomb_animation_name());
	Animate *animate = Animate::create(animation);
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(enemyLayer::enemy_remove, this, enemy));

	enemy->runAction(Sequence::create(animate, callback, nullptr));

	// 更新游戏分数
	menuLayer *menu = (menuLayer *)this->getParent()->getChildByTag(nodeTag::menu_layer);
	menu->update_game_scores( enemy_type.get_score_ratio()*100 );
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_remove_all()
{
	std::list<enemySprite *>::iterator iter = sp_enemy_list.begin();
	for (iter; iter != sp_enemy_list.end(); )
	{
		enemy_bomb(*iter++);
	}
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_shoot_update( float dt )
{
	enemy_shoot_judge();
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_shoot_judge()
{
	bulletLayer *bullet = (bulletLayer *)this->getParent()->getChildByTag(nodeTag::bullet);
	planeLayer *plane = (planeLayer *)this->getParent()->getChildByTag(nodeTag::plane);

	std::list<enemySprite *>::iterator iter = sp_enemy_list.begin();
	for (iter; iter != sp_enemy_list.end(); /*waring: iter++ 不能放在此处 */)
	{
		enemySprite *enemy = *iter++;
		if (plane->plane_crash_judge(enemy))
		{
			//主飞机发生爆炸
			enemy_bomb(enemy);
		}
		else if (bullet->bullet_shoot_judge(enemy))
		{
			// 敌机被子弹击中，根据血量判定是否发生爆炸
			enemy->lose_hp(bullet->get_bullet_atk());
			if (enemy->get_hp() < 1)
			{
				enemy_bomb(enemy);
			}
		}
	}
}
