#include "bulletLayer.h"
#include "planeLayer.h"
#include "gameScene.h"

#include "SimpleAudioEngine.h"

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
	schedule(schedule_selector(bulletLayer::bullet_insert), 0.15f);

	return true;
}

void bulletLayer::bullet_insert( float dt )
{
	//������Ч
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/bullet.mp3");

	Size xsize = Director::getInstance()->getVisibleSize();
	// ����ӵ�����
	Sprite *sp_bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	sp_batch_bullet->addChild(sp_bullet);

	// �����ӵ�����ĳ�ʼλ����ɻ���ǰ��λ��
	Sprite * sp_hero= (Sprite *)(this->getParent()->getChildByTag(nodeTag::plane))->getChildByTag(nodeTag::plane_sp);	
	Vec2 curpos = sp_hero->getPosition() + Vec2(0, sp_hero->getContentSize().height/2);
	sp_bullet->setPosition(curpos);
	sp_bullet_array.push_back(sp_bullet);

	/* �����ӵ�����е�ʱ��,Ϊ���÷ɻ����κεط�����������ӵ��ٶȶ�һ����
	 * ���Դ˴��ӵ����ٶȲ���ֱ���ù̶�ʱ��������
	*/
	float xheight = xsize.height - curpos.y;
	float xspeed = xheight/480; 

	// ִ���ӵ����� �������
	MoveTo *move = MoveTo::create(xspeed, Vec2(sp_bullet->getPositionX(), xsize.height));
	CallFunc *callback = CallFunc::create(CC_CALLBACK_0(bulletLayer::bullet_shoot_end, this, sp_bullet));
	sp_bullet->runAction(Sequence::create(move, callback, nullptr));
}

void bulletLayer::bullet_shoot_end(Sprite *bullet)
{
	if(bullet != nullptr)
	{
		sp_bullet_array.remove(bullet);
		this->sp_batch_bullet->removeChild(bullet,true);
	}
}




