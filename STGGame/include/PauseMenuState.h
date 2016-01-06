#pragma once
#include "MenuState.h"
class PauseMenuState:public MenuState
{
private:
	enum PauseMenuId{
		RESUME,
		OPTION,
		EXIT
	};
	void SetupContent();

	int menuCount;
	int menuIndex;
	SpaceText *menuArray;
public:
	void AddTime(Real deltaTime);
	void InjectKeyDown(const OIS::KeyEvent& evt);
	void InjectKeyUp(const OIS::KeyEvent& evt);
	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );
	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );
	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );
	void Show();
	void Removed();
	PauseMenuState();
	~PauseMenuState();

};

