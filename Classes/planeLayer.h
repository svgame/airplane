#pragma once
#include "cocos2d.h"
#include "gameScene.h"

class planeLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(planeLayer);
	virtual bool init();

	// �ɻ��ƶ�����
	void plane_move_to(cocos2d::Vec2 des_pos);
	// �ɻ���ը��������
	void plane_bomb();
	//  ��ȡ�ɻ������������ײ����
	cocos2d::Rect get_plane_boundingbox();
	/* 
	 *  ���Ƿɻ���ײ�ж� 
	 *  bomb: ��ײ���Ƿ�ɻ�������ը,true��������ը<����л���ײ>�� false:��������ը<����ufo�ȵ�����ײ> 
	 *  ������ײ return true; ���� return false;
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
	 *  ���ɻ��и�����������֣��ϲ��ֿ����С��1/4, �°ಿ�ֿ����С1/2,�ڽ�����ײ���
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

