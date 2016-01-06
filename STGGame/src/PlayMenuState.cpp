//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#include "PlayMenuState.h"
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
#include "GameStateManager.h"
void PlayMenuState::SetupContent()
{

}

void PlayMenuState::AddTime( Real deltaTime )
{
	INSTANCE(BulletManager)->AddTime(deltaTime);
	INSTANCE(PlayerManager)->AddTime(deltaTime);
	INSTANCE(PlanetManager)->AddTime(deltaTime);
	INSTANCE(ItemManager)->AddTime(deltaTime);
	INSTANCE(ToogleManager)->AddTime(deltaTime);
	INSTANCE(CollisionManager)->AddTime(deltaTime);
	INSTANCE(EnemyManager)->AddTime(deltaTime);
	INSTANCE(ScoreManager)->AddTime(deltaTime);
	INSTANCE(DisplayManager)->AddTime(deltaTime);
	levelManager->AddTime(deltaTime);
}

void PlayMenuState::InjectKeyDown( const OIS::KeyEvent& evt )
{
	if (evt.key==OIS::KC_ESCAPE)
	{
		INSTANCE(PlayerManager)->ResetController();
		INSTANCE(GameStateManager)->menuState=MenuState::PAUSE_MENU_STATE;
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,true);
		sceneMgr->setAmbientLight(ColourValue(0.1, 0.1, 0.1));
	}
	INSTANCE(PlayerManager)->InjectKeyDown(evt);
	levelManager->InjectKeyDown(evt);
}

void PlayMenuState::InjectKeyUp( const OIS::KeyEvent& evt )
{
	INSTANCE(PlayerManager)->InjectKeyUp(evt);
	levelManager->InjectKeyUp(evt);
}

PlayMenuState::PlayMenuState()
{

}

PlayMenuState::~PlayMenuState()
{
	delete levelManager;
}

void PlayMenuState::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	if (button==7)
	{
		INSTANCE(PlayerManager)->ResetController();
		INSTANCE(GameStateManager)->menuState=MenuState::PAUSE_MENU_STATE;
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,true);
		sceneMgr->setAmbientLight(ColourValue(0.1, 0.1, 0.1));
	}
	INSTANCE(PlayerManager)->InjectButtonPressed(arg,button);
	levelManager->InjectButtonPressed(arg,button);
}

void PlayMenuState::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{
	INSTANCE(PlayerManager)->InjectButtonReleased(arg,button);
	levelManager->InjectButtonReleased(arg,button);
}

void PlayMenuState::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{
	INSTANCE(PlayerManager)->InjectAxisMoved(arg,axis);
	levelManager->InjectAxisMoved(arg,axis);
}
