#include "enemyLayer.h"
#include "bulletLayer.h"
#include "planeLayer.h"
#include "gameScene.h"
#include "menuLayer.h"

using namespace cocos2d;

enemyLayer::enemyLayer()
{
	sp_enemy_list.clear(); 
}
enemyLayer::~enemyLayer()
{
	sp_enemy_list.clear(); 
}

bool enemyLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size xsize = Director::getInstance()->getVisibleSize();

	//add_enemy();
	schedule(schedule_selector(enemyLayer::enemy_insert), 0.5f);

	// 预加载敌机爆炸动画资源。
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);	// 设置帧间间隔时间 **
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));

	AnimationCache::getInstance()->addAnimation(animation, "enemy1_down");

	// 加入 敌机是否被击中判定 调度器
	schedule(schedule_selector(enemyLayer::enemy_shoot_update), 0.05f);

	return true;
}

void enemyLayer::enemy_insert(float dt)
{
	float rand_fn = cocos2d::random<float>(0.05f,0.95f);

	Size xsize = Director::getInstance()->getVisibleSize();
	enemySprite *sp_enemy = enemySprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1.png") );
		//(enemySprite *)enemySprite::createWithSpriteFrameName("enemy1.png");
	sp_enemy->set_hp(1);	// 显式设置敌机生命值. 不设置默认=1 
	sp_enemy->setPosition(Vec2(xsize.width*rand_fn, xsize.height));
	this->addChild(sp_enemy);

	sp_enemy_list.push_back(sp_enemy);

	float xheight = xsize.height;
	float xspeed = xheight/320*(cocos2d::random<float>(0.5f,1.2f)); /* 计算敌机需飞行的时间 */

	MoveTo *move = MoveTo::create(xspeed, Vec2(sp_enemy->getPositionX(), 0));
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(enemyLayer::enemy_remove, this, sp_enemy));
	sp_enemy->runAction(Sequence::create(move, callback, nullptr));
	
}

void enemyLayer::enemy_remove( enemySprite *sp )
{
 	if (sp != nullptr)
 	{
		sp_enemy_list.remove(sp);
		this->removeChild(sp);
	}
}

void enemyLayer::enemy_bomb_clean( enemySprite *sp )
{
	if (sp != nullptr)
	{
		//sp_enemy_list.remove(sp); // 这步操作提前到爆炸动画播放前完成
		this->removeChild(sp);
	}
}
void enemyLayer::enemy_bomb(enemySprite* enemy)  
{  
	// 爆炸动作播放前，先将该敌机从敌机列表中踢出
	sp_enemy_list.remove(enemy);
	// 敌机被击中，先停止该敌机的所有动作，然后播放爆炸动作特效
	enemy->stopAllActions();

	Animation *animation = AnimationCache::getInstance()->getAnimation("enemy1_down");
	Animate *animate = Animate::create(animation);
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(enemyLayer::enemy_remove, this, enemy));

	enemy->runAction(Sequence::create(animate, callback, nullptr));

	// 更新游戏分数
	menuLayer *menu = (menuLayer *)this->getParent()->getChildByTag(nodeTag::menu_layer);
	menu->update_game_scores(100);
}

void enemyLayer::enemy_remove_all()
{
 	std::list<enemySprite *>::iterator iter = sp_enemy_list.begin();
 	for (iter; iter != sp_enemy_list.end(); )
 	{
 		enemy_bomb(*iter++);
 	}
}

void enemyLayer::enemy_shoot_update( float dt )
{
	enemy_shoot_judge();
}

void enemyLayer::enemy_shoot_judge()
{
	bulletLayer *bullet = (bulletLayer *)this->getParent()->getChildByTag(nodeTag::bullet);
	planeLayer *plane = (planeLayer *)this->getParent()->getChildByTag(nodeTag::plane);
	

	std::list<enemySprite *>::iterator iter = sp_enemy_list.begin();
	for (iter; iter != sp_enemy_list.end(); /*waring: iter++ 不能放在此处 */)
	{
		enemySprite *enemy = *iter++;
		if (plane->plane_crash_judge(enemy))
		{
			// todo: 主飞机发生爆炸/ 游戏该结束了。
			enemy_bomb(enemy);
		}
		else if (bullet->bullet_shoot_judge(enemy))
		{
			// 敌机被子弹击中，根据血量判定是否发生爆炸
			enemy->lose_hp(bullet->get_bullet_atk());
			if (enemy->get_hp() < 1)
			{
				enemy_bomb(enemy);
			}
		}
	}
}




