//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "SpaceEntity.h"
#include "ItemType.h"
#include "Toggle.h"
class Item:public SpaceEntity
{

public:
	int itemType;
	Toggle *ticker;
	bool hasTicker;
	MaterialPtr materialPtr;
	ParticleSystem *ps;
	Item(void)
	{
		isAlive=false;
		hasTicker=false;
		rotateAxis=Vector3::ZERO;
		materialPtr.setNull();
		ps=NULL;
	}

	~Item(void)
	{
		if (NULL!=ps)
		{
			SceneManager *sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
			//Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(ps->getNumParticles()));
			sceneMgr->destroyParticleSystem(ps);
		}
		CommonTool::DestroyAllAttachedMovableObjects(node);
		node->removeAndDestroyAllChildren();
		node->getParentSceneNode()->removeAndDestroyChild(node->getName());

		if (!materialPtr.isNull())
		{
			MaterialManager::getSingletonPtr()->remove(materialPtr->getName());
		}

		if (hasTicker)
		{
			ticker->isAlive=false;
		}
		
		
		
	}

	

};