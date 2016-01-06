//Super Stardust for pc by yibojiang is licensed under a Creative Commons ����-����ҵ��ʹ��-��ͬ��ʽ���� 3.0 Unported License.
#pragma once
#include <list>

#include "Bullet.h"
 

class BulletManager:public ObjectManager
{
public:

	//����
	SINGLETON(BulletManager);

	//������������ӵ�
	std::list<Bullet*> bulletList;

	//�������ĵ����ӵ�
	std::list<Bullet*> enemyBulletList;

	//��Ⱦ����
	void AddTime(Real deltaTime);
	void Reset();
	BulletManager(void);
	~BulletManager(void);

	
};

