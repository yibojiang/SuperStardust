#pragma once
#include "MenuState.h"
#include "LevelManager.h"
class PlayMenuState:public MenuState
{
private:
	void SetupContent();
public:
	LevelManager *levelManager;
	void AddTime(Real deltaTime);
	void InjectKeyDown(const OIS::KeyEvent& evt);
	void InjectKeyUp(const OIS::KeyEvent& evt);
	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );
	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );
	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );
	PlayMenuState();
	~PlayMenuState();

};
