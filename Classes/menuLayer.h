#pragma once
#include "cocos2d.h"

class menuLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(menuLayer);
	virtual bool init();

	void update_game_scores(int nsocre);
private:
	menuLayer();
	~menuLayer();

	cocos2d::MenuItemSprite *sp_menu_pause;
	void menu_pause_callback();

	int _game_scores;
};

