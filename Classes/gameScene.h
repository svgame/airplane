#pragma once

#include "cocos2d.h"

class gameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	// implement the "static create()" method manually
	CREATE_FUNC(gameScene);

	// 触摸事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	void ufo_counts_update(int ncount = 1);
	void ufo_touch_callback();
private:
	gameScene():_ufo_counts(0){};
	~gameScene(){};
	//void update(float dt);
	
	//ufo 数量统计
	int _ufo_counts;
};