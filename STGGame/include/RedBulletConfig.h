//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "BulletConfig.h"

class RedBulletConfig:public BulletConfig
{
public:
	RedBulletConfig(int count)
	{
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		bulletCount=count;
		bulletArray=new Bullet[count]();
		SetupContent();
		turnRate=0.2;
		shotSound=AudioName::SOUND_WEAPON_PLASMA2_HIT;
	}

	void SetupContent()
	{
		SceneNode *node;
		NameValuePairList params;
		params["numberOfChains"] = "1";
		params["maxElements"] = "20";
		for (int i=0;i<bulletCount;i++)
		{
			Light *traillight;
			
			RibbonTrail* trail= (RibbonTrail*)sceneMgr->createMovableObject("RibbonTrail", &params);
			sceneMgr->getRootSceneNode()->attachObject(trail);
			
			trail->setMaterialName("STGGame/LightRibbonTrail");
			trail->setTrailLength(100);

			trail->setInitialColour(0,0.8, 0.0,0.0, 1);
			trail->setColourChange(0, 1.0, 1.0, 1.0, 0.5);
			trail->setInitialWidth(0,1);
		
			BillboardSet* bbs;
			bbs = sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(1,0,0));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);

			traillight = sceneMgr->createLight();
			traillight->setDiffuseColour(trail->getInitialColour(0));

			node=sceneMgr->getRootSceneNode()->createChildSceneNode();


			trail->addNode(node);
			node->attachObject(traillight);
			node->attachObject(bbs);

			
			Entity *ent = sceneMgr->createEntity("bullet_boundingbox.mesh");
			node->attachObject(ent);


			bulletArray[i].node=node;
			bulletArray[i].movableObject=ent;	
			bulletArray[i].trail=trail;
			node->setVisible(false);
		}
	}

	~RedBulletConfig(void)
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
				fireRate=90;
				fireToggle=1;
				damage=300;
				lifeTime=56000/fireRate;
				break;
			case 2:
				rangeDegree=0;
				col=1;
				fireRate=150;
				fireToggle=1;
				damage=500;
				lifeTime=56000/fireRate;
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
				break;
			case 3:
				rangeDegree=0;
				col=1;
				fireRate=150;
				fireToggle=1;
				damage=700;
				lifeTime=56000/fireRate;
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
				break;
			case 4:
				rangeDegree=0;
				col=1;
				fireRate=150;
				fireToggle=1;
				damage=700;
				lifeTime=56000/fireRate;
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_WEAPON_UP,true);
				break;
			case 5:
				rangeDegree=0;
				col=1;
				fireRate=150;
				fireToggle=1;
				damage=700;
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