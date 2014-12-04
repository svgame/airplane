#pragma once
#include "cocos2d.h"

class planeLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(planeLayer);
	virtual bool init();

	// �ɻ��ƶ�����
	void move_to(cocos2d::Vec2 des_pos);
	// �ɻ���ը��������
	void plane_bomb();
	//  ��ȡ�ɻ������������ײ����
	cocos2d::Rect get_plane_boundingbox();
	/* 
	 *  ���Ƿɻ���ײ�ж� 
	 *  �ɻ�׹�� return true; ���� return false;
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

