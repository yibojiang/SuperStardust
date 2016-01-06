#pragma once

#include "GameState.h"

#include "PlayMenuState.h"
#include "PauseMenuState.h"
class GamePlayState :public GameState
{
private:
	MenuState *currentMenuState;
	PlayMenuState *playMenuState;
	PauseMenuState *pauseMenuState;
	void SetupContent();
public:
	void GameStart(int gameMode);

	void AddTime(Real deltaTime);

	void InjectKeyDown(const OIS::KeyEvent& evt);

	void InjectKeyUp(const OIS::KeyEvent& evt);

	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );

	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );

	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );
	GamePlayState();
	~GamePlayState();

};