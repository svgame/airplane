#pragma once

#include "cocos2d.h"

// Ԥ������Ϸ������tagֵ
enum nodeTag
{
	background = 1,
	plane,
	plane_sp,
	bullet,
	menu_layer,
	menu_pause,
	menu_scores,
	game_over_score,
	ufo = 10,
	ufo_counts,
	ufo_counts_label,
	enemy = 20,
	enemy_small,
	enemy_medium,
	enemy_large
};

class gameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	// implement the "static create()" method manually
	CREATE_FUNC(gameScene);

	// �����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	// �����¼� 
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void game_over();	// ��Ϸ��������ת
private:
	gameScene(){};
	~gameScene(){};
};