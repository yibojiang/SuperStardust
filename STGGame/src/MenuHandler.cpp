#include "MenuHandler.h"

void MenuHnadler::Init(SceneManager& sMgr)
{
	sceneMgr=&sMgr;
	mainMenuManager->Init(*sceneMgr);
	pauseMenuManager->Init(*sceneMgr);
	curMenuManager=mainMenuManager;
}

MenuHnadler::MenuHnadler()
{
	mainMenuManager=new MainMenuManager();
	pauseMenuManager=new PauseMenuManager();
	
}

void MenuHnadler::AddTime(Real deltaTime)
{
	curMenuManager->AddTime(deltaTime);
}

void MenuHnadler::EnterMainMenu()
{
	curMenuManager=mainMenuManager;

}
void MenuHnadler::EnterPauseMenu()
{
	curMenuManager=pauseMenuManager;

}
MenuHnadler::~MenuHnadler()
{

}