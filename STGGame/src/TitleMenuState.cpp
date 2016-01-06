//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#include "TitleMenuState.h"
#include "GameStateManager.h"
#include "CameraManager.h"

void TitleMenuState::SetupContent()
{
	MenuTargetPos=Vector3(0,0,1200);
	menuNode=sceneMgr->getRootSceneNode()->createChildSceneNode(MenuTargetPos);

	menuNode->lookAt(Vector3(0,0,0),Node::TS_WORLD);

	titleText=new SpaceText();
	titleText->msg = new MovableText("TitleText", "Super StarDust For PC","StarWars",9.0f);
	titleText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	titleText->node=menuNode->createChildSceneNode(Vector3(0,0,0));
	titleText->node->attachObject(titleText->msg);

	nameText=new SpaceText();
	nameText->msg = new MovableText("NameText", "by yibojiang","StarWars",3.0f);
	nameText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	nameText->node=menuNode->createChildSceneNode(Vector3(0,-10,0));
	nameText->node->attachObject(nameText->msg);
	
	menuText=new SpaceText();
	menuText->msg = new MovableText("MenuText", "Press Enter to Start","StarWars",4.0f);
	menuText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	menuText->node=menuNode->createChildSceneNode(Vector3(0,-50,0));
	menuText->node->attachObject(menuText->msg);
	
	flashToogle=1;
	

}

void TitleMenuState::AddTime( Real deltaTime )
{
	if (flashToogle<0)
	{
		menuText->node->flipVisibility();
		flashToogle=1;
	}
	else
	{
		flashToogle=flashToogle-deltaTime;
	}
	
	
	menuNode->translate((MenuTargetPos-menuNode->getPosition())*deltaTime *5.0f);


	//titleText->msg->setCaption(Ogre::StringConverter::toString(INSTANCE(CameraManager)->cameraNode->getPosition().z) );
}

void TitleMenuState::InjectKeyDown( const OIS::KeyEvent& evt )
{
	switch(evt.key)
	{
	case OIS::KC_RETURN:
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENUSTART,true);
		INSTANCE(GameStateManager)->menuState=MenuState::MODE_MENU_STATE;
		Removed();
		break;
	default:
		break;
	}
}

void TitleMenuState::InjectKeyUp( const OIS::KeyEvent& evt )
{

}

void TitleMenuState::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	switch(button)
	{
	case 0:
	case 7://start
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENUSTART,true);
		INSTANCE(GameStateManager)->menuState=MenuState::MODE_MENU_STATE;
		Removed();
		break;
	}
}

void TitleMenuState::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{

}

void TitleMenuState::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{

}


TitleMenuState::TitleMenuState()
{

}

TitleMenuState::~TitleMenuState()
{
	delete titleText;
	delete menuText;
	delete nameText;
	CommonTool::DestroyAllAttachedMovableObjects(menuNode);
	menuNode->removeAndDestroyAllChildren();
	sceneMgr->destroySceneNode(menuNode);
}

void TitleMenuState::Removed()
{
	MenuTargetPos=Vector3(0,0,1200);
}

