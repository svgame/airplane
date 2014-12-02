#include "enemySprite.h"

using namespace cocos2d;

enemySprite::enemySprite()
{
	enemy_hp = 1;
}

enemySprite::~enemySprite()
{
	;
}
enemySprite* enemySprite::create()
{
	enemySprite *sprite = new (std::nothrow) enemySprite();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
enemySprite* enemySprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	enemySprite *sprite = new (std::nothrow) enemySprite();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool enemySprite::init()
{
	if ( !Sprite::init() )
	{
		return false;
	}

	return true;
}



