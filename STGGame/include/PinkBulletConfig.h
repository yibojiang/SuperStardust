#pragma once
#include "BulletConfig.h"

class PinkBulletConfig:public BulletConfig
{
public:
	PinkBulletConfig()
	{
		//bulletCount=count;
		//bulletArray=new Bullet[count]();
		//SetupContent();
		turnRate=0.2;
		shotSound=AudioName::SOUND_WEAPON_PLASMA3_SHOT;
	}

	void SetupContent()
	{
		SceneManager *sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		SceneNode *node;
		NameValuePairList params;
		params["numberOfChains"] = "1";
		params["maxElements"] = "20";
		for (int i=0;i<bulletCount;i++)
		{

			RibbonTrail* trail= (RibbonTrail*)sceneMgr->createMovableObject("RibbonTrail", &params);
			sceneMgr->getRootSceneNode()->attachObject(trail);
			trail->setMaterialName("STGGame/LightRibbonTrail");
			trail->setTrailLength(1);

			trail->setInitialColour(0.8, 0.8,0.8, 1);
			trail->setColourChange(0, 1.0, 1.0, 1.0, 1);
			trail->setInitialWidth(0,2);

			BillboardSet* bbs;
			bbs = sceneMgr->createBillboardSet(1);
			bbs->createBillboard(Vector3::ZERO,ColourValue(1,0,1));
			bbs->setMaterialName("STGGame/Flare");
			bbs->setDefaultHeight(10);
			bbs->setDefaultWidth(10);


			node=sceneMgr->getRootSceneNode()->createChildSceneNode();
			trail->addNode(node);

			node->attachObject(bbs);

			node->setVisible(false);

			Entity *ent = sceneMgr->createEntity("bullet_boundingbox.mesh");
			node->attachObject(ent);


			bulletArray[i].node=node;
			bulletArray[i].movableObject=ent;
		}
	}

	~PinkBulletConfig(void)
	{
		
	}

	void Upgrade(int level)
	{
		curLevel=level;
		switch (level)
		{
			case 1:
				rangeDegree=0;
				col=1;
				fireRate=20;
				fireToggle=15;
				damage=300;
				lifeTime=56000/fireRate;
				break;
			case 2:
				rangeDegree=15;
				col=1;
				fireRate=150;
				fireToggle=1;
				damage=500;
				lifeTime=56000/fireRate;
				break;
			case 3:
				rangeDegree=15;
				col=1;
				fireRate=150;
				fireToggle=1;
				damage=700;
				lifeTime=56000/fireRate;
				break;
			case 4:
				rangeDegree=45;
				col=1;
				fireRate=150;
				fireToggle=1;
				damage=700;
				lifeTime=56000/fireRate;
				break;
			case 5:
				rangeDegree=45;
				col=4;
				fireRate=30;
				fireToggle=35;
				damage=100;
				lifeTime=56000/fireRate;
				break;
			default:
				curLevel=6;
				break;
		}
	}

};