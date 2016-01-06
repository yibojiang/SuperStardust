#pragma once
#include "SpaceEntity.h"
class Bullet:public SpaceEntity
{
public:
	int speed;
	int lifeTime;
	int damage;
	Degree offsetDegree;
	Vector3 firePositon;

	RibbonTrail* trail;

	Bullet(void)
	{
		isAlive=false;
		lifeTime=300;
		damage=300;

		rotateAxis=Vector3::ZERO;
		speed=150;
	}


	virtual ~Bullet(void)
	{
		CommonTool::DestroyAllAttachedMovableObjects(node);
		node->removeAndDestroyAllChildren();
		node->getParentSceneNode()->removeAndDestroyChild(node->getName());
		SceneManager *sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		sceneMgr->destroyRibbonTrail(trail);
	}
	
};