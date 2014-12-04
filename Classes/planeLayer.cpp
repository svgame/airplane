#include "planeLayer.h"

using namespace cocos2d;

bool planeLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Size xsize = Director::getInstance()->getVisibleSize();

	// 加载主角精灵
	sp_hero = Sprite::createWithSpriteFrameName("hero1.png");
	sp_hero->setPosition(Vec2(xsize.width/2, xsize.height*0.1));
	addChild(sp_hero, 0, 10);

	// 设置主角入场动画
	Blink *blink = Blink::create(1.0f, 4); // 闪烁动作， 一秒钟闪烁三次
	sp_hero->runAction(blink);

	// 飞机尾部喷火动画
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
	Animate *animate = Animate::create(animation);
	sp_hero->runAction(RepeatForever::create(animate));

	return true;
}

// 飞机移动控制
void planeLayer::move_to( Vec2 des_pos )
{
	Size xsize = Director::getInstance()->getVisibleSize();
	// 飞机hero宽/高的一半
	Vec2 hero_radius = Vec2(sp_hero->getContentSize().width/2, sp_hero->getContentSize().height/2);

	// 限制飞机移动区域 
	des_pos.x = des_pos.x < hero_radius.x/2 ? hero_radius.x/2 : 
		(des_pos.x+hero_radius.x/2 > xsize.width ? xsize.width-hero_radius.x/2 : des_pos.x);
	des_pos.y = des_pos.y < hero_radius.y ? hero_radius.y : 
		(des_pos.y+hero_radius.y > xsize.height ? xsize.height-hero_radius.y : des_pos.y);

	sp_hero->setPosition(des_pos);
}

cocos2d::Rect planeLayer::get_plane_boundingbox()
{
	Rect rect = sp_hero->getBoundingBox();

	/* 将飞机的宽度区域缩小一倍再用于碰撞检测 (两边的机翼不作碰撞)*/
	rect.origin.x += rect.size.width/4;
	rect.size.width = rect.size.width/2;

	return rect;
}

void planeLayer::plane_bomb()
{
	Animation* animation=Animation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero_blowup_n1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero_blowup_n2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero_blowup_n3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("hero_blowup_n4.png"));

	Animate* animate=Animate::create(animation);
	sp_hero->runAction(animate);
}
