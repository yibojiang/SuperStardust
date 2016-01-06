#include "MenuManager.h"


void MenuManager::Init(SceneManager& sMgr)
{
	sceneMgr=&sMgr;
}

//‰÷»æ∂”¡–
void MenuManager::AddTime(Real deltaTime)
{

}


MenuManager::MenuManager(void)
{

}
MenuManager::~MenuManager(void)
{

}



void MenuManager::InjectKeyDown(const OIS::KeyEvent& evt)
{
	switch (evt.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		break;
	case OIS::KC_DOWN:
	case OIS::KC_S:
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:

		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:

		break;


	default:
		break;
	}


}
void MenuManager::InjectKeyUp(const OIS::KeyEvent& evt)
{
	switch (evt.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:

		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:

		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:

		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:

		break;

	default:
		break;
	}
}

