//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "Enemy.h"
#include "PlayerManager.h"

class EnemyPyramid:public Enemy
{
private:
	SceneNode *yawNode;
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


	void AddTime(Real deltaTime)
	{
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
			//自转
			this->yawNode->roll(Degree(1000*deltaTime),Node::TS_LOCAL);

			//计算摩擦力和加速度
			fx=-vx*k;
			fy=-vy*k;
			vx+=(ax+fx);
			vy+=(ay+fy);
			
			this->node->setPosition(0,0,0);
			this->node->translate(Vector3(0,INSTANCE(PlanetManager)->planet->radius+1,0),Node::TS_LOCAL);
			this->node->yaw(Degree(vx * deltaTime), Node::TS_LOCAL);
			this->node->pitch(Degree(vy * deltaTime),Node::TS_LOCAL);

			
			break;
		case EnemyState::DYING:
			//INSTANCE(ItemManager)->AddExplosion(ItemType::EXPLOSION_1,this->node->getPosition());
			INSTANCE(ItemManager)->AddRandomExplosion(this->node->getPosition());
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_ENEMY_FOLLOWER_DESTROYED,true);
			INSTANCE(ScoreManager)->AddScore(ScoreType::SCORE_PRYAMID);
			this->enemyState=EnemyState::DEAD;
			break;
		case EnemyState::DEAD:
			break;
		default:
			break;
		}

	}

	EnemyPyramid()
	{
		isAlive=false;
		rotateAxis=Vector3::ZERO;
		spawnTime=1.5;
		healthPoint=1000;
		enemyType=EnemyType::PRYAMID;
		SetupContent();
		k=0.02;
		fx=0.0;
		fy=0.0;
		ax=0.0;
		ay=0.0;
		vx=0.0;
		vy=0.0;
		isTracing=true;
		
	}
	~EnemyPyramid()
	{
		

		
	}

};