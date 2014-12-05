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
	void enemy_remove_all();	// ��������������Ļ�ϵĵл�������ը
private:
	void enemy_insert(float dt);
	void enemy_remove(enemySprite *sp);	// �Ƴ�ָ���л�
	void enemy_bomb_clean(enemySprite *sp);	// ָ���л���ը������������

	void enemy_shoot_update(float dt);	/* schedule update �ӵ������ж� */
	void enemy_shoot_judge();	/* �л����ӵ������ж� */

	std::list<enemySprite *> sp_enemy_list;
};