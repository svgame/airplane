#pragma once
#include "cocos2d.h"

class planeLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(planeLayer);
	virtual bool init();

	// �ɻ��ƶ�����
	void move_to(cocos2d::Vec2 des_pos);
	//  ��ȡ�ɻ������������ײ����
	cocos2d::Rect get_plane_boundingbox();
private:
	cocos2d::Sprite *sp_hero;
};