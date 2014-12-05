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
	void enemy_remove_all();	// 清屏。让所有屏幕上的敌机发生爆炸
private:
	void enemy_insert(float dt);
	void enemy_remove(enemySprite *sp);	// 移除指定敌机
	void enemy_bomb_clean(enemySprite *sp);	// 指定敌机爆炸后的清除操作。

	void enemy_shoot_update(float dt);	/* schedule update 子弹击中判定 */
	void enemy_shoot_judge();	/* 敌机被子弹击中判定 */

	std::list<enemySprite *> sp_enemy_list;
};