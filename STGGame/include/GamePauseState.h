#pragma once

#include "GameState.h"

class GamePauseState :public GameState
{
private:

	void SetupContent();
public:

	void AddTime(Real deltaTime);

	void InjectKeyDown(const OIS::KeyEvent& evt);

	void InjectKeyUp(const OIS::KeyEvent& evt);
	GamePauseState();
	~GamePauseState();

};