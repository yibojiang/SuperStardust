#pragma once
#include "Enemy.h"
#include "PlayerManager.h"
#include "PinkBulletConfig.h"

class EnemyBoss01:public Enemy
{
private:
	SceneNode *yawNode;
	Real fireToggle;
	std::list<Bullet*>fireList;
	PinkBulletConfig *bulletConfig;

	Vector3 aimDir;

	void SetupContent()
	{
		SceneManager *sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		Entity *ent= sceneMgr->createEntity( "enemy_pryamid.mesh");
		this->node=sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0,0,0));
		this->yawNode=node->createChildSceneNode();
		this->yawNode->attachObject(ent);
		ent=sceneMgr->createEntity("bullet_boundingbox.mesh");
		this->yawNode->attachObject(ent);
		this->movableObject=ent;
	}
public:

	void InitBulletList()
	{
		for (int i=0;i<bulletConfig->bulletCount;i++)
		{
			bulletConfig->bulletArray[i].speed=bulletConfig->fireRate;//子弹速度
		}
	}
	void PrepareBulletList()
	{
		Degree offsetDegree=bulletConfig->rangeDegree/(bulletConfig->col-1);//计算偏移间隔
		Degree offset=bulletConfig->rangeDegree/2;//计算半角
		fireList.clear();
		for (int i=0;i<bulletConfig->bulletCount;i++)
		{
			if (fireList.size()<bulletConfig->col)
			{
				if (!bulletConfig->bulletArray[i].isAlive)
				{
					bulletConfig->bulletArray[i].offsetDegree=offset;					
					bulletConfig->bulletArray[i].lifeTime=bulletConfig->lifeTime;//子弹生命
					bulletConfig->bulletArray[i].node->resetOrientation();
					fireList.push_back(&bulletConfig->bulletArray[i]);
					offset-=offsetDegree;
				}
			}
			else
			{
				break;
			}
		}
	}

	void Fire(Real deltaTime)
	{
		if (fireToggle<0.0)
		{
			PrepareBulletList();//装弹

			for (std::list<Bullet*>::iterator it = fireList.begin(); it != fireList.end(); it++)
			{
				Vector3 dir=Vector3(0,0,0);
				aimDir=-this->node->convertWorldToLocalPosition(INSTANCE(PlayerManager)->player->node->getPosition());
				dir.x=aimDir.x*cos((*it)->offsetDegree.valueRadians())-aimDir.z*sin((*it)->offsetDegree.valueRadians());
				dir.z=aimDir.x*sin((*it)->offsetDegree.valueRadians())+aimDir.z*cos((*it)->offsetDegree.valueRadians());

				(*it)->rotateAxis=this->node->convertLocalToWorldPosition(dir).crossProduct(this->node->getPosition()).normalisedCopy();

			}	
			BulletRelease();//发射

			fireToggle=bulletConfig->fireToggle*deltaTime;
		}
	}

	void BulletRelease()
	{
		while (!fireList.empty())
		{
			fireList.back()->isAlive=true;
			fireList.back()->node->setVisible(true);
			fireList.back()->movableObject->setVisible(false);//隐藏包围盒
			fireList.back()->firePositon=this->node->getPosition();
			INSTANCE(BulletManager)->enemyBulletList.push_back(fireList.back());
			INSTANCE(AudioManager)->soundMgr->playAudio(bulletConfig->shotSound,true);
			fireList.pop_back();
		}
	}
	void AddTime(Real deltaTime)
	{
		Vector3 Dir1,Dir2,Dir3;
		Vector3 dist=Vector3(0,0,0);
		switch(this->enemyState)
		{
		case EnemyState::SPAWN:
			if (this->node->getPosition().length()>INSTANCE(PlanetManager)->planet->radius+1)
			{		

				this->node->translate(this->node->getPosition().normalisedCopy()*(-1),Node::TS_WORLD);
			}
			else
			{
				this->enemyState=EnemyState::ALIVE;
			}
			break;
		case EnemyState::ALIVE:
			this->yawNode->roll(Degree(1000*deltaTime),Node::TS_LOCAL);

			fx=-vx*k;
			fy=-vy*k;

			vx+=(ax+fx);
			vy+=(ay+fy);


			this->node->setPosition(0,0,0);
			this->node->translate(Vector3(0,INSTANCE(PlanetManager)->planet->radius+1,0),Node::TS_LOCAL);
			this->node->yaw(Degree(vx * deltaTime), Node::TS_LOCAL);
			this->node->pitch(Degree(vy * deltaTime),Node::TS_LOCAL);
			


			if (fireToggle>=0.0)
			{
				fireToggle=fireToggle-deltaTime;
			}
			
			
			Fire(deltaTime);


			break;
		case EnemyState::DYING:
			INSTANCE(ItemManager)->AddExplosion(ItemType::EXPLOSION_2,this->node->getPosition());
			INSTANCE(ScoreManager)->AddScore(ScoreType::SCORE_CANNON);
			this->enemyState=EnemyState::DEAD;
			break;
		case EnemyState::DEAD:		
			break;
		default:
			break;
		}

	}

	EnemyBoss01()
	{
		//TODO
		//bulletConfig=new PinkBulletConfig(100);
		//bulletConfig->Upgrade(5);
		InitBulletList();

		isAlive=false;

		rotateAxis=Vector3::ZERO;
		spawnTime=1.5;
		healthPoint=50000;
		enemyType=EnemyType::BOSS01;
		SetupContent();
		
		k=0.02;
		fx=0.0;
		fy=0.0;
		ax=0.0;
		ay=0.0;
		vx=0.0;
		vy=0.0;
		isTracing=true;
		fireToggle=-1;

		

	}
	~EnemyBoss01()
	{
		CommonTool::DestroyAllAttachedMovableObjects(node);
		movableObject->getParentSceneNode()->removeAndDestroyChild(movableObject->getName());

		node->removeAndDestroyAllChildren();
		node->getParentSceneNode()->removeAndDestroyChild(node->getName());
		delete bulletConfig;
	}

};