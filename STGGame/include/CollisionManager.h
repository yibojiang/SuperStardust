//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include <list>
#include "BulletManager.h"
#include "PlayerManager.h"
#include "ItemManager.h"
#include "EnemyManager.h"
#include "ScoreManager.h"
class CollisionManager:public ObjectManager
{
private:

public:

	//单件
	SINGLETON(CollisionManager);


	void Init()
	{
		sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
	}

	//渲染队列
	void AddTime(Real deltaTime)
	{


		for (std::list<Item*>::iterator itemIt =INSTANCE(ItemManager)->itemList.begin(); itemIt !=INSTANCE(ItemManager)->itemList.end();itemIt++)
		{
			Vector3 goalOffset=INSTANCE(PlayerManager)->player->node->_getDerivedPosition()-(*itemIt)->node->_getDerivedPosition();
			if (goalOffset.length()<30)
			{
				switch ((*itemIt)->itemType)
				{
				case ItemType::UPGREADE_GREENBULLET:
				case ItemType::UPGREADE_BLUEBULLET:
				case ItemType::UPGREADE_REDBULLET:
				case ItemType::SCORE_1000:
				case ItemType::BOMB:
				case ItemType::EXTRA_SHIP:
					(*itemIt)->node->translate(goalOffset*deltaTime*8.0f);
					break;
				default:
					break;
				}	
			}

			if ((*itemIt)->movableObject-> getWorldBoundingBox(true).intersects(INSTANCE(PlayerManager)->player->movableObject->getWorldBoundingBox(true)) && INSTANCE(PlayerManager)->player->isAlive )
			{
				switch ((*itemIt)->itemType)
				{
				case ItemType::UPGREADE_GREENBULLET:
					INSTANCE(PlayerManager)->greenBulletConf->Upgrade(++INSTANCE(PlayerManager)->greenBulletConf->curLevel);
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_TOKEN_COLLECTED,true);
					(*itemIt)->isAlive=false;
					break;
				case ItemType::UPGREADE_BLUEBULLET:
					INSTANCE(PlayerManager)->blueBulletConf->Upgrade(++INSTANCE(PlayerManager)->blueBulletConf->curLevel);
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_TOKEN_COLLECTED,true);
					(*itemIt)->isAlive=false;
					break;
				case ItemType::UPGREADE_REDBULLET:
					INSTANCE(PlayerManager)->redBulletConf->Upgrade(++INSTANCE(PlayerManager)->redBulletConf->curLevel);
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_TOKEN_COLLECTED,true);
					(*itemIt)->isAlive=false;
					break;
				case ItemType::SCORE_1000:
					INSTANCE(ScoreManager)->AddScore(1000);
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_TOKEN_COLLECTED,true);
					(*itemIt)->isAlive=false;
					break;
				case ItemType::BOMB:
					INSTANCE(PlayerManager)->GetBomb();
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_TOKEN_COLLECTED,true);
					(*itemIt)->isAlive=false;
					break;
				case ItemType::EXTRA_SHIP:
					INSTANCE(PlayerManager)->GetLife();
					INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_TOKEN_COLLECTED,true);
					(*itemIt)->isAlive=false;
					break;
				default:
					break;
				}
				
				
			}
		}

		for (std::list<Bullet*>::iterator bulletIt =INSTANCE(BulletManager)->enemyBulletList.begin(); bulletIt !=INSTANCE(BulletManager)->enemyBulletList.end();bulletIt++)
		{
			if (INSTANCE(PlayerManager)->player->movableObject-> getWorldBoundingBox(true).intersects((*bulletIt)->movableObject->getWorldBoundingBox(true)) &&  INSTANCE(PlayerManager)->player->isAlive && (*bulletIt)->isAlive)
			{
				if (!INSTANCE(PlayerManager)->isGod)
				{
					DieExplosion();
					(*bulletIt)->isAlive=false;
					INSTANCE(PlayerManager)->player->isAlive=false;
					
				}
				else
				{
					(*bulletIt)->isAlive=false;
				}	
			}
		}

		for (std::list<Enemy*>::iterator enemyIt =INSTANCE(EnemyManager)->enemyList.begin(); enemyIt !=INSTANCE(EnemyManager)->enemyList.end();enemyIt++)
		{
			if ((*enemyIt)->movableObject-> getWorldBoundingBox(true).intersects(INSTANCE(PlayerManager)->player->movableObject->getWorldBoundingBox(true)) && INSTANCE(PlayerManager)->player->isAlive )
			{
				if (!INSTANCE(PlayerManager)->isGod)
				{
					DieExplosion();
					INSTANCE(PlayerManager)->player->isAlive=false;
					
				}
				else
				{
					(*enemyIt)->healthPoint-=10000;
				}	

			}


			for (std::list<Bullet*>::iterator bulletIt =INSTANCE(BulletManager)->bulletList.begin(); bulletIt !=INSTANCE(BulletManager)->bulletList.end();bulletIt++)
			{
				if ((*enemyIt)->movableObject-> getWorldBoundingBox(true).intersects((*bulletIt)->movableObject->getWorldBoundingBox(true)) &&  (*enemyIt)->enemyState==EnemyState::ALIVE && (*bulletIt)->isAlive)
				{
					switch ((*enemyIt)->enemyType)
					{
					case EnemyType::CANNON:
						INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SCORE_COUNT,true);
						(*enemyIt)->healthPoint-=(*bulletIt)->damage;
						(*bulletIt)->isAlive=false;
						break;
					case EnemyType::PRYAMID:
						INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_ENEMY_FOLLOWER_HIT,true);
						(*enemyIt)->healthPoint-=(*bulletIt)->damage;
						(*bulletIt)->isAlive=false;
						break;

					default:
						break;
					}
				}
			}

		}
	}

	void DieExplosion()
	{
		//Erase all the enemies.
		for (std::list<Enemy*>::iterator enemyIt1 =INSTANCE(EnemyManager)->enemyList.begin(); enemyIt1 !=INSTANCE(EnemyManager)->enemyList.end();enemyIt1++)
		{
			Vector3 dir1=Vector3(0,0,0);
			dir1=(*enemyIt1)->node->convertWorldToLocalPosition(INSTANCE(PlayerManager)->player->node->getPosition());
			if (dir1.length()<90)
			{
				(*enemyIt1)->healthPoint-=10000;
			}
		}
		//Erase all the bullets.
		for (std::list<Bullet*>::iterator bulletIt =INSTANCE(BulletManager)->enemyBulletList.begin(); bulletIt !=INSTANCE(BulletManager)->enemyBulletList.end();bulletIt++)
		{
			Vector3 dir1=Vector3(0,0,0);
			dir1=(*bulletIt)->node->convertWorldToLocalPosition(INSTANCE(PlayerManager)->player->node->getPosition());
			if (dir1.length()<90)
			{
				(*bulletIt)->isAlive=false;
			}
		}
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_DESTROYED,false);

	}
	
	CollisionManager(void)
	{

	}
	~CollisionManager(void)
	{

	}

};

