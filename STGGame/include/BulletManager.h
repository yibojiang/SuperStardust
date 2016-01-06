//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include <list>

#include "Bullet.h"
 

class BulletManager:public ObjectManager
{
public:

	//单件
	SINGLETON(BulletManager);

	//待遍历的玩家子弹
	std::list<Bullet*> bulletList;

	//待遍历的敌人子弹
	std::list<Bullet*> enemyBulletList;

	//渲染队列
	void AddTime(Real deltaTime);
	void Reset();
	BulletManager(void);
	~BulletManager(void);

	
};

