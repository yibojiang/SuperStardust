//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "EnemyCannon.h"
#include "EnemyPyramid.h"
#include "EnemyBoss01.h"
EnemyManager::EnemyManager(void)
{

}

EnemyManager::~EnemyManager(void)
{
	

}




void EnemyManager::SetupContent(Enemy& enemy)
{

}


void EnemyManager::Init()
{
	sceneMgr=INSTANCE(WorldManager)->GetSceneManager();

}

void EnemyManager::GeneratePryamid(int count,Degree distanceDegree)
{
	SceneNode *node=INSTANCE(PlayerManager)->player->node;


	Degree degree=Degree(360/count);

	Vector3 dir=Vector3(0,-1,0);
	Real x,y;
	x=0;
	y=-1;

	for (int i=0;i<count;i++)
	{

		dir.x=x*cos(degree.valueRadians()*i)-y*sin(degree.valueRadians()*i);
		dir.y=x*sin(degree.valueRadians()*i)+y*cos(degree.valueRadians()*i);

		Enemy* enemy=&AddEnemy(EnemyType::PRYAMID,Vector3(0,0,0));

		enemy->rotateAxis=node->convertLocalToWorldPosition(dir).crossProduct(node->getPosition()).normalisedCopy();

		if (i%2)
		{
			enemy->isTracing=true;
		}

		enemy->node->rotate(enemy->rotateAxis,distanceDegree,Node::TS_LOCAL);
		enemy->node->translate(node->getPosition()*enemy->spawnTime,Node::TS_LOCAL);		

		enemy->node->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);

	}

}

void EnemyManager::DropPryamid(Degree directionDegree,Degree distanceDegree,int count)
{
	if (count>0)
	{
		SceneNode *node=INSTANCE(PlayerManager)->player->node;
		directionDegree=-directionDegree;
		Vector3 dir=Vector3(0,-1,0);
		Real x,y;
		x=0;
		y=-1;

		dir.x=x*cos(directionDegree.valueRadians()*1)-y*sin(directionDegree.valueRadians()*1);
		dir.y=x*sin(directionDegree.valueRadians()*1)+y*cos(directionDegree.valueRadians()*1);

		Enemy* enemy=&AddEnemy(EnemyType::PRYAMID,Vector3(0,0,0));

		enemy->rotateAxis=node->convertLocalToWorldPosition(dir).crossProduct(node->getPosition()).normalisedCopy();

		enemy->node->rotate(enemy->rotateAxis,distanceDegree,Node::TS_LOCAL);
		enemy->node->translate(node->getPosition()*enemy->spawnTime,Node::TS_LOCAL);		

		enemy->node->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);

	}

}

void EnemyManager::GenerateCannon(int count,Degree distanceDegree)
{
	SceneNode *node=INSTANCE(PlayerManager)->player->node;

	Degree degree=Degree(360/count);

	Vector3 dir=Vector3(0,-1,0);
	Real x,y;
	x=0;
	y=-1;

	for (int i=0;i<count;i++)
	{
		dir.x=x*cos(degree.valueRadians()*i)-y*sin(degree.valueRadians()*i);
		dir.y=x*sin(degree.valueRadians()*i)+y*cos(degree.valueRadians()*i);

		Enemy* enemy=&AddEnemy(EnemyType::CANNON,Vector3(0,0,0));

		enemy->rotateAxis=node->convertLocalToWorldPosition(dir).crossProduct(node->getPosition()).normalisedCopy();


		enemy->node->rotate(enemy->rotateAxis,distanceDegree,Node::TS_LOCAL);
		enemy->node->translate(node->getPosition()*enemy->spawnTime,Node::TS_LOCAL);		

		enemy->node->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);

	}

}

void EnemyManager::AddTime(Real deltaTime)
{
	FlockingHandler();
	
	for (std::list<Enemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{

		if ((*it)->isAlive)
		{
			if ((*it)->healthPoint<0)
			{
				(*it)->isAlive=false;
				(*it)->enemyState=EnemyState::DYING;
			}

			(*it)->AddTime(deltaTime);
			it++;
		}
		else
		{

			delete *it;//TODO
			
			it=enemyList.erase(it);


		}

	}

}


void EnemyManager::FlockingHandler()
{
	Real AI_U,AI_A,AI_B,AI_n,AI_m;
	AI_A=2000;
	AI_B=5000;
	AI_n=2;
	AI_m=3;


	for (std::list<Enemy*>::iterator enemyIt1 =this->enemyFlockingAIList.begin(); enemyIt1 !=this->enemyFlockingAIList.end();enemyIt1++)
	{		
		if ((*enemyIt1)->isTracing  &&  (*enemyIt1)->enemyState==EnemyState::ALIVE)
		{
			if (INSTANCE(PlayerManager)->player->isAlive)
			{
				Vector3 dir1=Vector3(0,0,0);
				dir1=(*enemyIt1)->node->convertWorldToLocalPosition(INSTANCE(PlayerManager)->player->node->getPosition());
				if (dir1.length()<90)
				{
					AI_U=AI_B/(pow(dir1.length(),AI_n));
					(*enemyIt1)->ax=(*enemyIt1)->ax+dir1.x*AI_U*2;
					(*enemyIt1)->ay=(*enemyIt1)->ay+dir1.z*AI_U*2;
				}
			}
			
		}

		for (std::list<Enemy*>::iterator enemyIt2 =this->enemyList.begin(); enemyIt2 !=this->enemyList.end();enemyIt2++)
		{
			if ( ((*enemyIt2)!=(*enemyIt1)) &&  (*enemyIt1)->enemyState==EnemyState::ALIVE && (*enemyIt2)->enemyState==EnemyState::ALIVE)
			{

				Vector3 dir=Vector3(0,0,0);
				dir=(*enemyIt1)->node->convertWorldToLocalPosition((*enemyIt2)->node->getPosition());


				if (dir.length()<30)
				{
					switch ((*enemyIt2)->enemyType)
					{
					case EnemyType::CANNON:
						AI_U=(-AI_A)/(pow(dir.length(),AI_n));
						(*enemyIt1)->ax=(*enemyIt1)->ax+dir.x*AI_U;
						(*enemyIt1)->ay=(*enemyIt1)->ay+dir.z*AI_U;
						break;
					case EnemyType::PRYAMID:

						AI_U=(-AI_A)/(pow(dir.length(),AI_n))+AI_B/(pow(dir.length(),AI_m));

						(*enemyIt1)->ax=(*enemyIt1)->ax+dir.x*AI_U;
						(*enemyIt1)->ay=(*enemyIt1)->ay+dir.z*AI_U;

						break;
					default:
						break;
					}

				}

			}
		}

	}

	//加速度单位化
	for (std::list<Enemy*>::iterator enemyIt0 =this->enemyFlockingAIList.begin(); enemyIt0 !=this->enemyFlockingAIList.end();)
	{	
		Vector3 v1=Vector3(0,0,0);
		v1.x=(*enemyIt0)->ax;
		v1.y=(*enemyIt0)->ay;
		v1.normalise();

		(*enemyIt0)->ax=v1.x;
		(*enemyIt0)->ay=v1.y;

		if (!(*enemyIt0)->isAlive)
		{
			enemyIt0=enemyFlockingAIList.erase(enemyIt0);
		}
		else
		{
			enemyIt0++;
		}
	}
}

void EnemyManager::GenerateEnemy(int enemyType,int count,Degree distanceDegree)
{
	SceneNode *node=INSTANCE(PlayerManager)->player->node;

	Degree degree=Degree(360/count);

	Vector3 dir=Vector3(0,-1,0);
	Real x,y;
	x=0;
	y=-1;

	for (int i=0;i<count;i++)
	{
		dir.x=x*cos(degree.valueRadians()*i)-y*sin(degree.valueRadians()*i);
		dir.y=x*sin(degree.valueRadians()*i)+y*cos(degree.valueRadians()*i);

		Enemy* enemy=&AddEnemy(enemyType,Vector3(0,0,0));

		enemy->rotateAxis=node->convertLocalToWorldPosition(dir).crossProduct(node->getPosition()).normalisedCopy();


		enemy->node->rotate(enemy->rotateAxis,distanceDegree,Node::TS_LOCAL);
		enemy->node->translate(node->getPosition()*enemy->spawnTime,Node::TS_LOCAL);		

		enemy->node->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);

	}
}

Enemy& EnemyManager::AddEnemy(int enemyType,Vector3 pos)
{
	Enemy *enemy;
	switch (enemyType)
	{
	case EnemyType::CANNON:
		enemy=new EnemyCannon();

		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_VITTUMAINEN_CANNON,true);
		break;
	case EnemyType::PRYAMID:
		enemy=new EnemyPyramid();
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_ENEMY_FOLLOWER_SPAWNED,true);
		//加入FlockingAI
		enemyFlockingAIList.push_back(enemy);
		break;
	case EnemyType::BOSS01:
		enemy=new EnemyBoss01();
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_VITTUMAINEN_CANNON,true);
		break;
	}

	enemy->isAlive=true;
	enemy->node->setPosition(pos);
	enemy->node->setVisible(true);
	enemy->movableObject->setVisible(false);
	enemy->enemyState=EnemyState::SPAWN;
	enemyList.push_back(enemy);
	return *enemy;


}

void EnemyManager::Reset()
{
	for (std::list<Enemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		delete *it;
		it=enemyList.erase(it);
		
	}
	enemyFlockingAIList.clear();
}




