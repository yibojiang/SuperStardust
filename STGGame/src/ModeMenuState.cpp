#include "ModeMenuState.h"
#include "GameStateManager.h"
#include "CameraManager.h"

void ModeMenuState::SetupContent()
{
	MenuTargetPos=Vector3(1000,0,1000);
	menuNode=sceneMgr->getRootSceneNode()->createChildSceneNode(MenuTargetPos);

	menuIndex=0;
	menuCount=6;
	menuArray=new SpaceText[menuCount]();

	menuArray[0].msg = new MovableText("TutorialModeText", "Tutorial Mode","StarWars",5.0f);
	menuArray[0].tag=GameMode::TUTORIAL_MODE;
	menuArray[1].msg = new MovableText("EndLessModeText", "Endless Mode","StarWars",5.0f);
	menuArray[1].tag=GameMode::ENDLESS_MODE;
	menuArray[2].msg = new MovableText("StoryModeText", "Story Mode","StarWars",5.0f);
	menuArray[2].tag=GameMode::STORY_MODE;
	menuArray[3].msg = new MovableText("CrossoutModeText", "Crossout Mode","StarWars",5.0f);
	menuArray[3].tag=GameMode::CROSSOUT_MODE;
	menuArray[4].msg = new MovableText("BossRushModeText", "BossRush Mode","StarWars",5.0f);
	menuArray[4].tag=GameMode::BOSSRUSH_MODE;
	menuArray[5].msg = new MovableText("RankText", "Rank","StarWars",5.0f);
	menuArray[5].tag=GameMode::RANK;


	for (int i=0;i<menuCount;i++)
	{
		menuArray[i].msg->setTextAlignment(MovableText::H_LEFT, MovableText::V_ABOVE);
		menuArray[i].node=menuNode->createChildSceneNode(Vector3(-10,menuCount/2*10-i*10 ,0));
		menuArray[i].node->attachObject(menuArray[i].msg);
	}
}

void ModeMenuState::AddTime( Real deltaTime )
{
	menuNode->translate((MenuTargetPos-menuNode->getPosition())*deltaTime *5.0f);
	for (int i=0;i<menuCount;i++)
	{
		menuArray[i].msg->setColor(ColourValue::White);
		menuArray[i].msg->setCharacterHeight(5.0f);
		
	}
	
	menuArray[menuIndex].msg->setCharacterHeight(6.5f);

}

void ModeMenuState::InjectKeyDown( const OIS::KeyEvent& evt )
{
	switch(evt.key)
	{
	case OIS::KC_W:
	case OIS::KC_UP:
		if (menuIndex>0)
		{
			menuIndex--;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_MOVE,true);
		}

		break;
	case OIS::KC_S:
	case OIS::KC_DOWN:
		if (menuIndex<menuCount-1)
		{
			menuIndex++;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_MOVE,true);
		}
		break;
	case OIS::KC_RETURN:
		if (menuArray[menuIndex].tag==GameMode::BOSSRUSH_MODE)
		{
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_INVALID_SELECTION_OR_ACTI,true);
		}
		else if (menuArray[menuIndex].tag==GameMode::RANK)
		{
			Removed();
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_NEW_LINE_SHOWN,true);
			INSTANCE(GameStateManager)->menuState=MenuState::RANK_MENU_STATE;
		}
		else
		{
			Removed();//IMPORTANT: remove must before enter game.
			INSTANCE(AudioManager)->bgmMgr->stopAudio(AudioName::BGM_ORCHESTRAL_MENU);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENUSTART,true);
			INSTANCE(GameStateManager)->ChangeGameState(GameState::GAME_PLAY_STATE,MenuState::PLAY_MENU_STATE,menuArray[menuIndex].tag);
		}

		break;
	case OIS::KC_ESCAPE:
		INSTANCE(GameStateManager)->menuState=MenuState::TITLE_MENU_STATE;
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,false);
		Removed();
	default:
		break;
	}
}

void ModeMenuState::InjectKeyUp( const OIS::KeyEvent& evt )
{

}

void ModeMenuState::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	
	switch(button)
	{
	case 0:
		if (menuArray[menuIndex].tag==GameMode::BOSSRUSH_MODE)
		{
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_INVALID_SELECTION_OR_ACTI,true);
			
		}
		else if (menuArray[menuIndex].tag==GameMode::RANK)
		{
			Removed();
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_NEW_LINE_SHOWN,true);
			INSTANCE(GameStateManager)->menuState=MenuState::RANK_MENU_STATE;
			
		}
		else
		{
			Removed();	
			INSTANCE(AudioManager)->bgmMgr->stopAudio(AudioName::BGM_ORCHESTRAL_MENU);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENUSTART,true);
			INSTANCE(GameStateManager)->ChangeGameState(GameState::GAME_PLAY_STATE,MenuState::PLAY_MENU_STATE, menuArray[menuIndex].tag);
			
		}

		break;
	case 1:
		INSTANCE(GameStateManager)->menuState=MenuState::TITLE_MENU_STATE;
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,false);
		Removed();
	default:
		break;
	}
}

void ModeMenuState::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{

}

void ModeMenuState::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{
	Real y=arg.state.mAxes[0].abs*1.0/32767;
	if (Ogre::Math::Abs(yAxis)<0.5 && Ogre::Math::Abs(y)>0.5)
	{
		if (y<-0.5)
		{
			if (menuIndex>0)
			{
				menuIndex--;
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_MOVE,true);
			}
		}
		else if (y>0.5)
		{
			if (menuIndex<menuCount-1)
			{
				menuIndex++;
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_MOVE,true);
			}
		}
	}
	yAxis=y;
}

ModeMenuState::ModeMenuState()
{

}

ModeMenuState::~ModeMenuState()
{
	delete[] menuArray;
	CommonTool::DestroyAllAttachedMovableObjects(menuNode);
	menuNode->removeAndDestroyAllChildren();
	sceneMgr->destroySceneNode(menuNode);
}

void ModeMenuState::Removed()
{
	MenuTargetPos=Vector3(1000,0,1000);
}


