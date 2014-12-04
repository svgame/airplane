#include "bulletLayer.h"
#include "planeLayer.h"

using namespace cocos2d;

bulletLayer::bulletLayer()
	:bullet_atk(1)	// Ĭ�ϳ�ʼ��ʱ�ɻ��ӵ��Ĺ�����Ϊ1
{
	sp_bullet_array.clear(); 
	sp_batch_bullet = nullptr;
}
bulletLayer::~bulletLayer()
{
	sp_bullet_array.clear();
}
// on "init" you need to initialize your instance
bool bulletLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	Size xsize = Director::getInstance()->getVisibleSize();

	// ������Ⱦ����
	sp_batch_bullet = SpriteBatchNode::create("ui/shoot.png");
	this->addChild(sp_batch_bullet);

	//������Ϸ
	start_pass();

	return true;
}

void bulletLayer::add_bullet( float dt )
{
	Size xsize = Director::getInstance()->getVisibleSize();
	Sprite *sp_bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	sp_batch_bullet->addChild(sp_bullet);

	Sprite * sp_hero= (Sprite *)(this->getParent()->getChildByTag(2))->getChildByTag(10);
	Vec2 curpos = sp_hero->getPosition() + Vec2(0, sp_hero->getContentSize().height/2);
	sp_bullet->setPosition(curpos);
	sp_bullet_array.push_back(sp_bullet);

	float xheight = xsize.height - curpos.y;
	float xspeed = xheight/320; /* �����ӵ�����е�ʱ�� */

	MoveTo *move = MoveTo::create(xspeed, Vec2(sp_bullet->getPositionX(), xsize.height));
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(bulletLayer::bullet_shoot_end, this, sp_bullet));
	sp_bullet->runAction(Sequence::create(move, callback, nullptr));
}

void bulletLayer::start_pass( bool decision )
{
	static bool b_game_start = false;
	if (!b_game_start && decision)
	{
		// ��ʼ��Ϸ <����������>
		b_game_start = true;
		schedule(schedule_selector(bulletLayer::add_bullet), 0.15f);
	}
	else if (b_game_start && !decision)
	{
		// ��ͣ��Ϸ <ͣ�õ�������ʹ��>
		b_game_start = false;
		unschedule(schedule_selector(bulletLayer::add_bullet));
	}
}

void bulletLayer::bullet_shoot_end(Sprite *psender)
{
	if(psender != nullptr)
	{
		Sprite* bullet=(Sprite*)psender;

		sp_bullet_array.remove(bullet);
		this->sp_batch_bullet->removeChild(bullet,true);
	}
}




