#pragma once

#include "cocos2d.h"

class backgroundLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(backgroundLayer);
	virtual bool init();

	void pass_resume(bool decision);	//设置背景的状态 <暂停|恢复游戏> true:暂停 ,false:继续游戏
private:
	backgroundLayer():nSpeed(8){};

	void update(float df);	/* 背景滚动更新，调度器回调 */

	int nSpeed;	/* 背景滚动速度 */
	cocos2d::Sprite *sp_bg1;
	cocos2d::Sprite *sp_bg2;
};