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

	// 启动调度器
	//scheduleUpdate();
	schedule(schedule_selector(backgroundLayer::update), 0.1f);

	return true;
}

void backgroundLayer::update(float df)
{
	Size xsize = Director::getInstance()->getVisibleSize();
	// 更新背景滚动。
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

//设置背景的状态 <暂停|恢复游戏> true:暂停 ,false:继续游戏
void backgroundLayer::pass_resume( bool decision )
{
	static bool b_game_pass = false;
	if (!b_game_pass && decision)
	{
		// 暂停背景滚动 <通过停用调度器>
		b_game_pass = true;
		unschedule(schedule_selector(backgroundLayer::update));
	}
	else if (b_game_pass && !decision)
	{
		// 恢复游戏背景滚动 <恢复调度器的使用>
		b_game_pass = false;
		schedule(schedule_selector(backgroundLayer::update), 0.1f);
	}
}

