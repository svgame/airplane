#include "menuLayer.h"
#include "gameScene.h"

using namespace cocos2d;

menuLayer::menuLayer()
{
	_game_scores = 0;
}
menuLayer::~menuLayer()
{
}

bool menuLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Size xsize = Director::getInstance()->getVisibleSize();

	/* 暂停 按钮 */
	Sprite *sp_pause_normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_nor.png"));
	Sprite *sp_pause_selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_pressed.png"));

	sp_menu_pause = MenuItemSprite::create(
		sp_pause_normal, sp_pause_selected, CC_CALLBACK_0(menuLayer::menu_pause_callback, this) );
	sp_menu_pause->setPosition( Vec2(sp_pause_normal->getContentSize().width/2+10, xsize.height - sp_pause_normal->getContentSize().height/2-10));
	
	Menu *menu = Menu::create(sp_menu_pause, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0, nodeTag::menu_pause);

	// 游戏分数显示
	Label *label = Label::createWithBMFont("fonts/font.fnt", 
		String::createWithFormat("%d",_game_scores)->getCString());
	label->setColor(Color3B(143,146,147));
	label->setAnchorPoint(Vec2(0,0.5));
	label->setPosition(Vec2(sp_menu_pause->getPositionX() + sp_pause_normal->getContentSize().width, sp_menu_pause->getPositionY()));
	this->addChild(label, 0, nodeTag::menu_scores);

	return true;
}

void menuLayer::menu_pause_callback()
{
	if (!Director::getInstance()->isPaused())
	{
		// 更新暂停游戏按钮显示状态
		Sprite *sp_pause_normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png"));
		Sprite *sp_pause_selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png"));
		sp_menu_pause->setNormalImage(sp_pause_normal);
		sp_menu_pause->setSelectedImage(sp_pause_selected);
		// 暂停游戏
		Director::getInstance()->pause();
	}
	else
	{
		// 更新恢复游戏按钮显示状态
		Sprite *sp_resume_normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_nor.png"));
		Sprite *sp_resume_selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_pressed.png"));
		sp_menu_pause->setNormalImage(sp_resume_normal);
		sp_menu_pause->setSelectedImage(sp_resume_selected);
		// 恢复游戏
		Director::getInstance()->resume();
	}
}

void menuLayer::update_game_scores( int nsocre )
{
	_game_scores += nsocre;
	((gameScene *)this->getParent())->update_game_score(_game_scores);

	Label *sp_label = (Label *)this->getChildByTag(nodeTag::menu_scores);
	if (sp_label)
	{
		sp_label->setString(String::createWithFormat("%d",_game_scores)->getCString());
	}
}







