#pragma once

#include "SpaceEntity.h"

using namespace Ogre;
class GameState
{
protected:
	SceneManager *sceneMgr;

	virtual void SetupContent();
public:
	enum GameStateId
	{
		MAIN_MENU_STATE,
		GAME_PLAY_STATE,
		GAME_PAUSE_STATE,
	};
	GameState();

	virtual ~GameState();



	virtual void Init();

	virtual void AddTime(Real deltaTime);

	virtual void InjectKeyDown(const OIS::KeyEvent& evt);

	virtual void InjectKeyUp(const OIS::KeyEvent& evt);

	virtual void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );

	virtual void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );

	virtual	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );

};