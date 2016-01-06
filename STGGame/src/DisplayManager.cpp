#include "DisplayManager.h"
#include "ScoreManager.h"
#include "PlayerManager.h"
#include "CameraManager.h"
#include "GameStateManager.h"

void DisplayManager::SetupContent()
{
	debugText=new SpaceText();
	debugText->msg = new MovableText("Debug123", "  ","StarWars",2.0f);
	debugText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	debugText->node=sceneMgr->getRootSceneNode()->createChildSceneNode();
	debugText->node->attachObject(debugText->msg);
	debugText->node->setPosition(0,0,80);

	scoreText=new SpaceText();
	scoreText->msg = new MovableText("scoreText", " ","StarWars",3.0f);
	scoreText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	scoreText->node=INSTANCE(CameraManager)->cameraNode->createChildSceneNode();
	scoreText->node->attachObject(scoreText->msg);
	scoreText->node->setPosition(70,50,-50);

	lifetText=new SpaceText();
	lifetText->msg = new MovableText("lifetText", " ","StarWars",2.5f);
	lifetText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	lifetText->node=INSTANCE(CameraManager)->cameraNode->createChildSceneNode();
	lifetText->node->attachObject(lifetText->msg);
	lifetText->node->setPosition(-70,50,-50);

	bombText=new SpaceText();
	bombText->msg = new MovableText("bombText", " ","StarWars",2.5f);
	bombText->msg->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); 
	bombText->node=INSTANCE(CameraManager)->cameraNode->createChildSceneNode();
	bombText->node->attachObject(bombText->msg);
	bombText->node->setPosition(-70,40,-50);

}

String DisplayManager::ConvertToString(Real i)
{
	std::ostringstream out;
	out<<i;
	return out.str();
}


//äÖÈ¾¶ÓÁÐ
void DisplayManager::AddTime(Real deltaTime)
{

	lifetText->msg->setCaption("Life: "+ConvertToString(INSTANCE(PlayerManager)->lifeNum));
	bombText->msg->setCaption("Bomb: "+ConvertToString(INSTANCE(PlayerManager)->bombNum));
	scoreText->msg->setCaption("Score: "+ConvertToString(INSTANCE(ScoreManager)->displayScore));
	lifetText->node->setVisible(true);
	bombText->node->setVisible(true);
	scoreText->node->setVisible(true);

}


DisplayManager::DisplayManager(void)
{

}
DisplayManager::~DisplayManager(void)
{

	
}

void DisplayManager::Reset()
{
	delete debugText;
	delete scoreText;
	delete lifetText;
	delete bombText;
}

