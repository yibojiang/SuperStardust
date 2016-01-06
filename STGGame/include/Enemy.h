#pragma once
#include "ScoreManager.h"
#include "ItemManager.h"

class EnemyType
{
public:
	enum TypeId
	{
		CANNON,
		PRYAMID,
		BOSS01,

	};
};

class EnemyState
{
public:
	enum EnemyStateId
	{
		SPAWN=0,
		ALIVE=1,
		DYING=2,
		DEAD=3

	};
};

class Enemy:public SpaceEntity
{
protected:
	virtual void SetupContent()
	{

	}
public:
	int enemyType;
	int healthPoint;
	int enemyState;
	bool isTracing;
	Real spawnTime;

	
	virtual void AddTime(Real deltaTime)
	{

	}

	Enemy()
	{
		isAlive=false;
		rotateAxis=Vector3::ZERO;
		spawnTime=0.0;
	}
	virtual ~Enemy()
	{
		//drop an item
		int num=Math::RangeRandom(0,1000);
		if (num<20)
		{
			int type=Math::RangeRandom(0,2.9);
			INSTANCE(ItemManager)->AddItem(type,node->getPosition());
		}
		else if (num>40 && num<80)
		{
			INSTANCE(ItemManager)->AddItem(ItemType::SCORE_1000,node->getPosition());
		}
		else if (num>20 && num<40)
		{
			INSTANCE(ItemManager)->AddItem(ItemType::BOMB,node->getPosition());
		}
		else if (num>50 && num<54)
		{
			INSTANCE(ItemManager)->AddItem(ItemType::EXTRA_SHIP,node->getPosition());
		}
	
		CommonTool::DestroyAllAttachedMovableObjects(node);
		node->removeAndDestroyAllChildren();
		node->getParentSceneNode()->removeAndDestroyChild(node->getName());

		
	}

};