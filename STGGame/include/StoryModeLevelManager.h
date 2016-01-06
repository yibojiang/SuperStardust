#pragma once
#include "LevelManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "ToggleManager.h"
#include "PlanetManager.h"
class StoryModeLevelManager:public LevelManager
{
private:
	

	void SetupContent()
	{
		INSTANCE(PlayerManager)->SetLifeNum(30);
		INSTANCE(PlayerManager)->SetBombNum(99);
		INSTANCE(PlanetManager)->SetType(PlanetType::Earth);
		//INSTANCE(EnemyManager)->GenerateEnemy(EnemyType::BOSS01,1,Degree(60));

	}
public:
	void AddTime(Real deltaTime)
	{

		if (INSTANCE(EnemyManager)->enemyList.size()<5)
		{
			INSTANCE(EnemyManager)->GenerateCannon(10,Degree(60));
		}

	}

	StoryModeLevelManager()
	{


	}

	~StoryModeLevelManager()
	{

	}


};