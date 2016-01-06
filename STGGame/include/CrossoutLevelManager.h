#pragma once
#include "LevelManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "ToggleManager.h"
#include "PlanetManager.h"

class CrossoutLevelManager:public LevelManager
{
private:
	void SetupContent()
	{
		INSTANCE(PlayerManager)->SetLifeNum(30);
		INSTANCE(PlayerManager)->SetBombNum(99);
		INSTANCE(PlanetManager)->SetType(PlanetType::Earth);

		INSTANCE(PlayerManager)->blueBulletConf->Upgrade(++INSTANCE(PlayerManager)->blueBulletConf->curLevel);
		INSTANCE(PlayerManager)->blueBulletConf->Upgrade(++INSTANCE(PlayerManager)->blueBulletConf->curLevel);
		INSTANCE(PlayerManager)->blueBulletConf->Upgrade(++INSTANCE(PlayerManager)->blueBulletConf->curLevel);
		INSTANCE(PlayerManager)->blueBulletConf->Upgrade(++INSTANCE(PlayerManager)->blueBulletConf->curLevel);
		INSTANCE(PlayerManager)->blueBulletConf->Upgrade(++INSTANCE(PlayerManager)->blueBulletConf->curLevel);
		INSTANCE(PlayerManager)->redBulletConf->Upgrade(++INSTANCE(PlayerManager)->redBulletConf->curLevel);
		INSTANCE(PlayerManager)->redBulletConf->Upgrade(++INSTANCE(PlayerManager)->redBulletConf->curLevel);
		INSTANCE(PlayerManager)->redBulletConf->Upgrade(++INSTANCE(PlayerManager)->redBulletConf->curLevel);
		INSTANCE(PlayerManager)->redBulletConf->Upgrade(++INSTANCE(PlayerManager)->redBulletConf->curLevel);
		INSTANCE(PlayerManager)->redBulletConf->Upgrade(++INSTANCE(PlayerManager)->redBulletConf->curLevel);
		INSTANCE(PlayerManager)->greenBulletConf->Upgrade(++INSTANCE(PlayerManager)->greenBulletConf->curLevel);
		INSTANCE(PlayerManager)->greenBulletConf->Upgrade(++INSTANCE(PlayerManager)->greenBulletConf->curLevel);
		INSTANCE(PlayerManager)->greenBulletConf->Upgrade(++INSTANCE(PlayerManager)->greenBulletConf->curLevel);
		INSTANCE(PlayerManager)->greenBulletConf->Upgrade(++INSTANCE(PlayerManager)->greenBulletConf->curLevel);
		INSTANCE(PlayerManager)->greenBulletConf->Upgrade(++INSTANCE(PlayerManager)->greenBulletConf->curLevel);
		INSTANCE(PlayerManager)->Crossout();

	}
public:
	void AddTime(Real deltaTime)
	{
		if (INSTANCE(EnemyManager)->enemyList.size()<10)
		{
			INSTANCE(EnemyManager)->GenerateCannon(10,Degree(60));
			INSTANCE(EnemyManager)->GeneratePryamid(20,Degree(150));
		}
	}
	

	void InjectKeyDown(const OIS::KeyEvent& evt)
	{
		if (INSTANCE(PlayerManager)->isControllerOn)
		{
			switch (evt.key)
			{
			case OIS::KC_W:
			case OIS::KC_S:
			case OIS::KC_A:
			case OIS::KC_D:
				break;
			case OIS::KC_LSHIFT:
				break;
			case OIS::KC_RSHIFT:
				break;
			case OIS::KC_O:
			case OIS::KC_K:
			case OIS::KC_SEMICOLON:
			case OIS::KC_L:
				break;
			case OIS::KC_SPACE:
				break;
			case OIS::KC_1:
			case OIS::KC_2:
			case OIS::KC_3:
				break;


			default:
				break;
			}
		}

	}

	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
	{
		if (INSTANCE(PlayerManager)->isControllerOn)
		{
			switch(button)
			{

			case 0://A
			case 1://B
			case 2://X

				break;
			case 3://Y

				break;
			case 4://LA

				break;
			case 5://RA

				break;
			case 6://BACK

				break;
			case 7://START


				break;
			}
		}
	}
	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
	{
	}

	CrossoutLevelManager()
	{



	}
	~CrossoutLevelManager()
	{


	}
};