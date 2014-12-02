#pragma once
#include "cocos2d.h"

class enemySprite : public cocos2d::Sprite
{
public:
	enemySprite();
	~enemySprite();
	static enemySprite* create();
	static enemySprite* createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
	virtual bool init(); 
	
	void set_hp(int hp){ enemy_hp = hp; };
	int get_hp(){ return enemy_hp; };
	void lose_hp(int hp = 1) { enemy_hp -= hp; };

private:
	int enemy_hp;	/*µĞ»úÉúÃüÖµ*/
};