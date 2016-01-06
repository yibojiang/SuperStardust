#pragma once
#include "Bullet.h"
class BulletConfig
{
public:
	int shotSound;
	int col;
	int fireRate;
	int fireToggle;
	int damage;
	int lifeTime;
	int curLevel;
	int bulletCount;
	Real turnRate;//ת��ʱ��
	Bullet *bulletArray;
	Degree rangeDegree;//������Χ

	
	

	BulletConfig(void)
	{

	}
	virtual ~BulletConfig(void)
	{
		delete[] bulletArray;
	}

	virtual void Upgrade(int level)=0;
protected:
	SceneManager *sceneMgr;
};

