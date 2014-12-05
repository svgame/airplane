#pragma once
#include "cocos2d.h"

class bulletLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(bulletLayer);
	virtual bool init();

	void start_pass(bool decision = true);	/* <开始|暂停游戏> true: 开始，false: 暂停*/
	/* 
	 *  子弹的射击判定 ,敌机与子弹层上所有子弹的碰撞检测 
	 *  如果有子弹与该敌机发生碰撞 return true; 否则 return false;
	 */
	template<class sprite>
	bool bullet_shoot_judge(sprite *enemy);

	//设置子弹攻击力属性
	void set_bullet_atk(int atk) { bullet_atk = atk; };
	int get_bullet_atk() { return bullet_atk; };
private:
	bulletLayer();
	~bulletLayer();

	void bullet_insert(float dt);
	void bullet_shoot_end(cocos2d::Sprite *psender);	/* 子弹射击结束处理，回收资源 */

	cocos2d::SpriteBatchNode *sp_batch_bullet;
	std::list<cocos2d::Sprite *> sp_bullet_array;

	// 子弹攻击力属性
	int bullet_atk;
};


template<class sprite>
bool bulletLayer::bullet_shoot_judge( sprite *enemy )
{
	bool bret = false;
	std::list<Sprite *>::iterator iter = sp_bullet_array.begin();
	for (iter; iter != sp_bullet_array.end(); /*waring: iter++ 不能放在此处 */)
	{
		if ((*iter)->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
		{
			bret = true;
			bullet_shoot_end(*iter++);
		}
		else
		{
			iter++;
		}
	}

	return bret;
}