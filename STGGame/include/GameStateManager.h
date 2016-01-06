//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once

#include "SpaceEntity.h"

#include "MainMenuState.h"
#include "GamePlayState.h"
#include "GamePauseState.h"

class GameMode
{
public:
	enum GameModeId
	{
		TUTORIAL_MODE,
		STORY_MODE,
		ENDLESS_MODE,
		BOSSRUSH_MODE,
		CROSSOUT_MODE,
		RANK,
	};
};

class GameStateManager
{
private:

	

public:

	GameState *currentGameState;

	int menuState;

	SceneManager *sceneMgr;

	//单件
	SINGLETON(GameStateManager);

	void Init();

	void AddTime(Real deltaTime);

	void InjectKeyDown(const OIS::KeyEvent& evt);

	void InjectKeyUp(const OIS::KeyEvent& evt);
	
	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );
	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );
	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );

	void ChangeGameState(int gameState,int menuState,int gameMode=GameMode::ENDLESS_MODE);

	GameStateManager(void);
	~GameStateManager(void);

};

