#pragma once
#include "cocos2d.h"

class planeLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(planeLayer);
	virtual bool init();

	// 飞机移动控制
	void move_to(cocos2d::Vec2 des_pos);
	// 飞机爆炸动作播放
	void plane_bomb();
	//  获取飞机的区域矩阵（碰撞区域）
	cocos2d::Rect get_plane_boundingbox();
	/* 
	 *  主角飞机碰撞判定 
	 *  飞机坠毁 return true; 否则 return false;
	 */
	template<class sprite>
	bool plane_crash_judge(sprite *enemy);
private:
	cocos2d::Sprite *sp_hero;
};

template<class sprite>
bool planeLayer::plane_crash_judge( sprite *enemy )
{
	if (get_plane_boundingbox().intersectsRect(enemy->getBoundingBox()))
	{
		plane_bomb();
		return true;
	}

	return false;
}

