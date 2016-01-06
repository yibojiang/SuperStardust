#include "RankMenuState.h"
#include "GameStateManager.h"
#include "CameraManager.h"
#include "ScoreManager.h"

void RankMenuState::SetupContent()
{
	MenuTargetPos=Vector3(1000,0,1000);
	menuNode=sceneMgr->getRootSceneNode()->createChildSceneNode(MenuTargetPos);

	menuNode->lookAt(Vector3(0,0,0),Node::TS_WORLD);

	scoreTitleText=new SpaceText();
	scoreTitleText->msg = new MovableText("ScoreTitleText", "Your Score:","StarWars",6.0f);
	scoreTitleText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	scoreTitleText->node=menuNode->createChildSceneNode(Vector3(0,15,0));
	scoreTitleText->node->attachObject(scoreTitleText->msg);

	scoreText=new SpaceText();
	scoreText->msg = new MovableText("ScoreText", StringConverter::toString(INSTANCE(ScoreManager)->curScore),"StarWars",10.0f);
	scoreText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	scoreText->node=menuNode->createChildSceneNode(Vector3(0,0,0));
	scoreText->node->attachObject(scoreText->msg);

	bestScoreTitleText=new SpaceText();
	bestScoreTitleText->msg = new MovableText("BestScoreTitleText", "Best:","StarWars",4.0f);
	bestScoreTitleText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	bestScoreTitleText->node=menuNode->createChildSceneNode(Vector3(0,-15,0));
	bestScoreTitleText->node->attachObject(bestScoreTitleText->msg);

	bestScoreText=new SpaceText();
	bestScoreText->msg = new MovableText("BestScoreText", StringConverter::toString(INSTANCE(ScoreManager)->bestScore),"StarWars",8.0f);
	bestScoreText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	bestScoreText->node=menuNode->createChildSceneNode(Vector3(0,-25,0));
	bestScoreText->node->attachObject(bestScoreText->msg);


	
}

void RankMenuState::AddTime( Real deltaTime )
{
	menuNode->translate((MenuTargetPos-menuNode->getPosition())*deltaTime *5.0f);

}

void RankMenuState::InjectKeyDown( const OIS::KeyEvent& evt )
{
	switch(evt.key)
	{
	case OIS::KC_RETURN:
	case OIS::KC_ESCAPE:
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,true);
		INSTANCE(GameStateManager)->menuState=MenuState::MODE_MENU_STATE;
		Removed();
		break;
	default:
		break;
	}
}

void RankMenuState::InjectKeyUp( const OIS::KeyEvent& evt )
{

}

void RankMenuState::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	switch(button)
	{
	case 0://A
	case 1://B
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MENU_PREVIOUS_SCREEN,true);
		INSTANCE(GameStateManager)->menuState=MenuState::MODE_MENU_STATE;
		Removed();
		break;
	}
}

void RankMenuState::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{

}

void RankMenuState::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{

}


RankMenuState::RankMenuState()
{

}

RankMenuState::~RankMenuState()
{
	delete scoreTitleText;
	delete scoreText;
	delete bestScoreTitleText;
	delete bestScoreText;
	CommonTool::DestroyAllAttachedMovableObjects(menuNode);
	menuNode->removeAndDestroyAllChildren();
	sceneMgr->destroySceneNode(menuNode);
}

void RankMenuState::Removed()
{
	MenuTargetPos=Vector3(1000,0,1000);
}

