#pragma once

#include "cocos2d.h"

class backgroundLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(backgroundLayer);
	virtual bool init();

	void pass_resume(bool decision);	//���ñ�����״̬ <��ͣ|�ָ���Ϸ> true:��ͣ ,false:������Ϸ
private:
	backgroundLayer():nSpeed(8){};

	void update(float df);	/* �����������£��������ص� */

	int nSpeed;	/* ���������ٶ� */
	cocos2d::Sprite *sp_bg1;
	cocos2d::Sprite *sp_bg2;
};