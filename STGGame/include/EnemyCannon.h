//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "Enemy.h"
#include "PinkBulletConfig.h"
#include "BulletManager.h"
#include "PlanetManager.h"

#define CANNON_BULLET_COUNT 3
#define CANNON_BULLET_LOAD_TOGGLE 5

class EnemyCannon:public Enemy
{
private:

	Real fireToggle;
	PinkBulletConfig *bulletConfig;

	Real loadToggle;
	int bulletCount;

	void SetupContent()
	{
		SceneManager *sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		Entity *ent= sceneMgr->createEntity( "enemy_cannon.mesh");
		this->node=sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0,0,0));
		this->node->attachObject(ent);
		ent=sceneMgr->createEntity("cannon_boundingbox.mesh");
		this->node->attachObject(ent);
		this->movableObject=ent;

		fireToggle=-1;

	}
public:
	void Fire(Real deltaTime)
	{
		SceneManager *sceneMgr=INSTANCE(WorldManager)->GetSceneManager();
		Bullet *bullet=new Bullet();
		
		NameValuePairList params;
		params["numberOfChains"] = "1";
		params["maxElements"] = "20";

		bullet->trail= (RibbonTrail*)sceneMgr->createMovableObject("RibbonTrail", &params);
		sceneMgr->getRootSceneNode()->attachObject(bullet->trail);
		bullet->trail->setMaterialName("STGGame/LightRibbonTrail");
		bullet->trail->setTrailLength(50);

		//bullet->trail->setInitialColour(0.8, 0.8,0.8, 1);
		//bullet->trail->setColourChange(0, 1.0, 1.0, 1.0, 1);
		bullet->trail->setInitialColour(0, 0.8, 0.3,0.8, 1);
		bullet->trail->setColourChange(0, 1.0, 1.0, 1.0, 0.5);
		bullet->trail->setInitialWidth(0,1);

		


		BillboardSet *bbs = sceneMgr->createBillboardSet(1);
		bbs->createBillboard(Vector3::ZERO,ColourValue(1,0,1));
		bbs->setMaterialName("STGGame/Flare");
		bbs->setDefaultHeight(10);
		bbs->setDefaultWidth(10);


		bullet->node=sceneMgr->getRootSceneNode()->createChildSceneNode();
		bullet->trail->addNode(bullet->node);

		bullet->node->attachObject(bbs);

		Entity *ent = sceneMgr->createEntity("bullet_boundingbox.mesh");
		bullet->node->attachObject(ent);

		bullet->movableObject=ent;


		bullet->lifeTime=bulletConfig->lifeTime;//子弹生命
		bullet->node->resetOrientation();

		bullet->rotateAxis=-this->node->getOrientation().xAxis();

		bullet->isAlive=true;
				
		bullet->damage=bulletConfig->damage;//伤害值
		bullet->speed=bulletConfig->fireRate;//子弹速度

		bullet->node->setVisible(true);
		bullet->movableObject->setVisible(false);//隐藏包围盒
		bullet->firePositon=this->node->getPosition();

		INSTANCE(BulletManager)->enemyBulletList.push_back(bullet);
		INSTANCE(AudioManager)->soundMgr->playAudio(bulletConfig->shotSound,true);



			
		fireToggle=bulletConfig->fireToggle*deltaTime;

	}

	void AddTime(Real deltaTime)
	{
		switch(this->enemyState)
		{
		case EnemyState::SPAWN:
			if (this->node->getPosition().length()>INSTANCE(PlanetManager)->planet->radius+1)
			{
				this->node->lookAt(INSTANCE(PlayerManager)->player->node->getPosition(),Node::TS_WORLD);
				this->node->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);
				this->node->translate(this->node->getPosition().normalisedCopy()*(-0.6),Node::TS_WORLD);
			}
			else
			{
				this->enemyState=EnemyState::ALIVE;
			}
			break;
		case EnemyState::ALIVE:

			if (INSTANCE(PlayerManager)->player->isAlive)
			{

				this->node->lookAt(INSTANCE(PlayerManager)->player->node->getPosition(),Node::TS_WORLD);
				this->node->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);

				if (loadToggle>0.0)
				{
					loadToggle=loadToggle-deltaTime;
				}
				else
				{
					bulletCount=CANNON_BULLET_COUNT;
					loadToggle=CANNON_BULLET_LOAD_TOGGLE;
				}

				if (fireToggle>0.0)
				{
					fireToggle=fireToggle-deltaTime;
				}
				else
				{
					if (bulletCount>0)
					{
					
						Fire(deltaTime);
						bulletCount--;
					
					
					}
				}
			
			}
			


			break;
		case EnemyState::DYING:
			//INSTANCE(ItemManager)->AddExplosion(ItemType::EXPLOSION_2,this->node->getPosition());
			//INSTANCE(ItemManager)->AddRandomExplosion(this->node->getPosition());
			INSTANCE(ItemManager)->AddFirework(ItemType::EXPLOSION_FIRWORK_1,this->node->getPosition());
			
			INSTANCE(ScoreManager)->AddScore(ScoreType::SCORE_CANNON);
			this->enemyState=EnemyState::DEAD;
			break;
		case EnemyState::DEAD:		
			break;
		default:
			break;
		}

	}

	EnemyCannon()
	{
		bulletConfig=new PinkBulletConfig();
		bulletConfig->Upgrade(1);

		isAlive=false;

		rotateAxis=Vector3::ZERO;
		spawnTime=1.5;
		healthPoint=5000;
		enemyType=EnemyType::CANNON;
		fireToggle=3;
		loadToggle=CANNON_BULLET_LOAD_TOGGLE;
		bulletCount=CANNON_BULLET_COUNT;
		SetupContent();

	}
	~EnemyCannon()
	{
		//TODO
	}

};