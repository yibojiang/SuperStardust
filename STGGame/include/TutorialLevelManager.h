//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "LevelManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "ToggleManager.h"
#include "CameraManager.h"
#include "PlanetManager.h"
class TutorialLevelManager:public LevelManager
{
protected:

	Ticker *stageTicker,*ticker1;
	SpaceText *tipText,*debugText,*statusText;

	int lastLevel;
	bool isControlTutorial;

	void SetupContent()
	{
		INSTANCE(PlayerManager)->SetLifeNum(3);
		INSTANCE(PlayerManager)->SetBombNum(99);


		INSTANCE(PlanetManager)->SetType(PlanetType::Earth);
		tipText=new SpaceText();
		debugText=new SpaceText();
		statusText=new SpaceText();

		tipText->msg = new MovableText("Tip", "Control tutorial is beginning...","StarWars",1.5f);
		tipText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 

		debugText->msg = new MovableText("Debug", "  ","StarWars",2.0f);
		debugText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 

		statusText->msg = new MovableText("Status", "  ","StarWars",2.0f);
		statusText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 

		tipText->node=INSTANCE(PlayerManager)->player->node->createChildSceneNode();
		tipText->node->attachObject(tipText->msg);
		tipText->node->setPosition(0,5,10);

		debugText->node=INSTANCE(CameraManager)->cameraNode->createChildSceneNode();
		debugText->node->attachObject(debugText->msg);
		debugText->node->setPosition(0,43,-50);

		statusText->node=INSTANCE(CameraManager)->cameraNode->createChildSceneNode();
		statusText->node->attachObject(statusText->msg);
		statusText->node->setPosition(0,-43,-50);

		ticker1=new Ticker();
		ticker1->tickerToggle=&INSTANCE(ToogleManager)->AddToggle(10.0);
		ticker1->tickerToggle->TickerStart();
		ticker1->tickerFlag=0;

		stageTicker=new Ticker();
		stageTicker->tickerToggle=&INSTANCE(ToogleManager)->AddToggle(10.0);
		stageTicker->tickerToggle->TickerStart();
		stageTicker->tickerFlag=0;

		INSTANCE(PlayerManager)->isControllerOn=false;
		lastLevel=0;
		isControlTutorial=true;

		INSTANCE(AudioManager)->bgmMgr->playAudio(AudioName::BGM_ARCADE_BOSS,false);
	}

public:

	TutorialLevelManager()
	{

	}
	~TutorialLevelManager()
	{
		delete tipText;
		delete debugText;
		delete statusText;
		delete stageTicker;
		delete ticker1;
	}


	Item& GenerateNextItem(Degree degree,Degree distanceDegree)
	{
		Item *newItem;
		SceneNode *node=INSTANCE(PlayerManager)->player->node;

		Vector3 dir=Vector3(0,-1,0);
		Real x,y;
		x=0;
		y=-1;

		dir.x=x*cos(degree.valueRadians())-y*sin(degree.valueRadians());
		dir.y=x*sin(degree.valueRadians())+y*cos(degree.valueRadians());

		newItem=&INSTANCE(ItemManager)->AddItem(ItemType::UPGREADE_GREENBULLET,Vector3(0,0,0));
		newItem->rotateAxis=node->convertLocalToWorldPosition(dir).crossProduct(node->getPosition()).normalisedCopy();
		newItem->node->rotate(newItem->rotateAxis,Degree(distanceDegree),Node::TS_LOCAL);
		newItem->node->translate(node->getPosition(),Node::TS_LOCAL);	
		return *newItem;
	}


	void ControlTutorial(Real deltaTime)
	{
		if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==0 )
		{
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag++;
			tipText->msg->setCaption("Hold W,S,A,D to move your ship.");
			statusText->msg->setCaption("   ");
			INSTANCE(PlayerManager)->isControllerOn=true;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
		}
		else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==1)
		{
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag++;
			tipText->msg->setCaption("While moving, hold LShift to move slowly...");
			statusText->msg->setCaption("   ");
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
		}
		else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==2)
		{
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag++;
			INSTANCE(PlayerManager)->speedAccToggle=0.0;
			tipText->msg->setCaption("Hold RShift to boost!");
			statusText->msg->setCaption("   ");
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
		}
		else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==3 )
		{
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag++;
			tipText->msg->setCaption("Hold K,;,O,L to shot toward different directions!");
			statusText->msg->setCaption("   ");
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
		}
		else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==4 )
		{
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag++;
			tipText->msg->setCaption("Press SPACE to release a bomb!");
			statusText->msg->setCaption("   ");
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
		}
		else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==5 )
		{
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag++;
			tipText->msg->setCaption("Press 1,2,3 to switch weapons!");
			statusText->msg->setCaption("   ");
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
		}
		else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==6 )
		{
			ticker1->tickerToggle->SetTimeTicker(8.35);
			ticker1->tickerFlag++;
			ticker1->tickerToggle->TickerStart();
			tipText->msg->setCaption("Ok, you have finished the basic control tutorial!");
			statusText->msg->setCaption("   ");
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
		}
		else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==7 )
		{
			tipText->msg->setCaption("next is the system tutorial!");

			ticker1->tickerFlag=0;

			isControlTutorial=false;

			stageTicker->tickerToggle->SetTimeTicker(8.35);
			stageTicker->tickerFlag++;
			stageTicker->tickerToggle->TickerStart();

			lastLevel=0;

			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
		}


		
	}

	void SystemTutorial(Real deltaTime)
	{


		Item *newItem;
		switch ((INSTANCE(PlayerManager)->greenBulletConf->curLevel))
		{
		case 1:
			statusText->msg->setCaption("Search For Green Item");
			break;
		case 2:
			statusText->msg->setCaption("okay, your weapon is upgraded to level 2");
			break;
		case 3:
			statusText->msg->setCaption("weapon upgraded (level 3)!");
			break;
		case 4:
			statusText->msg->setCaption("weapon upgraded (level 4)!");
			break;
		case 5:
			statusText->msg->setCaption("congralations, now your weapon has been fully upgraded!");
			break;
		default:
			statusText->msg->setCaption("max power!");
			break;
		}

		if ((INSTANCE(PlayerManager)->greenBulletConf->curLevel)>lastLevel)
		{		
			ticker1->tickerToggle->TickerStart();
			if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==0 )
			{
				newItem=&GenerateNextItem(Degree(-45),Degree(45));
				ticker1->tickerToggle->SetTimeTicker(5);	
				ticker1->tickerFlag++;
				lastLevel=(INSTANCE(PlayerManager)->greenBulletConf->curLevel);
				tipText->msg->setCaption("Search For Green Item!");
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);
			}
			else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==1  )
			{
				newItem=&GenerateNextItem(Degree(-30),Degree(30));
				ticker1->tickerToggle->SetTimeTicker(5);
				ticker1->tickerFlag++;
				lastLevel=(INSTANCE(PlayerManager)->greenBulletConf->curLevel);
				tipText->msg->setCaption("Done well, search For next Green Item!");
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);

			}
			else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==2)
			{
				newItem=&GenerateNextItem(Degree(-80),Degree(50));
				ticker1->tickerToggle->SetTimeTicker(5);
				ticker1->tickerFlag++;
				lastLevel=(INSTANCE(PlayerManager)->greenBulletConf->curLevel);
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);

			}
			else if (ticker1->tickerToggle->timeTicker<0 &&  ticker1->tickerFlag==3 )
			{
				newItem=&GenerateNextItem(Degree(-45),Degree(80));
				ticker1->tickerToggle->SetTimeTicker(5);
				ticker1->tickerFlag++;
				lastLevel=(INSTANCE(PlayerManager)->greenBulletConf->curLevel);
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);	
			}
			else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==4)
			{
				newItem=&GenerateNextItem(Degree(0),Degree(60));
				ticker1->tickerToggle->SetTimeTicker(5);
				ticker1->tickerFlag++;
				lastLevel=(INSTANCE(PlayerManager)->greenBulletConf->curLevel);
				tipText->msg->setCaption("okay, last one!");
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);	
			}
		}

		if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==5)
		{
			ticker1->tickerToggle->SetTimeTicker(5);
			ticker1->tickerFlag++;
			ticker1->tickerToggle->TickerStart();
			lastLevel=(INSTANCE(PlayerManager)->greenBulletConf->curLevel);
			tipText->msg->setCaption("okay, you have finished this tutorial!");
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3SOUND,false);	
		}
		else if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==6)
		{
			tipText->msg->setCaption("now, enemies are coming!");
			INSTANCE(AudioManager)->bgmMgr->pauseAudio(AudioName::BGM_ARCADE_BOSS);
			INSTANCE(AudioManager)->bgmMgr->playAudio(AudioName::BGM_ARCADE_PLANET_2,false);
			stageTicker->tickerToggle->SetTimeTicker(8.35);
			stageTicker->tickerToggle->TickerStart();
			stageTicker->tickerFlag++;
			ticker1->tickerFlag=0;
			
		}
	}

	void CannonStage(Real deltaTime)
	{

		if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==0 )
		{
			INSTANCE(EnemyManager)->GenerateCannon(8,Degree(45));
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag++;
		}
		if (INSTANCE(EnemyManager)->enemyList.size()<5 && ticker1->tickerFlag==1)
		{
			INSTANCE(EnemyManager)->GenerateCannon(10,Degree(60));
			ticker1->tickerFlag++;
		}
		if (INSTANCE(EnemyManager)->enemyList.size()<5 && ticker1->tickerFlag==2)
		{
			INSTANCE(EnemyManager)->GenerateCannon(5,Degree(90));
			ticker1->tickerFlag++;
		}
		if (INSTANCE(EnemyManager)->enemyList.size()<8 && ticker1->tickerFlag==3)
		{
			INSTANCE(EnemyManager)->GenerateCannon(8,Degree(90));
		}
		if (INSTANCE(ScoreManager)->curScore>15000)
		{
			tipText->msg->setCaption("warning...");
			stageTicker->tickerToggle->SetTimeTicker(8.35);
			stageTicker->tickerToggle->TickerStart();
			stageTicker->tickerFlag++;
			
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag=0;
			ticker1->tickerToggle->TickerStart();
		}

	}

	void AddTime(Real deltaTime)
	{
	
		if (stageTicker->tickerToggle->timeTicker<0 && stageTicker->tickerFlag==0)
		{
			debugText->msg->setCaption("  ");
			ControlTutorial(deltaTime);
		}
		else if (stageTicker->tickerToggle->timeTicker<0 && stageTicker->tickerFlag==1)
		{
			debugText->msg->setCaption("  ");
			SystemTutorial(deltaTime);
		}
		else if (stageTicker->tickerToggle->timeTicker<0 && stageTicker->tickerFlag==2)
		{
			
			tipText->msg->setCaption("eliminating the enemies...");
			CannonStage(deltaTime);
		}
		else if (stageTicker->tickerToggle->timeTicker<0 && stageTicker->tickerFlag==3)
		{

			tipText->msg->setCaption("warning, more enemies are coming...");
			PryamidStage(deltaTime);
		}
		debugText->msg->setCaption(ConvertToString(ticker1->tickerToggle->timeTicker));

		

	}

	void PryamidStage(Real deltaTime)
	{
		

		if (ticker1->tickerToggle->timeTicker<0 && ticker1->tickerFlag==0 )
		{
			INSTANCE(ItemManager)->GenerateItem(INSTANCE(PlayerManager)->player->node,ItemType::UPGREADE_REDBULLET,Degree(248),Degree(160));
			INSTANCE(ItemManager)->GenerateItem(INSTANCE(PlayerManager)->player->node,ItemType::UPGREADE_REDBULLET,Degree(45),Degree(80));
			INSTANCE(ItemManager)->GenerateItem(INSTANCE(PlayerManager)->player->node,ItemType::UPGREADE_REDBULLET,Degree(135),Degree(70));
			INSTANCE(ItemManager)->GenerateItem(INSTANCE(PlayerManager)->player->node,ItemType::UPGREADE_REDBULLET,Degree(225),Degree(30));
			INSTANCE(ItemManager)->GenerateItem(INSTANCE(PlayerManager)->player->node,ItemType::UPGREADE_BLUEBULLET,Degree(100),Degree(70));
			INSTANCE(ItemManager)->GenerateItem(INSTANCE(PlayerManager)->player->node,ItemType::UPGREADE_BLUEBULLET,Degree(170),Degree(20));
			INSTANCE(ItemManager)->GenerateItem(INSTANCE(PlayerManager)->player->node,ItemType::UPGREADE_BLUEBULLET,Degree(220),Degree(10));
			INSTANCE(ItemManager)->GenerateItem(INSTANCE(PlayerManager)->player->node,ItemType::UPGREADE_BLUEBULLET,Degree(335),Degree(150));
			INSTANCE(EnemyManager)->GeneratePryamid(60,Degree(150));
			//INSTANCE(EnemyManager)->GenerateCannon(10,Degree(60));
			ticker1->tickerToggle->SetTimeTicker(16.7);	
			ticker1->tickerFlag++;
		}
		if (INSTANCE(EnemyManager)->enemyList.size()<50 && ticker1->tickerFlag==1)
		{
			INSTANCE(EnemyManager)->GeneratePryamid(60,Degree(150));
			//INSTANCE(EnemyManager)->GenerateCannon(10,Degree(60));

		}
		
	}

	void InjectKeyDown(const OIS::KeyEvent& evt)
	{
		if (isControlTutorial && INSTANCE(PlayerManager)->isControllerOn)
		{
			switch (evt.key)
			{
			case OIS::KC_W:
			case OIS::KC_S:
			case OIS::KC_A:
			case OIS::KC_D:
				if (ticker1->tickerFlag==1)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("well done!");
					ticker1->tickerToggle->TickerStart();
					
				}
				break;
			case OIS::KC_LSHIFT:
				if (ticker1->tickerFlag==2)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("excellent! slow down could help you better control your ship");
					ticker1->tickerToggle->TickerStart();

				}
				break;
			case OIS::KC_RSHIFT:
				if (ticker1->tickerFlag==3)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("good job! while boosting, you wouldn't get any damage.remember coldtime after boost.");
					ticker1->tickerToggle->TickerStart();

				}
				break;
			
			case OIS::KC_O:
			case OIS::KC_K:
			case OIS::KC_SEMICOLON:
			case OIS::KC_L:
				if (ticker1->tickerFlag==4)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("perfect! try to shot towards different directions.");
					ticker1->tickerToggle->TickerStart();

				}
				break;

			case OIS::KC_SPACE:
				if (ticker1->tickerFlag==5)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("well done!");
					ticker1->tickerToggle->TickerStart();

				}
				break;

			case OIS::KC_1:
			case OIS::KC_2:
			case OIS::KC_3:
				if (ticker1->tickerFlag==6)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("okay, now you have three weapn to switch, check your button!");
					ticker1->tickerToggle->TickerStart();

				}
				break;


			default:
				break;
			}
		}
		
	}

	void InjectKeyUp(const OIS::KeyEvent& evt)
	{
		if (isControlTutorial && INSTANCE(PlayerManager)->isControllerOn)
		{
			switch (evt.key)
			{
			case OIS::KC_W:
			case OIS::KC_S:
			case OIS::KC_A:
			case OIS::KC_D:
				break;

			case OIS::KC_LSHIFT:

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
				break;
			case OIS::KC_2:
				break;
			case OIS::KC_3:
				break;


			default:
				break;
			}
		}
	}

	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
	{
		if (isControlTutorial && INSTANCE(PlayerManager)->isControllerOn)
		{
			switch(button)
			{

			case 0://A
			case 1://B
			case 2://X
				if (ticker1->tickerFlag==6)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("okay, now you have three weapn to switch, check your button!");
					ticker1->tickerToggle->TickerStart();

				}
				break;
			case 3://Y

				break;
			case 4://LA
				if (ticker1->tickerFlag==3)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("good job! while boosting, you wouldn't get any damage.remember coldtime after boost.");
					ticker1->tickerToggle->TickerStart();

				}
				break;
			case 5://RA
				if (ticker1->tickerFlag==5)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("well done!");
					ticker1->tickerToggle->TickerStart();

				}
				break;
			case 6://BACK

				break;
			case 7://START


				break;
			}
		}
	}
	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
	{

	}
	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
	{
		if (isControlTutorial && INSTANCE(PlayerManager)->isControllerOn)
		{
			if (axis==0 || axis ==1)
			{
				if (ticker1->tickerFlag==1)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("well done!");
					ticker1->tickerToggle->TickerStart();

				}

				if (ticker1->tickerFlag==2)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("excellent! slow down could help you better control your ship");
					ticker1->tickerToggle->TickerStart();

				}
			}
			else if (axis==2 || axis ==3)
			{
				if (ticker1->tickerFlag==4)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_PS3TROPHY,false);	
					statusText->msg->setCaption("perfect! try to shot towards different directions.");
					ticker1->tickerToggle->TickerStart();

				}
			}
		}

	}
	

	

};

