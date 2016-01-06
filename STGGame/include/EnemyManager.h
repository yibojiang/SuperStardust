//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "Enemy.h"
#include "ObjectPool.h"

class EnemyPyramid;
class EnemyCannon;
class PlayerManager;

class EnemyManager:public ObjectManager
{
private:

	void SetupContent(Enemy& enemy);
public:

	SINGLETON(EnemyManager);

	//遍历的敌人
	std::list<Enemy*> enemyList;
	std::list<Enemy*> enemyFlockingAIList;
	void Init();
	void GeneratePryamid(int count,Degree distanceDegree);

	void DropPryamid(Degree directionDegree,Degree distanceDegree,int count);
	void GenerateCannon(int count,Degree distanceDegree);

	void AddTime(Real deltaTime);


	void FlockingHandler();

	void GenerateEnemy(int enemyType,int count,Degree distanceDegree);
	Enemy& AddEnemy(int enemyType,Vector3 pos);

	void Reset();
	EnemyManager();
	~EnemyManager();
};

