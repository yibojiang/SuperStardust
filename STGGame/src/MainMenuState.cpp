//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#include "MainMenuState.h"
#include "GameStateManager.h"
#include "CameraManager.h"

void MainMenuState::SetupContent()
{
	ps=sceneMgr->createParticleSystem("FlowStar","STGGame/FlowStar");
	SceneNode *node= sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0,0,990));
	node->attachObject(ps);

	bbs=sceneMgr->createBillboardSet(1);
	bbs->createBillboard(Vector3::ZERO);
	bbs->setMaterialName("STGGame/Title");
	bbs->setDefaultHeight(256);
	bbs->setDefaultWidth(256);
	node->attachObject(bbs);
	bgRotateRadian=0.0;

	titleMenuState=new TitleMenuState();
	titleMenuState->Init();

	modeMenuState=new ModeMenuState();
	modeMenuState->Init();

	rankMenuState=new RankMenuState();
	rankMenuState->Init();

	currentMenuState=titleMenuState;
	INSTANCE(GameStateManager)->menuState=MenuState::TITLE_MENU_STATE;

	cameraGoal=sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0,0,1060));
	INSTANCE(CameraManager)->SetCameraGoal(cameraGoal);
	
	INSTANCE(AudioManager)->bgmMgr->playAudio(AudioName::BGM_ORCHESTRAL_MENU,false);
}

void MainMenuState::AddTime( Real deltaTime )
{
	bgRotateRadian=bgRotateRadian+deltaTime*0.05;
	bbs->getBillboard(0)->setRotation(Radian(bgRotateRadian));
	switch (INSTANCE(GameStateManager)->menuState)
	{
	case MenuState::TITLE_MENU_STATE:
		currentMenuState=titleMenuState;
		break;
	case MenuState::MODE_MENU_STATE:
		currentMenuState=modeMenuState;
		break;
	case MenuState::RANK_MENU_STATE:
		currentMenuState=rankMenuState;
	default:
		break;
	}
	currentMenuState->Show();
	titleMenuState->AddTime(deltaTime);
	modeMenuState->AddTime(deltaTime);
	rankMenuState->AddTime(deltaTime);
}

void MainMenuState::InjectKeyDown( const OIS::KeyEvent& evt )
{
	currentMenuState->InjectKeyDown(evt);
}

void MainMenuState::InjectKeyUp( const OIS::KeyEvent& evt )
{
	currentMenuState->InjectKeyUp(evt);
}

void MainMenuState::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	currentMenuState->InjectButtonPressed(arg,button);
}

void MainMenuState::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{
	currentMenuState->InjectButtonReleased(arg,button);
}

void MainMenuState::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{
	currentMenuState->InjectAxisMoved(arg,axis);
}


MainMenuState::~MainMenuState()
{
	sceneMgr->destroySceneNode(ps->getParentSceneNode());
	sceneMgr->destroyParticleSystem(ps);
	sceneMgr->destroyBillboardSet(bbs);
	INSTANCE(CameraManager)->Reset();
	sceneMgr->destroySceneNode(cameraGoal->getName());

	delete rankMenuState;
	delete titleMenuState;
	delete modeMenuState;
}

MainMenuState::MainMenuState()
{

}

