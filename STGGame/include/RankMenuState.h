#pragma once

#include "MenuState.h"
class RankMenuState:public MenuState
{
private:
	void SetupContent();

	SpaceText *scoreTitleText;
	SpaceText *scoreText;
	SpaceText *bestScoreTitleText;
	SpaceText *bestScoreText;


public:

	void AddTime(Real deltaTime);
	void InjectKeyDown(const OIS::KeyEvent& evt);
	void InjectKeyUp(const OIS::KeyEvent& evt);
	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );
	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );
	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );
	void Removed();
	RankMenuState();
	~RankMenuState();
};