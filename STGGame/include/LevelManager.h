#pragma once

#include "SpaceEntity.h"
#include "Toggle.h"
class Ticker  
{
public:
	Ticker()
	{

	}
	~Ticker()
	{
		tickerToggle->isAlive=false;
	}
	Toggle* tickerToggle;
	int tickerFlag;
};

class LevelManager
{
protected:

	SceneManager* sceneMgr;

	String ConvertToString(Real i)
	{
		std::ostringstream out;
		out<<i;
		return out.str();
	}

	virtual void SetupContent()
	{
		
	}

public:
	LevelManager(void)
	{

	}
	virtual ~LevelManager(void)
	{

	}


	virtual void Init()
	{
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		SetupContent();
	}

	virtual void AddTime(Real deltaTime)
	{	
	
	}
	virtual void InjectKeyDown(const OIS::KeyEvent& evt)
	{
		switch (evt.key)
		{
		case OIS::KC_W:
		case OIS::KC_S:
		case OIS::KC_A:
		case OIS::KC_D:
			break;

		case OIS::KC_LSHIFT:
			break;
		case OIS::KC_RSHIFT:
			break;
		case OIS::KC_O:
		case OIS::KC_K:
		case OIS::KC_SEMICOLON:
		case OIS::KC_L:
			break;

		case OIS::KC_SPACE:
			break;

		case OIS::KC_1:
			break;
		case OIS::KC_2:
			break;
		case OIS::KC_3:
			break;
		default:
			break;
		}
	}

	virtual void InjectKeyUp(const OIS::KeyEvent& evt)
	{
		switch (evt.key)
		{
		case OIS::KC_W:
		case OIS::KC_S:
		case OIS::KC_A:
		case OIS::KC_D:
			break;

		case OIS::KC_LSHIFT:
			break;
		case OIS::KC_RSHIFT:
			break;
		case OIS::KC_O:
		case OIS::KC_K:
		case OIS::KC_SEMICOLON:
		case OIS::KC_L:
			break;

		case OIS::KC_SPACE:
			break;

		case OIS::KC_1:
			break;
		case OIS::KC_2:
			break;
		case OIS::KC_3:
			break;


		default:
			break;
		}
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




};

