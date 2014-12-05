#pragma once
#include "cocos2d.h"

class planeLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(planeLayer);
	virtual bool init();

	// 飞机移动控制
	void plane_move_to(cocos2d::Vec2 des_pos);
	// 飞机爆炸动作播放
	void plane_bomb();
	//  获取飞机的区域矩阵（碰撞区域）
	cocos2d::Rect get_plane_boundingbox();
	/* 
	 *  主角飞机碰撞判定 
	 *  bomb: 碰撞后是否飞机发生爆炸,true：发生爆炸<如与敌机碰撞>， false:不发生爆炸<如与ufo等道具碰撞> 
	 *  发生碰撞 return true; 否则 return false;
	 */
	template<class sprite>
	bool plane_crash_judge(sprite *enemy, bool bomb = true);
private:
	cocos2d::Sprite *sp_hero;
};

template<class sprite>
bool planeLayer::plane_crash_judge( sprite *enemy, bool bomb )
{
	if (get_plane_boundingbox().intersectsRect(enemy->getBoundingBox()))
	{
		if (bomb)
		{
			plane_bomb();
		}
		return true;
	}

	return false;
}

