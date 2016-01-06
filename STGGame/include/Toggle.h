//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "SpaceEntity.h"
class Toggle:public SpaceEntity
{
public:
	bool isActivated;
	Real timeTicker;

	Toggle(void)
	{
		isAlive=false;
		isActivated=false;

	}

	void SetTimeTicker(Real time)
	{
		timeTicker=time;
	}

	void TickerStop()
	{
		isActivated=false;
	}

	void TickerStart()
	{
		if (timeTicker<0)
			isActivated=false;
		else
			isActivated=true;

		
	}

	~Toggle(void)
	{

	}

};