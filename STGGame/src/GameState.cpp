#include "GameState.h"

void GameState::Init()
{
	sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
	SetupContent();
}

void GameState::AddTime( Real deltaTime )
{

}

void GameState::InjectKeyDown( const OIS::KeyEvent& evt )
{

}

void GameState::InjectKeyUp( const OIS::KeyEvent& evt )
{

}

void GameState::SetupContent()
{

}

GameState::GameState()
{

}

GameState::~GameState()
{

}

void GameState::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{

}

void GameState::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{

}

void GameState::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{

}
