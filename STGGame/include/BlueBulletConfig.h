#pragma once
#include "BulletConfig.h"
	
class BlueBulletConfig:public BulletConfig
{
public:
	BlueBulletConfig(int count)
	{
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		bulletCount=count;
		bulletArray=new Bullet[count]();
		SetupContent();
		turnRate=0.25;
		shotSound=AudioName::SOUND_WEAPON_PLASMA3_SHOT;
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
			trail->setTrailLength(3);

			trail->setInitialColour(0,0.8, 0.8,0.8, 1);
			trail->setColourChange(0, 1.0, 1.0, 1.0, 1);
			trail->setInitialWidth(0,3);
		
			BillboardSet* bbs;
			bbs = sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(0,0,1));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(15);
			bbs->setDefaultWidth(15);


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

	~BlueBulletConfig(void)
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
				rangeDegree=0;
				col=1;
				fireRate=120;
				fireToggle=15;
				damage=300;
				lifeTime=56000/fireRate;
				break;
			case 2:
				rangeDegree=15;
				col=2;
				fireRate=150;
				fireToggle=12;
				damage=500;
				lifeTime=56000/fireRate;
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
				break;
			case 3:
				rangeDegree=15;
				col=3;
				fireRate=150;
				fireToggle=6;
				damage=700;
				lifeTime=56000/fireRate;
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
				break;
			case 4:
				rangeDegree=30;
				col=4;
				fireRate=200;
				fireToggle=12;
				damage=1200;
				lifeTime=56000/fireRate;
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
				break;
			case 5:
				rangeDegree=30;
				col=5;
				fireRate=250;
				fireToggle=6;
				damage=1200;
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