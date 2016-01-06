#pragma once
#include "SpaceEntity.h"


class CameraManager;

class DisplayManager:public ObjectManager
{
	
public:
	String ConvertToString(Real i);
	SpaceText *debugText;
	SpaceText *scoreText;
	SpaceText *lifetText;
	SpaceText *bombText;
	//单件
	SINGLETON(DisplayManager);

	void SetupContent();

	//渲染队列
	void AddTime(Real deltaTime);
	
	void Reset();

	DisplayManager(void);
	~DisplayManager(void);

};

