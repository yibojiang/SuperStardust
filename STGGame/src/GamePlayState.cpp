#include "GamePlayState.h"
#include "GameStateManager.h"
#include "CameraManager.h"
#include "BulletManager.h"
#include "PlayerManager.h"
#include "PlanetManager.h"
#include "ItemManager.h"
#include "ToggleManager.h"
#include "CollisionManager.h"
#include "TutorialLevelManager.h"
#include "EndlessLevelManager.h"
#include "StoryModeLevelManager.h"
#include "DisplayManager.h"
#include "ScoreManager.h"
#include "AudioManager.h"
#include "CrossoutLevelManager.h"

void GamePlayState::SetupContent()
{
	INSTANCE(ScoreManager)->Reset();
	INSTANCE(ItemManager)->Init();
	INSTANCE(ToogleManager)->Init();
	INSTANCE(CollisionManager)->Init();
	INSTANCE(EnemyManager)->Init();
	INSTANCE(BulletManager)->Init();
	INSTANCE(PlanetManager)->Init();
	INSTANCE(PlayerManager)->Init();
	INSTANCE(DisplayManager)->Init();
	
	playMenuState=new PlayMenuState();
	playMenuState->Init();
	pauseMenuState=new PauseMenuState();
	pauseMenuState->Init();
	
	currentMenuState=playMenuState;
	INSTANCE(GameStateManager)->menuState=MenuState::PLAY_MENU_STATE;
}


void GamePlayState::GameStart( int gameMode )
{
	
	switch (gameMode)
	{
	case GameMode::TUTORIAL_MODE:
		playMenuState->levelManager=new TutorialLevelManager();
		break;
	case GameMode::ENDLESS_MODE:
		playMenuState->levelManager=new EndlessLevelManager();
		break;
	case GameMode::STORY_MODE:
		playMenuState->levelManager=new StoryModeLevelManager();
		break;
	case GameMode::CROSSOUT_MODE:
		playMenuState->levelManager=new CrossoutLevelManager();
		break;
	default:
		break;
	}
	playMenuState->levelManager->Init();
	
	INSTANCE(CameraManager)->SetCameraGoal(INSTANCE(PlayerManager)->cameraGoal);
	
}
void GamePlayState::AddTime( Real deltaTime )
{
	switch (INSTANCE(GameStateManager)->menuState)
	{
	case MenuState::PLAY_MENU_STATE:
		if (INSTANCE(PlayerManager)->playerState==PlayerState::GAMEOVER)
		{
			if (INSTANCE(ScoreManager)->curScore>INSTANCE(ScoreManager)->bestScore)
			{
				INSTANCE(ScoreManager)->bestScore=INSTANCE(ScoreManager)->curScore;
			}
			INSTANCE(GameStateManager)->ChangeGameState(GameState::MAIN_MENU_STATE,MenuState::RANK_MENU_STATE);
			
			
			return;
		}

		currentMenuState=playMenuState;
		playMenuState->AddTime(deltaTime);
		pauseMenuState->AddTime(deltaTime);
		break;
	case MenuState::PAUSE_MENU_STATE:
		currentMenuState=pauseMenuState;
		pauseMenuState->AddTime(deltaTime);
		break;
	default:
		break;
	}
	currentMenuState->Show();

}

void GamePlayState::InjectKeyDown( const OIS::KeyEvent& evt )
{
	currentMenuState->InjectKeyDown(evt);
}

void GamePlayState::InjectKeyUp( const OIS::KeyEvent& evt )
{
	currentMenuState->InjectKeyUp(evt);
}

void GamePlayState::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	currentMenuState->InjectButtonPressed(arg,button);
}

void GamePlayState::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{
	currentMenuState->InjectButtonReleased(arg,button);
}

void GamePlayState::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{
	currentMenuState->InjectAxisMoved(arg,axis);
}

GamePlayState::GamePlayState()
{

}

GamePlayState::~GamePlayState()
{
	INSTANCE(DisplayManager)->Reset();
	delete playMenuState;
	delete pauseMenuState;
	
	//INSTANCE(ScoreManager)->Reset();
	INSTANCE(PlayerManager)->Reset();
	INSTANCE(PlanetManager)->Reset();
	INSTANCE(BulletManager)->Reset();
	INSTANCE(EnemyManager)->Reset();
	INSTANCE(CollisionManager)->Reset();
	INSTANCE(ItemManager)->Reset();
	INSTANCE(ToogleManager)->Reset();
	INSTANCE(CameraManager)->Reset();
	INSTANCE(AudioManager)->soundMgr->stopAllAudio();
	INSTANCE(AudioManager)->bgmMgr->stopAllAudio();
	
	


}




