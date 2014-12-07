#include "ufoLayer.h"
#include "planeLayer.h"
#include "gameScene.h"
#include "controlLayer.h"

using namespace cocos2d;

ufoLayer::ufoLayer()
{
	sp_ufo_list.clear();
}
ufoLayer::~ufoLayer()
{
	sp_ufo_list.clear();
}

bool ufoLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Size xsize = Director::getInstance()->getVisibleSize();

	//ufo_insert();
	schedule(schedule_selector(ufoLayer::ufo_insert), 20.f);

	// 加入碰撞检测调度器
	schedule(schedule_selector(ufoLayer::ufo_crash_update), 0.1f);

	return true;
}

void ufoLayer::ufo_insert( float dt )
{
	float rand_fn = cocos2d::random<float>(0.05f,0.95f);

	Size xsize = Director::getInstance()->getVisibleSize();
	Sprite *sp_ufo = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("ufo%d.png", cocos2d::random<int>(1,2))->getCString()) );
	sp_ufo->setPosition(Vec2(xsize.width*rand_fn, xsize.height));
	this->addChild(sp_ufo);

	sp_ufo_list.push_back(sp_ufo);

	float xheight = xsize.height;
	float xspeed = xheight/320*(cocos2d::random<float>(1.5f,2.2f)); /* 计算敌机需飞行的时间 */

	MoveTo *move = MoveTo::create(xspeed, Vec2(sp_ufo->getPositionX(), 0));
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(ufoLayer::ufo_remove, this, sp_ufo));
	sp_ufo->runAction(Sequence::create(EaseBackIn::create(move), callback, nullptr));
}

void ufoLayer::ufo_remove( cocos2d::Sprite *sp )
{
	if (sp != nullptr)
	{
		sp_ufo_list.remove(sp);
		this->removeChild(sp);
	}
}

void ufoLayer::ufo_crash_update( float dt )
{
	ufo_crash_jude();
}

void ufoLayer::ufo_crash_jude()
{
	planeLayer *plane = (planeLayer *)this->getParent()->getChildByTag(nodeTag::plane);

	std::list<Sprite *>::iterator iter = sp_ufo_list.begin();
	for (iter; iter != sp_ufo_list.end(); )
	{
		Sprite *ufo = *iter++;
		if (plane->plane_crash_judge(ufo, false))
		{
			CCLOG("plane crash ufo.");
			ufo_remove(ufo);
			// 更新ufo数
			((menuLayer *)this->getParent()->getChildByTag(nodeTag::menu_layer))->ufo_counts_update();
		}
	}
}







