#include "startScene.h"
#include "gameScene.h"
#include "controlLayer.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* startScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = startScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool startScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size xsize = Director::getInstance()->getWinSize();
    
	// 预加载图片资源
	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("ui/shoot_background.plist");
	cache->addSpriteFramesWithFile("ui/shoot.plist");
	
	Sprite *sp_bg = Sprite::createWithSpriteFrameName("background.png");
	sp_bg->setPosition(Vec2(xsize.width/2, xsize.height/2));
	addChild(sp_bg);
    
	//加入copyright
	Sprite* copyright=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("shoot_copyright.png"));
	copyright->setAnchorPoint(Vec2(0.5,0));
	copyright->setPosition(Vec2(xsize.width/2,xsize.height/2));
	this->addChild(copyright);

	Sprite *sp_loading = Sprite::createWithSpriteFrameName("game_loading1.png");
	sp_loading->setPosition(Vec2(xsize.width/2, xsize.height*0.45));
	addChild(sp_loading);

	// 加载loading动画
	cocos2d::Vector<SpriteFrame *> spfme = Vector<SpriteFrame *>::Vector();
	for (int i = 0; i < 4; ++i)
	{
		SpriteFrame *fname = cache->getSpriteFrameByName(
			cocos2d::String::createWithFormat("game_loading%d.png", i+1)->getCString() );
		spfme.pushBack(fname);
	}

	Animation * animation = Animation::createWithSpriteFrames(spfme, 0.2f);
	Animate* animate=CCAnimate::create(animation);
	Repeat* repeat=CCRepeat::create(animate,2);
	//RepeatForever *repeat = RepeatForever::create(animate);
	auto repeatdone=CallFunc::create(CC_CALLBACK_0(startScene::loadingDone, this));
	Sequence* sequence=Sequence::create(repeat,repeatdone,NULL);

	//sp_loading->runAction(repeat);
	sp_loading->runAction(sequence);

	// read config file.
	fileUnit::getInstance()->read_config_file();

    return true;
}

void startScene::loadingDone()
{
	CCLOG("loading scene.");
	preload_music();
	Director::getInstance()->replaceScene(gameScene::createScene());
}

// 预加载背景音乐和音效文件
void startScene::preload_music()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/game_music.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/bullet.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy1_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy2_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy3_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/game_over.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/get_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/get_double_laser.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/use_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/big_spaceship_flying.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/achievement.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/out_porp.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/button.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3",true);
}



/*
 *	gameoverScene 
 */
Scene* gameoverScene::createScene(int nscore)
{
	auto scene = Scene::create();
	auto layer = gameoverScene::create();
	
	layer->show_game_score(nscore);
	scene->addChild(layer);

	return scene;
}

bool gameoverScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size xsize = Director::getInstance()->getVisibleSize();

	// background
	Sprite* background=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gameover.png"));
	background->setPosition(Vec2(xsize.width/2,xsize.height/2));
	this->addChild(background);

	// show back game menuitem. 
	Sprite* normalBackToGame=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btn_finish.png"));
	Sprite* pressedBackToGame=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btn_finish.png"));
	MenuItemSprite *menuitem = MenuItemSprite::create(
	normalBackToGame,pressedBackToGame,CC_CALLBACK_0(gameoverScene::back_game_callback, this) );
	menuitem->setPosition(Vec2(xsize.width-normalBackToGame->getContentSize().width/2-10,normalBackToGame->getContentSize().height/2+10));
	Menu *menuBack=Menu::create(menuitem,nullptr);
	menuBack->setPosition(Vec2::ZERO);
	this->addChild(menuBack);

	// show score 
	Label *score_label = Label::createWithBMFont("fonts/font.fnt", String::createWithFormat("%d",_game_score)->getCString() );
	score_label->setPosition(Vec2(xsize.width/2, xsize.height/2));
	score_label->setColor(Color3B(143,146,147));
	this->addChild(score_label, 0, nodeTag::game_over_score);

	// show history best score.
	Label *best_score_label = Label::createWithBMFont("fonts/font.fnt", 
		String::createWithFormat("%d", fileUnit::getInstance()->get_best_score())->getCString());
	best_score_label->setColor(ccc3(143,146,147));
	best_score_label->setAnchorPoint(ccp(0,0.5));
	best_score_label->setPosition(Vec2(140,xsize.height-30));
	this->addChild(best_score_label);

	//////////////////////////////////////////////////////////////////////////
	// 移动设备键盘按键响应事件
	EventDispatcher *dispach = CCDirector::getInstance()->getEventDispatcher();
	auto keyboardlisten = EventListenerKeyboard::create();
	keyboardlisten->onKeyPressed = CC_CALLBACK_2(gameoverScene::onKeyPressed, this);
	keyboardlisten->onKeyReleased = CC_CALLBACK_2(gameoverScene::onKeyReleased, this);

	dispach->addEventListenerWithSceneGraphPriority(keyboardlisten,this);

	return true;
}

void gameoverScene::back_game_callback()
{
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1.f,gameScene::createScene()));
}

void gameoverScene::show_game_score( int nscore )
{
	this->_game_score = nscore;
	((Label *)this->getChildByTag(nodeTag::game_over_score))->setString(
		String::createWithFormat("%d",nscore)->getCString());

	// update the best score.
	fileUnit::getInstance()->update_best_score(this->_game_score);
	fileUnit::getInstance()->save_config_file();
}

// 键盘事件 
void gameoverScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
}

void gameoverScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		CCLOG("exit game. ");
		fileUnit::getInstance()->save_config_file();
		Director::getInstance()->end();
	}
}

