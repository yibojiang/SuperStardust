#pragma once
#include "SpaceEntity.h"

using namespace Ogre;
class MenuState
{
protected:
	Real yAxis;
	SceneManager *sceneMgr;
	SceneNode *menuNode;
	virtual void SetupContent()
	{

	}
public:

	Vector3 MenuTargetPos;
	enum MenuStateId
	{
		TITLE_MENU_STATE,
		MODE_MENU_STATE,
		RANK_MENU_STATE,
		PAUSE_MENU_STATE,
		PLAY_MENU_STATE,
	
	};

	virtual void Init()
	{
		yAxis=0;
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		SetupContent();
	}

	virtual void AddTime(Real deltaTime)
	{
	}

	virtual void InjectKeyDown(const OIS::KeyEvent& evt)
	{

	}

	virtual void InjectKeyUp(const OIS::KeyEvent& evt)
	{

	}

	virtual void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
	{

	}

	virtual void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
	{

	}

	virtual void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
	{

	}

	virtual void Removed()
	{

	}

	virtual void Show()
	{
		MenuTargetPos=Vector3(0,0,1000);
	}

	MenuState()
	{

	}
	virtual ~MenuState()
	{

	}
};