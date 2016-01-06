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
	//����
	SINGLETON(DisplayManager);

	void SetupContent();

	//��Ⱦ����
	void AddTime(Real deltaTime);
	
	void Reset();

	DisplayManager(void);
	~DisplayManager(void);

};

