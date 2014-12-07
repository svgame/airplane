#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class startScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // implement the "static create()" method manually
    CREATE_FUNC(startScene);
private:
	void loadingDone();
	void preload_music();
};

class gameoverScene : public cocos2d::Layer
{
public:
	CREATE_FUNC(gameoverScene);
	static cocos2d::Scene* createScene(int nscore);
	virtual bool init(); 

	// ¼üÅÌÊÂ¼þ 
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
private:
	gameoverScene():_game_score(0){};
	~gameoverScene(){};

	void show_game_score(int nscore);
	void back_game_callback();
	int _game_score;
};

#endif // __HELLOWORLD_SCENE_H__
