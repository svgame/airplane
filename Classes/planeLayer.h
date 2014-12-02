#pragma once
#include "cocos2d.h"

class planeLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(planeLayer);
	virtual bool init();

	// 飞机移动控制
	void move_to(cocos2d::Vec2 des_pos);
	//  获取飞机的区域矩阵（碰撞区域）
	cocos2d::Rect get_plane_boundingbox();
private:
	cocos2d::Sprite *sp_hero;
};