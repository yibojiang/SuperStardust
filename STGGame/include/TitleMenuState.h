//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once

#include "MenuState.h"
class TitleMenuState:public MenuState
{
private:
	void SetupContent();
	
	SpaceText *titleText;
	SpaceText *menuText;
	SpaceText *nameText;

	Real flashToogle;
public:
	
	void AddTime(Real deltaTime);
	void InjectKeyDown(const OIS::KeyEvent& evt);
	void InjectKeyUp(const OIS::KeyEvent& evt);
	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );
	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );
	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );
	void Removed();
	TitleMenuState();
	~TitleMenuState();
};