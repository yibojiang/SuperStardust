//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#include "GameStateManager.h"
#include "PlayerManager.h"
void GameStateManager::Init()
{
	currentGameState=NULL;
	sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
	ChangeGameState(GameState::MAIN_MENU_STATE,MenuState::TITLE_MENU_STATE);
}

void GameStateManager::AddTime(Real deltaTime)
{
	
	currentGameState->AddTime(deltaTime);
}


void GameStateManager::InjectKeyDown( const OIS::KeyEvent& evt )
{
	currentGameState->InjectKeyDown(evt);
}

void GameStateManager::InjectKeyUp( const OIS::KeyEvent& evt )
{
	currentGameState->InjectKeyUp(evt);
}

void GameStateManager::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	currentGameState->InjectButtonPressed(arg,button);
}

void GameStateManager::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{
	currentGameState->InjectButtonReleased(arg,button);
}

void GameStateManager::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{
	currentGameState->InjectAxisMoved(arg,axis);
}

void GameStateManager::ChangeGameState( int gameState,int menuState, int gameMode )
{
	//delete prvious GameState
	if (currentGameState)
	{
		delete currentGameState;
	}

	if (gameState==GameState::MAIN_MENU_STATE)
	{
		MainMenuState *mainMenuState=new MainMenuState();
		mainMenuState->Init();
		this->menuState=menuState;
		currentGameState=mainMenuState;
	}
	else if (gameState==GameState::GAME_PLAY_STATE)
	{
		GamePlayState *gamePlayState=new GamePlayState();
		gamePlayState->Init();
		this->menuState=menuState;
		gamePlayState->GameStart(gameMode);
		currentGameState=gamePlayState;
	}
}

GameStateManager::GameStateManager(void)
{

}
GameStateManager::~GameStateManager(void)
{

}


