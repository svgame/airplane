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
private:
	bulletLayer(){sp_bullet_array.clear(); sp_batch_bullet = nullptr; };
	~bulletLayer(){sp_bullet_array.clear(); };

	void add_bullet(float dt);
	void bullet_shoot_end(cocos2d::Sprite *psender);	/* 子弹射击结束处理，回收资源 */

	cocos2d::SpriteBatchNode *sp_batch_bullet;
	std::list<cocos2d::Sprite *> sp_bullet_array;
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