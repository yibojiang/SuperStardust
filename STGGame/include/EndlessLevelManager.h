//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "LevelManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "ToggleManager.h"
#include "PlanetManager.h"
class EndlessLevelManager:public LevelManager
{
private:

	Ticker *stageTicker,*ticker1;
	SpaceText *tipText,*debugText,*statusText;

	int lastLevel;
	bool isControlTutorial;
	int pryamidCount;
	Real pryamidDropToggle;
	void SetupContent()
	{
		INSTANCE(PlayerManager)->SetLifeNum(3);
		INSTANCE(PlayerManager)->SetBombNum(50);

		INSTANCE(PlanetManager)->SetType(PlanetType::Earth2);
		tipText=new SpaceText();
		debugText=new SpaceText();
		statusText=new SpaceText();


		tipText->msg = new MovableText("Tip", "Game is beginning...","StarWars",1.2f);
		tipText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 

		debugText->msg = new MovableText("Debug", "  ","StarWars",2.0f);
		debugText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 

		statusText->msg = new MovableText("Status", "  ","StarWars",2.0f);
		statusText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 

		tipText->node=INSTANCE(PlayerManager)->player->node->createChildSceneNode();
		tipText->node->attachObject(tipText->msg);
		tipText->node->setPosition(0,5,10);


		debugText->node=INSTANCE(PlayerManager)->player->node->createChildSceneNode();
		debugText->node->attachObject(debugText->msg);
		debugText->node->setPosition(0,43,10);

		statusText->node=INSTANCE(PlayerManager)->player->node->createChildSceneNode();
		statusText->node->attachObject(statusText->msg);
		statusText->node->setPosition(0,-43,10);

		ticker1=new Ticker();
		ticker1->tickerToggle=&INSTANCE(ToogleManager)->AddToggle(8.0);
		ticker1->tickerToggle->isActivated=true;
		ticker1->tickerFlag=0;

		stageTicker=new Ticker();
		stageTicker->tickerToggle=&INSTANCE(ToogleManager)->AddToggle(8.0);
		stageTicker->tickerToggle->isActivated=true;
		stageTicker->tickerFlag=0;

		lastLevel=0;

		INSTANCE(AudioManager)->bgmMgr->playAudio(AudioName::BGM_ARCADE_PLANET_2,false);

		pryamidCount=200;
		pryamidDropToggle=0;
	}

public:

	EndlessLevelManager()
	{

	}
	~EndlessLevelManager()
	{
		delete tipText;
		delete debugText;
		delete statusText;
		delete stageTicker;
		delete ticker1;
	}


	void CannonStage(Real deltaTime)
	{
		
		//debugText->msg->setCaption(ConvertToString(deltaTime));
		if (pryamidDropToggle<0)
		{
			//INSTANCE(EnemyManager)->DropPryamid(Degree(45),Degree(60),pryamidCount--);
			pryamidDropToggle=0.1;
		}
		else
		{
			pryamidDropToggle=pryamidDropToggle-deltaTime;
		}

		if (ticker1->tickerFlag==0 )
		{
			
			INSTANCE(EnemyManager)->GeneratePryamid(60,Degree(150));
			INSTANCE(EnemyManager)->GenerateCannon(10,Degree(60));

			ticker1->tickerFlag++;
		}


		if (INSTANCE(EnemyManager)->enemyList.size()<5 && ticker1->tickerFlag==1)
		{

			INSTANCE(EnemyManager)->GeneratePryamid(80,Degree(130));
			INSTANCE(EnemyManager)->GenerateCannon(16,Degree(90));
			INSTANCE(EnemyManager)->GenerateCannon(8,Degree(60));

			//INSTANCE(EnemyManager)->GeneratePryamid(90,Degree(130));
			//INSTANCE(EnemyManager)->GeneratePryamid(80,Degree(140));
			//INSTANCE(EnemyManager)->GeneratePryamid(60,Degree(150));
			
		}

	}

	void AddTime(Real deltaTime)
	{
		//debugText->msg->setCaption(ConvertToString(ticker1->tickerToggle->timeTicker));
		//tipText->msg->setCaption(Ogre::StringConverter::toString(INSTANCE(ItemManager)->itemList.size()));
		tipText->msg->setCaption(Ogre::StringConverter::toString(INSTANCE(EnemyManager)->enemyList.size()));
		if (stageTicker->tickerToggle->timeTicker<0 && stageTicker->tickerFlag==0)
		{
			CannonStage(deltaTime);

		}
		else if (stageTicker->tickerToggle->timeTicker<0 && stageTicker->tickerFlag==1)
		{


		}



	}

	void InjectKeyDown(const OIS::KeyEvent& evt)
	{
		
	}

	void InjectKeyUp(const OIS::KeyEvent& evt)
	{
		
		
	}


};

