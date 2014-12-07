#pragma once
#include "cocos2d.h"
#include "enemySprite.h"

#include "bulletLayer.h"
#include "planeLayer.h"
#include "gameScene.h"
#include "controlLayer.h"

#include "SimpleAudioEngine.h"
using namespace cocos2d;

//Large,medium or small
/**
 *	�л�ʵ������<ģ��>
 */
class enemyType
{
public:
	enemyType(){};
	~enemyType(){};
	//virtual void init() {};	//�л��漰�����ж�������init() ��Ԥ����
	virtual int get_enemy_hp() = 0;		// �л�����ֵ
	virtual int get_score_ratio() = 0;	// �л��������� <ʵ�ʷ���=ration*100>
	virtual float get_refresh_interval() = 0;	// �л�ˢ��ʱ����
	virtual float get_move_speed() = 0;	// �л������ٶ�<���ط���������ʱ��>
	virtual std::string get_enemy_sprite_name() = 0;	// �л���������
	virtual std::string get_bomb_animation_name() =0;	// �л���ը��������
	virtual std::string get_move_animation_name() = 0;	// �л��ƶ��������ƣ�û�ж���ֱ�ӷ��ؿ��ַ���
};
/*
 *  �л�ʵ������
 */
class enemySmall:public enemyType
{
public:
	enemySmall();
	~enemySmall(){};

	int get_enemy_hp(){ return enemy_hp; };
	int get_score_ratio() { return get_enemy_hp()*5; };
	float get_refresh_interval() {return refresh_interval;}
	std::string get_enemy_sprite_name() { return enemy_sprite_name; };
	std::string get_bomb_animation_name() {  return bomb_animation_name;};
	std::string get_move_animation_name() { return enemy_move_animation_name; };
	float get_move_speed() { return 3.f*cocos2d::random<float>(0.5f,1.2f); }
private:
	void init();

	int enemy_hp;
	float refresh_interval;	// ˢ��ʱ����
	std::string bomb_animation_name;
	std::string enemy_sprite_name;
	std::string enemy_move_animation_name;
};

class enemyMedium:public enemyType
{
public:
	enemyMedium();
	~enemyMedium(){};

	int get_enemy_hp(){ return enemy_hp; };
	int get_score_ratio() { return get_enemy_hp()*10; };
	float get_refresh_interval() {return refresh_interval;}
	std::string get_enemy_sprite_name() { return enemy_sprite_name; };
	std::string get_bomb_animation_name() {  return bomb_animation_name;};
	std::string get_move_animation_name() { return enemy_move_animation_name; };
	float get_move_speed() { return 4.f*cocos2d::random<float>(0.5f,1.2f); }
private:
	void init();

	int enemy_hp;
	float refresh_interval;	// ˢ��ʱ����
	std::string bomb_animation_name;
	std::string enemy_sprite_name;
	std::string enemy_move_animation_name;
};

class enemyLarge:public enemyType
{
public:
	enemyLarge();
	~enemyLarge(){};

	int get_enemy_hp(){ return enemy_hp; };
	int get_score_ratio() { return get_enemy_hp()*25; };
	float get_refresh_interval() {return refresh_interval;}
	std::string get_enemy_sprite_name() { return enemy_sprite_name; };
	std::string get_bomb_animation_name() {  return bomb_animation_name;};
	std::string get_move_animation_name() { return enemy_move_animation_name; };
	float get_move_speed() { return 10.f; }

private:
	void init();

	int enemy_hp;
	float refresh_interval;	// ˢ��ʱ����
	std::string bomb_animation_name;
	std::string enemy_sprite_name;
	std::string enemy_move_animation_name;
};

/** 
 *  �л�ģ�嶨��
 */
template<class enemyType>
class enemyLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(enemyLayer);
	virtual bool init();

	void enemy_remove_all();	// ��������������Ļ�ϵĵл�������ը
protected:
	enemyLayer() { sp_enemy_list.clear(); };
	~enemyLayer() { sp_enemy_list.clear(); };

	void enemy_insert(float dt);
	void enemy_remove(enemySprite *sp);	// �Ƴ�ָ���л�

	void enemy_bomb(enemySprite *enemy); // ָ���л�������ը
	void enemy_bomb_clean(enemySprite *sp);	// ָ���л���ը������������

	void enemy_shoot_update(float dt);	/* schedule update �ӵ������ж� */
	void enemy_shoot_judge();	/* �л����ӵ������ж� */

	std::list<enemySprite *> sp_enemy_list;
	
	// �л�ʵ��
	enemyType enemy_type;
};

/** 
 *  �л�ģ��ʵ��
 */
template<class enemyType>
bool enemyLayer<enemyType>::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size xsize = Director::getInstance()->getVisibleSize();

	//add_enemy();
	schedule(schedule_selector(enemyLayer::enemy_insert), enemy_type.get_refresh_interval());

	// ���� �л��Ƿ񱻻����ж� ������
	schedule(schedule_selector(enemyLayer::enemy_shoot_update), 0.05f);

	return true;
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_insert(float dt)
{
	float rand_fn = cocos2d::random<float>(0.05f,0.95f);

	Size xsize = Director::getInstance()->getVisibleSize();
	enemySprite *sp_enemy = enemySprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(enemy_type.get_enemy_sprite_name() ) );
	
	sp_enemy->set_hp(enemy_type.get_enemy_hp());	// ��ʽ���õл�����ֵ. ������Ĭ��=1 
	sp_enemy->setPosition(Vec2(xsize.width*rand_fn, xsize.height));
	this->addChild(sp_enemy);

	sp_enemy_list.push_back(sp_enemy);

	float xheight = xsize.height;
	float xspeed = enemy_type.get_move_speed(); //xheight/320*(cocos2d::random<float>(0.5f,1.2f)); /* ����л�����е�ʱ�� */

	MoveTo *move = MoveTo::create(xspeed, Vec2(sp_enemy->getPositionX(), 0));
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(enemyLayer::enemy_remove, this, sp_enemy));
	sp_enemy->runAction(Sequence::create(move, callback, nullptr));

	// -..
	if (!enemy_type.get_move_animation_name().empty())
	{
		// ִ�б�ը����
		Animation *animation = AnimationCache::getInstance()->getAnimation(enemy_type.get_move_animation_name());
		Animate *animate = Animate::create(animation);
		sp_enemy->runAction(RepeatForever::create(animate));
	}
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_remove( enemySprite *sp )
{
	if (sp != nullptr)
	{
		sp_enemy_list.remove(sp);
		this->removeChild(sp);
	}
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_bomb_clean( enemySprite *sp )
{
	if (sp != nullptr)
	{
		//sp_enemy_list.remove(sp); // �ⲽ������ǰ����ը��������ǰ���
		this->removeChild(sp);
	}
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_bomb(enemySprite* enemy)  
{  
	// ��ը��������ǰ���Ƚ��õл��ӵл��б����߳�
	sp_enemy_list.remove(enemy);
	// �л������У���ֹͣ�õл������ж�����Ȼ�󲥷ű�ը������Ч
	enemy->stopAllActions();

	//������Ч
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy1_down.mp3");

	// ִ�б�ը����
	Animation *animation = AnimationCache::getInstance()->getAnimation(enemy_type.get_bomb_animation_name());
	Animate *animate = Animate::create(animation);
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(enemyLayer::enemy_remove, this, enemy));

	enemy->runAction(Sequence::create(animate, callback, nullptr));

	// ������Ϸ����
	menuLayer *menu = (menuLayer *)this->getParent()->getChildByTag(nodeTag::menu_layer);
	menu->update_game_scores( enemy_type.get_score_ratio()*100 );
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_remove_all()
{
	std::list<enemySprite *>::iterator iter = sp_enemy_list.begin();
	for (iter; iter != sp_enemy_list.end(); )
	{
		enemy_bomb(*iter++);
	}
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_shoot_update( float dt )
{
	enemy_shoot_judge();
}

template<class enemyType>
void enemyLayer<enemyType>::enemy_shoot_judge()
{
	bulletLayer *bullet = (bulletLayer *)this->getParent()->getChildByTag(nodeTag::bullet);
	planeLayer *plane = (planeLayer *)this->getParent()->getChildByTag(nodeTag::plane);

	std::list<enemySprite *>::iterator iter = sp_enemy_list.begin();
	for (iter; iter != sp_enemy_list.end(); /*waring: iter++ ���ܷ��ڴ˴� */)
	{
		enemySprite *enemy = *iter++;
		if (plane->plane_crash_judge(enemy))
		{
			//���ɻ�������ը
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
