#pragma once

#include "SpaceEntity.h"

class ScoreType
{
public:
	enum ScoreId{
		SCORE_CANNON=400,
		SCORE_PRYAMID=50


	};
};

class ScoreManager:public ObjectManager
{

private:
	Real increaseToggle;
public:
	double displayScore;
	long curScore;
	long bestScore;
	
	//µ¥¼þ
	SINGLETON(ScoreManager);

	void Init()
	{
		curScore=0;
		displayScore=0;
		increaseToggle=0;
		bestScore=0;
	}

	void Reset()
	{
		curScore=0;
		displayScore=0;
		increaseToggle=0;
	}
	ScoreManager()
	{
		Init();
	}
	void AddScore(int score)
	{
		curScore=curScore+score;
	}

	void AddTime(Real deltaTime)
	{
		

		if (curScore>displayScore)
		{
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SCORE_COUNT,true);
			displayScore+=(curScore-displayScore)*5*deltaTime;
		}
		else
		{
			displayScore=curScore;

		}
		displayScore=Math::Ceil(displayScore);

		/*
		increaseToggle=increaseToggle-deltaTime;
		if (increaseToggle<0)
		{

			

			/*
			if (curScore>displayScore)
			{
				if (curScore>displayScore)
				{
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SCORE_COUNT,true);
					if(curScore-displayScore>1600)
					{
						displayScore=displayScore+320;
					}
					else if(curScore-displayScore<=1600 && curScore-displayScore>800)
					{
						displayScore=displayScore+320;
					}
					else if(curScore-displayScore<=800 && curScore-displayScore>400)
					{
						displayScore=displayScore+160;
					}
					else if(curScore-displayScore<=400 && curScore-displayScore>200)
					{
						displayScore=displayScore+80;
					}
					else if(curScore-displayScore<=200 && curScore-displayScore>100)
					{
						displayScore=displayScore+40;
					}
					else if(curScore-displayScore<=100 && curScore-displayScore>50)
					{
						displayScore=displayScore+20;
					}
					else if(curScore-displayScore<=50 && curScore-displayScore>25)
					{
						displayScore=displayScore+10;
					}
					else if (curScore-displayScore<=25  && curScore-displayScore>10)
					{
						displayScore=displayScore+5;
					}
					else if	(curScore-displayScore<=10 )
					{
						displayScore=displayScore+1;

					}
				}
			}
			
			increaseToggle=deltaTime*2;

		}
		*/
		
	}
	~ScoreManager()
	{

	}

};