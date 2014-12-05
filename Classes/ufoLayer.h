#pragma once
#include "cocos2d.h"

class ufoLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(ufoLayer);
	virtual bool init();

private:
	ufoLayer();
	~ufoLayer();

	void ufo_insert(float dt);
	void ufo_remove(cocos2d::Sprite *sp);

	void ufo_crash_update(float dt);
	void ufo_crash_jude();

	cocos2d::Sprite *sp_ufo;
	std::list<cocos2d::Sprite *> sp_ufo_list;
};

