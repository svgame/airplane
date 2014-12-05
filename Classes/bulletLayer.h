#pragma once
#include "cocos2d.h"

class bulletLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(bulletLayer);
	virtual bool init();

	void start_pass(bool decision = true);	/* <��ʼ|��ͣ��Ϸ> true: ��ʼ��false: ��ͣ*/
	/* 
	 *  �ӵ�������ж� ,�л����ӵ����������ӵ�����ײ��� 
	 *  ������ӵ���õл�������ײ return true; ���� return false;
	 */
	template<class sprite>
	bool bullet_shoot_judge(sprite *enemy);

	//�����ӵ�����������
	void set_bullet_atk(int atk) { bullet_atk = atk; };
	int get_bullet_atk() { return bullet_atk; };
private:
	bulletLayer();
	~bulletLayer();

	void bullet_insert(float dt);
	void bullet_shoot_end(cocos2d::Sprite *psender);	/* �ӵ������������������Դ */

	cocos2d::SpriteBatchNode *sp_batch_bullet;
	std::list<cocos2d::Sprite *> sp_bullet_array;

	// �ӵ�����������
	int bullet_atk;
};


template<class sprite>
bool bulletLayer::bullet_shoot_judge( sprite *enemy )
{
	bool bret = false;
	std::list<Sprite *>::iterator iter = sp_bullet_array.begin();
	for (iter; iter != sp_bullet_array.end(); /*waring: iter++ ���ܷ��ڴ˴� */)
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