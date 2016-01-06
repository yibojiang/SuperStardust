#pragma once
#include "SpaceEntity.h"
class Planet:public SpaceEntity
{
public:
	Real radius;
	Planet(Real r)
	{
		rotateAxis=Vector3::ZERO;
		radius=r;
	}
	~Planet(void)
	{
		CommonTool::DestroyAllAttachedMovableObjects(node);
		node->removeAndDestroyAllChildren();
		node->getParentSceneNode()->removeAndDestroyChild(node->getName());
	}

};