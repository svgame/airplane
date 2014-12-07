#include "controlLayer.h"
#include "gameScene.h"
#include "enemyLayer.h"

#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

//using namespace cocos2d::extension;

using namespace cocos2d;

menuLayer::menuLayer()
	:_ufo_counts(0)
	,_game_scores(0)
{
	//_game_scores = 0;
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

void menuLayer::update_game_scores( int nsocre_inc )
{
	_game_scores += nsocre_inc;
	//((gameScene *)this->getParent())->update_game_score(_game_scores);

	Label *sp_label = (Label *)this->getChildByTag(nodeTag::menu_scores);
	if (sp_label)
	{
		sp_label->setString(String::createWithFormat("%d",_game_scores)->getCString());
	}
}

void menuLayer::ufo_counts_update( int ncount /*= 1*/ )
{
	_ufo_counts += ncount;
	if (_ufo_counts < 0)
	{
		return ;
	}
	cocos2d::Node *sp_ufo = nullptr;
	if (!(sp_ufo = this->getChildByTag(nodeTag::ufo_counts)))
	{
		Sprite *sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb.png"));

		MenuItemSprite *menuitem = MenuItemSprite::create(
			sp,sp,CC_CALLBACK_0(menuLayer::ufo_touch_callback, this) );
		menuitem->setPosition(Vec2(sp->getContentSize().width/2+10,sp->getContentSize().height/2+10));
		Menu *menu = Menu::create(menuitem, nullptr);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 0, nodeTag::ufo_counts);

		sp_ufo = menu;
	}
	cocos2d::Label *sp_count = nullptr;
	if (!(sp_count = (Label *)this->getChildByTag(nodeTag::ufo_counts_label)))
	{
		Sprite *sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb.png"));

		Label *label = Label::createWithBMFont("fonts/font.fnt", 
			String::createWithFormat("X%d",_ufo_counts)->getCString());
		label->setColor(Color3B(143,146,147));
		label->setAnchorPoint(Vec2(0,0.5));
		label->setPosition(Vec2(sp->getContentSize().width*1.2, sp->getContentSize().height/2 + 5));
		this->addChild(label, 0, nodeTag::ufo_counts_label);

		sp_count = label;
	}
	sp_count->setString(String::createWithFormat("X%d",_ufo_counts)->getCString());

	if (_ufo_counts == 0)
	{
		sp_ufo->runAction(Hide::create());
		sp_count->runAction(Hide::create());
	}
	else
	{
		sp_ufo->runAction(Show::create());
		sp_count->runAction(Show::create());
	}

}

// ufo 功能实现
void menuLayer::ufo_touch_callback()
{
	if (!(Director::getInstance()->isPaused()))
	{
		// 清除屏幕上的敌机
		enemyLayer<enemySmall> *enemy_s = (enemyLayer<enemySmall> *)this->getParent()->getChildByTag(nodeTag::enemy_small);
		enemy_s->enemy_remove_all();
		enemyLayer<enemyMedium> *enemy_m = (enemyLayer<enemyMedium> *)this->getParent()->getChildByTag(nodeTag::enemy_medium);
		enemy_m->enemy_remove_all();
		enemyLayer<enemyLarge> *enemy_l = (enemyLayer<enemyLarge> *)this->getParent()->getChildByTag(nodeTag::enemy_large);
		enemy_l->enemy_remove_all();

		// 更新ufo数
		ufo_counts_update(-1);
	}
}



fileUnit *fileUnit::_file = nullptr;

// 单例模式，此处未做线程安全处理，所以只适用于单线程
fileUnit * fileUnit::getInstance()
{
	if(!_file)
	{
		// todo: 需线程安全处理

		if(!_file)
		{
			static fileUnit _inst;
			_file = &_inst;
		}
	}
	return _file;
}

void fileUnit::read_config_file()
{
	std::string filePath = FileUtils::getInstance()->getWritablePath() + "config.xml";
	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	XMLError errorId = pDoc->LoadFile(filePath.c_str());

	if (errorId != 0) {
		//xml格式错误
		return;
	}

	XMLElement *rootElem = pDoc->RootElement();

	XMLElement *scoresElem = rootElem->FirstChildElement("scores");
	// 读取历史最高分数记录。
	game_best_score = scoresElem->IntAttribute("best_score");

	delete pDoc;
}

void fileUnit::save_config_file()
{
	std::string filePath = FileUtils::getInstance()->getWritablePath() + "config.xml";
	CCLOG(filePath.c_str());
	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();

	//xml 声明（参数可选）
	XMLDeclaration *pDel = pDoc->NewDeclaration();

	pDoc->LinkEndChild(pDel);

	//添加<config>节点
	XMLElement *plistElement = pDoc->NewElement("config");
	pDoc->LinkEndChild(plistElement);

	//添加 <config>/<scores> 节点
	XMLElement *scoreElement = pDoc->NewElement("scores");
	plistElement->LinkEndChild(scoreElement);
	scoreElement->SetAttribute("best_score", String::createWithFormat("%d", game_best_score)->getCString());

	pDoc->SaveFile(filePath.c_str());
	delete pDoc;
}

