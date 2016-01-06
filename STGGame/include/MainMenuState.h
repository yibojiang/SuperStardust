#pragma once
#include "GameState.h"
#include "TitleMenuState.h"
#include "ModeMenuState.h"
#include "RankMenuState.h"
class MainMenuState :public GameState
{
private:
	MenuState *currentMenuState;
	TitleMenuState *titleMenuState;
	ModeMenuState *modeMenuState;
	RankMenuState *rankMenuState;
	ParticleSystem *ps;
	BillboardSet *bbs;
	SceneNode *cameraGoal;
	double bgRotateRadian;
	void SetupContent();
public:
	
	void AddTime(Real deltaTime);

	void InjectKeyDown(const OIS::KeyEvent& evt);

	void InjectKeyUp(const OIS::KeyEvent& evt);

	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );

	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );

	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );
	MainMenuState();
	~MainMenuState();

};