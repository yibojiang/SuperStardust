//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#include "BulletManager.h"

BulletManager::BulletManager()
{
	
}

BulletManager::~BulletManager(void)
{
	
}



void BulletManager::AddTime(Real deltaTime)
{
	//遍历玩家子弹
	for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end();)
	{

		if ((*it)->lifeTime<0)
			(*it)->isAlive=false;

		if ((*it)->isAlive)
		{
			(*it)->lifeTime-=10;
			(*it)->node->setPosition(Vector3(0,0,0));
			(*it)->node->translate((*it)->firePositon,Node::TS_LOCAL);		
			(*it)->node->rotate((*it)->rotateAxis,Degree((*it)->speed*deltaTime),Node::TS_LOCAL);

			it++;
		}
		else
		{
			(*it)->node->setPosition(Vector3(0,0,0));
			(*it)->node->setVisible(false);
			it=bulletList.erase(it);
		}
	}

	//遍历敌人子弹
	for (std::list<Bullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end();)
	{

		if ((*it)->lifeTime<0)
			(*it)->isAlive=false;

		if ((*it)->isAlive)
		{
			(*it)->lifeTime-=10;
			(*it)->node->setPosition(Vector3(0,0,0));
			(*it)->node->translate((*it)->firePositon,Node::TS_LOCAL);		
			(*it)->node->rotate((*it)->rotateAxis,Degree((*it)->speed*deltaTime),Node::TS_LOCAL);

			it++;
		}
		else
		{
			delete *it;
			it=enemyBulletList.erase(it);
		}
	}


}

void BulletManager::Reset()
{
	//Delete the player's bullet in playerManager.
	//for (std::list<Bullet*>::iterator it = bulletList.begin(); it != bulletList.end();)
	//{
	//	delete *it;
	//	it=bulletList.erase(it);
	//}
	bulletList.clear();
	for (std::list<Bullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end();)
	{
		delete *it;
		it=enemyBulletList.erase(it);
	}
	//enemyBulletList.clear();
}

