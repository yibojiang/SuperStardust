#pragma once
#include "BulletConfig.h"
class GreenBulletConfig:public BulletConfig
{
public:


;	GreenBulletConfig(int count)
	{
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		bulletCount=count;
		bulletArray=new Bullet[count]();
		SetupContent();
		turnRate=0.5;
		shotSound=AudioName::SOUND_WEAPON_PLASMA1_SHOT;
	}

	void SetupContent()
	{
		SceneNode *node;
		NameValuePairList params;
		params["numberOfChains"] = "1";
		params["maxElements"] = "20";
		for (int i=0;i<bulletCount;i++)
		{
			RibbonTrail* trail= (RibbonTrail*)sceneMgr->createMovableObject("RibbonTrail", &params);
			sceneMgr->getRootSceneNode()->attachObject(trail);
			trail->setMaterialName("STGGame/LightRibbonTrail");
			trail->setTrailLength(2);

			trail->setInitialColour(0,0.8, 0.8,0.8, 1);
			trail->setColourChange(0, 1.0, 1.0, 1.0, 1);
			trail->setInitialWidth(0,2);
		
			BillboardSet* bbs;
			bbs = sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(0,1,0));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);

			node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			trail->addNode(node);

			node->attachObject(bbs);

			Entity *ent = sceneMgr->createEntity("bullet_boundingbox.mesh");
			node->attachObject(ent);

			bulletArray[i].node=node;
			bulletArray[i].movableObject=ent;	
			bulletArray[i].trail=trail;

			node->setVisible(false);
		}
	}

	~GreenBulletConfig(void)
	{

	}

	/**
		* @override
		*/
	void Upgrade(int level)
	{
		curLevel=level;
		switch (level)
		{
		case 1:
			rangeDegree=5;
			col=2;
			fireRate=80;
			fireToggle=15;
			damage=300;
			lifeTime=56000/fireRate;
			break;
		case 2:
			rangeDegree=10;
			col=3;
			fireRate=90;
			fireToggle=12;
			damage=500;
			lifeTime=56000/fireRate;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
			break;
		case 3:
			rangeDegree=15;
			col=4;
			fireRate=90;
			fireToggle=15;
			damage=500;
			lifeTime=56000/fireRate;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
			break;
		case 4:
			rangeDegree=75;
			col=5;
			fireRate=90;
			fireToggle=12;
			damage=500;
			lifeTime=56000/fireRate;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
			break;
		case 5:
			rangeDegree=75;
			col=6;
			fireRate=100;
			fireToggle=10;
			damage=1000;
			lifeTime=56000/fireRate;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_MAXMIZED,true);
			break;
		default:
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_OVERDRIVE,true);
			curLevel=6;
			break;
		}
	}

};