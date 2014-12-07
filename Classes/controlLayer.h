#pragma once
#include "cocos2d.h"

class menuLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(menuLayer);
	virtual bool init();

	void update_game_scores(int nsocre_inc);
	int get_game_scores() { return _game_scores; };

	void ufo_counts_update(int ncount = 1);
	void ufo_touch_callback();
private:
	menuLayer();
	~menuLayer();

	cocos2d::MenuItemSprite *sp_menu_pause;
	void menu_pause_callback();

	// game score
	int _game_scores;
	//ufo 数量统计
	int _ufo_counts;
};

class fileUnit
{
public:
	static fileUnit *getInstance();

	void read_config_file();
	void save_config_file();

	void update_best_score(int nsocre){ game_best_score = (nsocre > game_best_score)?nsocre:game_best_score; };
	int get_best_score() { return game_best_score; };
private:
	fileUnit():game_best_score(0),game_score(0){};
	~fileUnit(){};
	static fileUnit *_file;

	//
	int game_best_score;
	int game_score;
};