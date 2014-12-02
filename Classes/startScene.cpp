#include "startScene.h"
#include "gameScene.h"

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
