//Super Stardust for pc by yibojiang is licensed under a Creative Commons ����-����ҵ��ʹ��-��ͬ��ʽ���� 3.0 Unported License.
#include <OgreSceneManager.h>
#include "CSingleton.h"
#pragma once

using namespace Ogre;

class WorldManager
{
public:
	SINGLETON(WorldManager);
	
	void Init(SceneManager *sMgr)
	{
		sceneMgr=sMgr;
	}
	WorldManager()
	{

	}
	~WorldManager()
	{

	}

	inline SceneManager* GetSceneManager()
	{
		return sceneMgr;
	}

protected:
	SceneManager *sceneMgr;
};