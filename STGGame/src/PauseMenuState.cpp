#include "PauseMenuState.h"
#include "GameStateManager.h"
#include "CameraManager.h"
void PauseMenuState::SetupContent()
{
	MenuTargetPos=Vector3(200,0,-50);
	menuNode=INSTANCE(CameraManager)->cameraNode->createChildSceneNode(MenuTargetPos);
	menuIndex=0;
	menuCount=3;
	menuArray=new SpaceText[menuCount]();

	menuArray[0].msg = new MovableText("ResumeText", "Resume","StarWars",5.0f);
	menuArray[0].tag=PauseMenuState::RESUME;
	menuArray[1].msg = new MovableText("OptionText", "Option","StarWars",5.0f);
	menuArray[1].tag=PauseMenuState::OPTION;
	menuArray[2].msg = new MovableText("ExitText", "Exit","StarWars",5.0f);
	menuArray[2].tag=PauseMenuState::EXIT;


	for (int i=0;i<menuCount;i++)
	{
		menuArray[i].msg->setTextAlignment(MovableText::H_LEFT, MovableText::V_ABOVE);
		menuArray[i].node=menuNode->createChildSceneNode(Vector3(-10,menuCount/2*10-i*10 ,0));
		menuArray[i].node->attachObject(menuArray[i].msg);
	}
}

void PauseMenuState::AddTime( Real deltaTime )
{
	menuNode->translate((MenuTargetPos-menuNode->getPosition())*deltaTime *5.0f);
	for (int i=0;i<menuCount;i++)
	{
		menuArray[i].msg->setColor(ColourValue::White);
		menuArray[i].msg->setCharacterHeight(5.0f);

	}

	menuArray[menuIndex].msg->setCharacterHeight(6.5f);
}

void PauseMenuState::InjectKeyDown( const OIS::KeyEvent& evt )
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
		if (menuArray[menuIndex].tag==PauseMenuState::RESUME)
		{
			INSTANCE(GameStateManager)->menuState=MenuState::PLAY_MENU_STATE;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,true);
			Removed();
			sceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
		}
		else if (menuArray[menuIndex].tag==PauseMenuState::EXIT)
		{
			INSTANCE(GameStateManager)->ChangeGameState(GameState::MAIN_MENU_STATE,MenuState::TITLE_MENU_STATE);

		}
		else
		{
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_INVALID_SELECTION_OR_ACTI,true);
		}

		break;
	case OIS::KC_ESCAPE:
		INSTANCE(GameStateManager)->menuState=MenuState::PLAY_MENU_STATE;
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,true);
		Removed();
		sceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
		break;
	default:
		break;
	}
}

void PauseMenuState::InjectKeyUp( const OIS::KeyEvent& evt )
{

}

void PauseMenuState::Show()
{
	MenuTargetPos=Vector3(0,0,-50);

}

void PauseMenuState::Removed()
{
	MenuTargetPos=Vector3(200,0,-50);

}

PauseMenuState::PauseMenuState()
{

}

PauseMenuState::~PauseMenuState()
{
	delete[] menuArray;
	CommonTool::DestroyAllAttachedMovableObjects(menuNode);
	menuNode->removeAndDestroyAllChildren();
	sceneMgr->destroySceneNode(menuNode);
}

void PauseMenuState::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	switch(button)
	{
	case 0:
		if (menuArray[menuIndex].tag==PauseMenuState::RESUME)
		{
			INSTANCE(GameStateManager)->menuState=MenuState::PLAY_MENU_STATE;
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,true);
			Removed();
			sceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
		}
		else if (menuArray[menuIndex].tag==PauseMenuState::EXIT)
		{
			INSTANCE(GameStateManager)->ChangeGameState(GameState::MAIN_MENU_STATE,MenuState::TITLE_MENU_STATE);

		}
		else
		{
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_INVALID_SELECTION_OR_ACTI,true);
		}

		break;
	case 1:
		INSTANCE(GameStateManager)->menuState=MenuState::PLAY_MENU_STATE;
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,true);
		Removed();
		sceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
		break;
	default:
		break;
	}
}

void PauseMenuState::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{

}

void PauseMenuState::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
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

