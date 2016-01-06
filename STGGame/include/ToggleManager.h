//Super Stardust for pc by yibojiang is licensed under a Creative Commons ����-����ҵ��ʹ��-��ͬ��ʽ���� 3.0 Unported License.
#pragma once
#include <list>
#include "Toggle.h"
class ToogleManager:public ObjectManager
{


public:

	//����
	SINGLETON(ToogleManager);

	std::list<Toggle*> toggleList;

	void Init()
	{

	}

	//��Ⱦ����
	void AddTime(Real deltaTime)
	{
		for (std::list<Toggle*>::iterator it = toggleList.begin(); it != toggleList.end();)
		{
			if (!(*it)->isAlive)
			{
				delete *it;
				it=toggleList.erase(it);
			}
			else if ((*it)->isActivated)
			{
				(*it)->timeTicker=(*it)->timeTicker-deltaTime;	
				if ((*it)->timeTicker<0)
				{
					(*it)->TickerStop();
				}
				it++;
				
			}
			else
			{
				it++;
			}
		}
	}

	Toggle& AddToggle(Real timeTicker)
	{
		Toggle *toggle=new Toggle();
		toggle->isAlive=true;
		toggle->isActivated=false;
		toggle->timeTicker=timeTicker;
		toggleList.push_back(toggle);
		return *toggle;
	}
	void Reset()
	{
		for (std::list<Toggle*>::iterator it = toggleList.begin(); it != toggleList.end();)
		{
			delete *it;
			it=toggleList.erase(it);
		}
		toggleList.clear();
	}

	ToogleManager(void)
	{

	}
	~ToogleManager(void)
	{

	}

};

