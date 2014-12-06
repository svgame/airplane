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

	// Ԥ���صл���ը������Դ��
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);	// ����֡����ʱ�� **
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));

	AnimationCache::getInstance()->addAnimation(animation, "enemy1_down");

	// ���� �л��Ƿ񱻻����ж� ������
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
	sp_enemy->set_hp(1);	// ��ʽ���õл�����ֵ. ������Ĭ��=1 
	sp_enemy->setPosition(Vec2(xsize.width*rand_fn, xsize.height));
	this->addChild(sp_enemy);

	sp_enemy_list.push_back(sp_enemy);

	float xheight = xsize.height;
	float xspeed = xheight/320*(cocos2d::random<float>(0.5f,1.2f)); /* ����л�����е�ʱ�� */

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
		//sp_enemy_list.remove(sp); // �ⲽ������ǰ����ը��������ǰ���
		this->removeChild(sp);
	}
}
void enemyLayer::enemy_bomb(enemySprite* enemy)  
{  
	// ��ը��������ǰ���Ƚ��õл��ӵл��б����߳�
	sp_enemy_list.remove(enemy);
	// �л������У���ֹͣ�õл������ж�����Ȼ�󲥷ű�ը������Ч
	enemy->stopAllActions();

	Animation *animation = AnimationCache::getInstance()->getAnimation("enemy1_down");
	Animate *animate = Animate::create(animation);
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(enemyLayer::enemy_remove, this, enemy));

	enemy->runAction(Sequence::create(animate, callback, nullptr));

	// ������Ϸ����
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
	for (iter; iter != sp_enemy_list.end(); /*waring: iter++ ���ܷ��ڴ˴� */)
	{
		enemySprite *enemy = *iter++;
		if (plane->plane_crash_judge(enemy))
		{
			// todo: ���ɻ�������ը/ ��Ϸ�ý����ˡ�
			enemy_bomb(enemy);
		}
		else if (bullet->bullet_shoot_judge(enemy))
		{
			// �л����ӵ����У�����Ѫ���ж��Ƿ�����ը
			enemy->lose_hp(bullet->get_bullet_atk());
			if (enemy->get_hp() < 1)
			{
				enemy_bomb(enemy);
			}
		}
	}
}




