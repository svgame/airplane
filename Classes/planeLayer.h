#pragma once
#include "cocos2d.h"
#include "gameScene.h"

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
	cocos2d::Rect plane_head_rect = sp_hero->getBoundingBox();
	cocos2d::Rect plane_bottom_rect = sp_hero->getBoundingBox();

	/*
	 *  将飞机切割成上下两部分，上部分宽度缩小到1/4, 下班部分宽度缩小1/2,在进行碰撞检测
	 */
	plane_head_rect.origin.x += plane_head_rect.size.width*3/8;
	plane_head_rect.size.width = plane_head_rect.size.width/4;
	plane_head_rect.size.height -= 5;

	plane_bottom_rect.origin.x += plane_bottom_rect.size.width/4;
	plane_bottom_rect.size.width = plane_bottom_rect.size.width/2;
	plane_bottom_rect.size.height = plane_bottom_rect.size.height/2;

	if (plane_head_rect.intersectsRect(enemy->getBoundingBox()) 
		|| plane_bottom_rect.intersectsRect(enemy->getBoundingBox()) 
		)
	{
		if (bomb)
		{
			plane_bomb();
			((gameScene *)this->getParent())->game_over();
		}
		return true;
	}

	return false;
}

