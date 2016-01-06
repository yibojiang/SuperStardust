#pragma once
#include "SpaceEntity.h"


class Player:public SpaceEntity
{
public:
	int HP;
	SceneNode *shipYawNode;
	RibbonTrail* trail;
	Player(void)
	{
		isAlive=true;

		rotateAxis=Vector3::ZERO;
	}
	~Player(void)
	{
		CommonTool::DestroyAllAttachedMovableObjects(node);
		node->removeAndDestroyAllChildren();
		node->getParentSceneNode()->removeAndDestroyChild(node->getName());
		SceneManager *sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		sceneMgr->destroyRibbonTrail(trail);
	
	}
	
};