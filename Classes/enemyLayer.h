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

	void enemy_bomb(enemySprite *sp); // ָ���л�������ը
	void remove_all_enemy();	// ���
private:
	void add_enemy(float dt);
	void remove_enemy(enemySprite *sp);	// ɾ��ָ���л�

	void enemy_shoot_update(float dt);	/* schedule update �ӵ������ж� */
	void enemy_shoot_judge();	/* �л����ӵ������ж� */

	std::list<enemySprite *> sp_enemy_list;
};