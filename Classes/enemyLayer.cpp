#include "enemyLayer.h"

/**
 *  enemySmall 实现
 */
enemySmall::enemySmall()
{
	bomb_animation_name = "enemy1_down";
	enemy_hp = 1;
	refresh_interval = 0.5f;
	enemy_sprite_name = "enemy1.png";
	enemy_move_animation_name.clear();
	init();
}

void enemySmall::init()
{
	// 预加载敌机爆炸动画资源。
	cocos2d::Animation *animation = cocos2d::Animation::create();
	animation->setDelayPerUnit(0.1f);	// 设置帧间间隔时间 **
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));

	cocos2d::AnimationCache::getInstance()->addAnimation(animation, bomb_animation_name);
}

/**
 *  enemyMedium 实现
 */
enemyMedium::enemyMedium()
{
	enemy_hp = 3;
	refresh_interval = 5.f;
	enemy_sprite_name = "enemy2.png";
	bomb_animation_name = "enemy2_down";
	enemy_move_animation_name.clear();
	init();
}

void enemyMedium::init()
{
	// 预加载敌机爆炸动画资源。
	cocos2d::Animation *animation = cocos2d::Animation::create();
	animation->setDelayPerUnit(0.1f);	// 设置帧间间隔时间 **
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));

	cocos2d::AnimationCache::getInstance()->addAnimation(animation, bomb_animation_name);
}


/**
 *  enemyLarge 实现
 */
enemyLarge::enemyLarge()
{
	enemy_hp = 25;
	refresh_interval = 40.f;
	enemy_sprite_name = "enemy3_n1.png";
	bomb_animation_name = "enemy3_down";
	enemy_move_animation_name = "enemy3_move";
	init();
}

void enemyLarge::init()
{
	// 预加载敌机爆炸动画资源。
	cocos2d::Animation *animation = cocos2d::Animation::create();
	animation->setDelayPerUnit(0.1f);	// 设置帧间间隔时间 **
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png"));
	animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png"));

	cocos2d::AnimationCache::getInstance()->addAnimation(animation, bomb_animation_name);

	Animation* animation_move=CCAnimation::create();
	animation_move->setDelayPerUnit(0.2f);
	animation_move->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
	animation_move->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
	
	cocos2d::AnimationCache::getInstance()->addAnimation(animation_move, enemy_move_animation_name);
}