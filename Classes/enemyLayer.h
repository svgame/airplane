#pragma once
#include "cocos2d.h"
#include "enemySprite.h"

class enemyLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(enemyLayer);
	virtual bool init();
	enemyLayer();
	~enemyLayer();

	void enemy_bomb(enemySprite *sp); // 指定敌机发生爆炸
	void remove_all_enemy();	// 清空
private:
	void add_enemy(float dt);
	void remove_enemy(enemySprite *sp);	// 删除指定敌机

	void enemy_shoot_update(float dt);	/* schedule update 子弹击中判定 */
	void enemy_shoot_judge();	/* 敌机被子弹击中判定 */

	std::list<enemySprite *> sp_enemy_list;
};