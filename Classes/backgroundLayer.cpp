#include "backgroundLayer.h"

using namespace cocos2d;

bool backgroundLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Size xsize = Director::getInstance()->getVisibleSize();

	sp_bg1 = Sprite::createWithSpriteFrameName("background.png");
	sp_bg1->setPosition(Vec2(xsize.width/2, (sp_bg1->getContentSize().height)/2));
	addChild(sp_bg1);

	sp_bg2 = Sprite::createWithSpriteFrameName("background.png");
	sp_bg2->setPosition(Vec2(xsize.width/2, (sp_bg1->getContentSize().height)*3/2-2));
	addChild(sp_bg2);

	// ����������
	//scheduleUpdate();
	schedule(schedule_selector(backgroundLayer::update), 0.1f);

	return true;
}

void backgroundLayer::update(float df)
{
	Size xsize = Director::getInstance()->getVisibleSize();
	// ���±���������
	sp_bg1->setPositionY(sp_bg1->getPositionY()-nSpeed);
	sp_bg2->setPositionY(sp_bg2->getPositionY()-nSpeed);

 	if (sp_bg1->getPositionY()+sp_bg1->getContentSize().height/2 < 0)
 	{
 		sp_bg1->setPositionY((sp_bg2->getPositionY() + sp_bg1->getContentSize().height) - 2);
 	}
 	if (sp_bg2->getPositionY()+sp_bg2->getContentSize().height/2 < 0)
 	{
 		sp_bg2->setPositionY(sp_bg1->getPositionY() + sp_bg2->getContentSize().height -2);
 	}

}

//���ñ�����״̬ <��ͣ|�ָ���Ϸ> true:��ͣ ,false:������Ϸ
void backgroundLayer::pass_resume( bool decision )
{
	static bool b_game_pass = false;
	if (!b_game_pass && decision)
	{
		// ��ͣ�������� <ͨ��ͣ�õ�����>
		b_game_pass = true;
		unschedule(schedule_selector(backgroundLayer::update));
	}
	else if (b_game_pass && !decision)
	{
		// �ָ���Ϸ�������� <�ָ���������ʹ��>
		b_game_pass = false;
		schedule(schedule_selector(backgroundLayer::update), 0.1f);
	}
}

