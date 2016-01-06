#pragma once

#include "SpaceEntity.h"

class CameraManager
{
private:
	SceneManager* sceneMgr;

public:
	//µ¥¼þ
	SINGLETON(CameraManager);

	Camera *camera;
	SceneNode *cameraNode;
	SceneNode *cameraGoal;

	bool isEnabled;



	void Init(Camera* cam)
	{
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		camera=cam;
		cameraNode=sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0,0,0));
		cameraNode->attachObject(camera);
		isEnabled=false;
	}

	void AddTime(Real deltaTime)
	{
		if (isEnabled)
		{
			//Check whether the deltaTime has met problems.
			//deltaTime=Math::Clamp(deltaTime,0,0.04);
			if (deltaTime>0.04)
			{
				deltaTime=0.04;
			}
			Vector3 goalOffset = (cameraGoal->_getDerivedPosition() - cameraNode->_getDerivedPosition() )  * deltaTime *5.0f;

			cameraNode->translate(goalOffset);
			cameraNode->setOrientation(cameraGoal->_getDerivedOrientation());
			cameraNode->lookAt(Vector3(0,0,0),Node::TS_WORLD);

		}
		
	}

	void Reset()
	{
		isEnabled=false;

	}
	void SetCameraGoal(SceneNode* goal)
	{
		cameraNode->resetOrientation();
		cameraGoal=goal;
		isEnabled=true;
		
	}
	void Disable()
	{
		isEnabled=false;
	}
	
	CameraManager()
	{

	}
	~CameraManager()
	{

	}
};

