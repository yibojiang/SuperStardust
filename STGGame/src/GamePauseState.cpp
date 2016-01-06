#include "GamePauseState.h"
#include "GameStateManager.h"

void GamePauseState::SetupContent()
{

}


void GamePauseState::AddTime( Real deltaTime )
{

}

void GamePauseState::InjectKeyDown( const OIS::KeyEvent& evt )
{
	if (evt.key==OIS::KC_ESCAPE)
	{
		INSTANCE(GameStateManager)->ChangeGameState(GameState::GAME_PLAY_STATE);
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,false);
	}
}

void GamePauseState::InjectKeyUp( const OIS::KeyEvent& evt )
{

}

GamePauseState::GamePauseState()
{

}

GamePauseState::~GamePauseState()
{

}
