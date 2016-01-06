//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#include "PlayerManager.h"
#include "BulletManager.h"
#include "PlanetManager.h"
#include "EnemyManager.h"
#include "DisplayManager.h"
#include "CameraManager.h"

PlayerManager::PlayerManager(void)
{

}


PlayerManager::~PlayerManager(void)
{
	

}

void PlayerManager::GetBomb()
{
	bombNum++;
	INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_BOMB,true);
}

void PlayerManager::GetLife()
{
	lifeNum++;
	INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_EXTRA_SHIP,true);
}


void PlayerManager::Init()
{
	sceneMgr=INSTANCE(WorldManager)->GetSceneManager();

	greenBulletConf=new GreenBulletConfig(80);
	greenBulletConf->Upgrade(1);
	

	blueBulletConf=new BlueBulletConfig(80);
	blueBulletConf->Upgrade(1);

	redBulletConf=new RedBulletConfig(60);
	redBulletConf->Upgrade(1);

	curBulletConf=greenBulletConf;

	player=new Player();

	SetupContent();
	crossoutEnable=false;
	crossoutButton=false;
	isUp=false;
	isDown=false;
	isLeft=false;
	isRight=false;
	isFire=false;
	fireUp=false;
	fireDown=false;
	fireLeft=false;
	fireRight=false;
	isControllerOn=false;

	//位移向量
	//moveDirection=Vector2::ZERO;
	
	shipSpeedAcc=1;
	vx=0.0;
	vy=0.0;
	ax=0.0;//设置加速度
	ay=0.0;
	fx=0.0;//设置摩擦加速度
	fy=0.0;
	k=0.11;//设置阻尼系数

	fvx=0.0;
	fvy=0.0;
	fax=0.0;//设置加速度
	fay=0.0;
	ffx=0.0;//设置摩擦加速度
	ffy=0.0;

	
	cacc=Vector2::ZERO;


	shipSpeedrate=3.0;

	fk= curBulletConf->turnRate;

	fireToggle=0.0;
	speedAccToggle=-1.0;
	SpownToggle=SPAWN_TOGGLE;
	boostingToogle=-1.0;

	flashToggle=0.1;
	isGod=false;
	
	player->isAlive=false;

	//初始化玩家状态
	playerState=PlayerState::SPAWN;

	//创建3号相机（飞船跟踪）
	cameraGoal=player->node->createChildSceneNode(Vector3(0,0,60));
	SetBombNum(99);
	SetLifeNum(3);
}

void PlayerManager::SetLifeNum(int life)
{
	lifeNum=life;
}
void PlayerManager::SetBombNum(int bomb)
{
	bombNum=bomb;
}
void PlayerManager::ResetController()
{
	ax=0;
	ay=0;
	isLeft=false;
	isRight=false;
	isUp=false;
	isDown=false;
	isFire=false;
	fireLeft=false;
	fireRight=false;
	fireDown=false;
	fireUp=false;
	shipSpeedrate=3.0;

}



void PlayerManager::ResetShip()
{
	INSTANCE(AudioManager)->soundMgr->pauseAudio(AudioName::SOUND_MOVE);
	vx=0;
	vy=0;
	ResetController();
	player->shipYawNode->resetOrientation();
	player->shipYawNode->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);

	speedAccToggle=-1;
}

void PlayerManager::SetupContent()
{
	Entity *ent = sceneMgr->createEntity("Spaceship", "spaceship_zero.mesh");
	//Entity *ent = sceneMgr->createEntity("Spaceship", "spaceship.mesh");
	//Entity *ent = sceneMgr->createEntity("Spaceship", "SpaceFighter.mesh");
	player->isAlive=true;
	player->node = sceneMgr->getRootSceneNode()->createChildSceneNode("ShipNode",Vector3(0,0,INSTANCE(PlanetManager)->planet->radius));
	
	player->node->lookAt(Vector3(0,0,0),Node::TS_WORLD);
	
	player->shipYawNode=player->node->createChildSceneNode("ShipYawNode",Vector3(0,0,0));
	player->shipYawNode->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);
	player->shipYawNode->attachObject(ent);
	
	ent=sceneMgr->createEntity("Spaceship_boundingbox","spaceship_boundingbox.mesh");
	player->movableObject=ent;
	player->shipYawNode->attachObject(ent);
	ent->setVisible(false);

	BillboardSet *bbs=sceneMgr->createBillboardSet(1);
	bbs->createBillboard(Vector3::ZERO);
	bbs->setMaterialName("STGGame/Bubble");
	protectedBubble=player->node->createChildSceneNode();
	bbs->setDefaultHeight(10);
	bbs->setDefaultWidth(10);
	protectedBubble->attachObject(bbs);
	protectedBubble->setVisible(false);


#pragma region 尾焰效果

	NameValuePairList params;
	params["numberOfChains"] = "1";
	params["maxElements"] = "80";

	this->player->trail = (RibbonTrail*)sceneMgr->createMovableObject("RibbonTrail", &params);
	sceneMgr->getRootSceneNode()->attachObject(this->player->trail);

	this->player->trail->setMaterialName("STGGame/LightRibbonTrail");
	this->player->trail->setTrailLength(200);

	this->player->trail->setInitialColour(0, 1.0, 0.8, 0.9);
	this->player->trail->setColourChange(0, 1 ,1, 1, 1);
	this->player->trail->setInitialWidth(0, 2.5);


	Light *traillight = sceneMgr->createLight();
	traillight->setDiffuseColour(1.0,1.0,1.0);
	traillight->setPosition(0,5,0);
	this->player->shipYawNode->attachObject(traillight);
	//
	//BillboardSet* bbs;
	//bbs = sceneMgr->createBillboardSet(1);
	//bbs->createBillboard(Vector3::ZERO,ColourValue(0.5,0.0,0.0));
	//bbs->setMaterialName("STGGame/Flare");
	
	this->player->trail->addNode(player->shipYawNode);

	
#pragma endregion 尾焰效果	

	player->node->setVisible(false);
	player->movableObject->setVisible(false);

	exploisionPS=sceneMgr->createParticleSystem("ShipExplosion","STGGame/ShipExplosion");
	
	exploisionPS->setVisible(true);
	exploisionPS->getEmitter(0)->setEnabled(false);
	player->node->attachObject(exploisionPS);

	boostPS=sceneMgr->createParticleSystem("ShipBoost","STGGame/ShipBoost");

	boostPS->setVisible(true);
	boostPS->getEmitter(0)->setEnabled(false);
	player->node->attachObject(boostPS);
	
}
void PlayerManager::Show()
{
	INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_SPAWNSHIP_SPAWN,true);//玩家出现
	player->node->setVisible(true);
	player->movableObject->setVisible(false);
	this->player->trail->setVisible(true);
}
void PlayerManager::Hide()
{
	player->shipYawNode->setVisible(false);
	player->movableObject->setVisible(false);
	this->player->trail->setVisible(false);
	
}
void PlayerManager::SpeedUp()
{
	if (speedAccToggle<0)
	{				
		boostingToogle=BOSTING_TOGGLE;
		speedAccToggle=SPEEDAAC_TOGGLE;
		playerState=PlayerState::BOOSTING;
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_BOOST,true);
		
	}
	else
	{
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_BOOST_NOTREADY,true);
	}
}

void PlayerManager::SwitchBulletType(BulletConfig *bulletConfig)
{
	curBulletConf=bulletConfig;
}
void PlayerManager::PrepareBulletList()
{
	int col=curBulletConf->col;
	Degree offsetDegree=curBulletConf->rangeDegree/(col-1);//计算偏移间隔
	Degree offset=curBulletConf->rangeDegree/2;//计算半角
	fireList.clear();
	for (int i=0;i<curBulletConf->bulletCount;i++)
	{
		if (fireList.size()<col)
		{
			if (!curBulletConf->bulletArray[i].isAlive)
			{
				curBulletConf->bulletArray[i].offsetDegree=offset;
				curBulletConf->bulletArray[i].damage=curBulletConf->damage;//伤害值
				curBulletConf->bulletArray[i].speed=curBulletConf->fireRate;//子弹速度
				curBulletConf->bulletArray[i].lifeTime=curBulletConf->lifeTime;//子弹生命
				curBulletConf->bulletArray[i].node->resetOrientation();

				fireList.push_back(&curBulletConf->bulletArray[i]);
				offset-=offsetDegree;
			}
		}
		else
		{
			break;
		}
	}

}
void PlayerManager::Fire(Real deltaTime)
{
	if (fireToggle<0.0)
	{
		PrepareBulletList();//装弹
		for (std::list<Bullet*>::iterator it =fireList.begin(); it != fireList.end(); it++)
		{
			Vector3 dir=Vector3(0,0,0);

			//TODO: Crossout Fire
			if (crossoutEnable)
			{
				
				fvx=player->shipYawNode->getOrientation().zAxis().x;
				fvy=player->shipYawNode->getOrientation().zAxis().y;
			}

			dir.x=fvx*cos((*it)->offsetDegree.valueRadians())-fvy*sin((*it)->offsetDegree.valueRadians());
			dir.y=fvx*sin((*it)->offsetDegree.valueRadians())+fvy*cos((*it)->offsetDegree.valueRadians());


			SceneNode *node=player->node;
			(*it)->rotateAxis=node->convertLocalToWorldPosition(dir).crossProduct(node->getPosition()).normalisedCopy();

		}	

		while (!fireList.empty())
		{
			fireList.back()->isAlive=true;
			fireList.back()->node->setVisible(true);
			fireList.back()->movableObject->setVisible(false);//隐藏包围盒
			fireList.back()->firePositon=INSTANCE(PlayerManager)->player->node->getPosition();
			INSTANCE(BulletManager)->bulletList.push_back(fireList.back());
			fireList.pop_back();
		}

		INSTANCE(AudioManager)->soundMgr->playAudio(curBulletConf->shotSound,true);
		fireToggle=curBulletConf->fireToggle*deltaTime;
	}

	
}
void PlayerManager::Bomb(void)
{
	if (bombNum>0)
	{
		bombNum--;
		
		
		for (std::list<Enemy*>::iterator enemyIt1 =INSTANCE(EnemyManager)->enemyList.begin(); enemyIt1 !=INSTANCE(EnemyManager)->enemyList.end();enemyIt1++)
		{
			Vector3 dir1=Vector3(0,0,0);
			dir1=(*enemyIt1)->node->convertWorldToLocalPosition(this->player->node->getPosition());
			if (dir1.length()<90)
			{
				(*enemyIt1)->healthPoint-=10000;
			}
		}

		for (std::list<Bullet*>::iterator bulletIt =INSTANCE(BulletManager)->enemyBulletList.begin(); bulletIt !=INSTANCE(BulletManager)->enemyBulletList.end();bulletIt++)
		{
			Vector3 dir1=Vector3(0,0,0);
			dir1=(*bulletIt)->node->convertWorldToLocalPosition(this->player->node->getPosition());
			if (dir1.length()<90)
			{
				(*bulletIt)->isAlive=false;
			}
		}

		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_WEAPON_ANTIMATTER_PLANE,true);
	}
	else
	{
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_WEAPON_BOMB_OUT_OF_BOMBS,true);
	}
	
}
void PlayerManager::UpdateShip(Real deltaTime)
{
	if (fireToggle>=0.0)
	{
		fireToggle=fireToggle-deltaTime;
	}

	if (speedAccToggle>=0.0)
	{
		speedAccToggle=speedAccToggle-deltaTime;
		if (speedAccToggle<0.0)
		{
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SHIP_BOOST_READY,true);
		}
	}

	if (!isControllerOn)
	{
		isLeft=false;
		isRight=false;
		isUp=false;
		isDown=false;
		isFire=false;	
	}

	facc=Vector2::ZERO;
	if (fireUp)
		facc.y-=1;
	if (fireDown)
		facc.y+=1;
	if (fireLeft)
		facc.x+=1;
	if (fireRight)
		facc.x-=1;

	ffx=-fvx*fk;
	ffy=-fvy*fk;

	fvx+=(facc.x+fax+ffx);
	fvy+=(facc.y+fay+ffy);

	if ((facc!=Vector2::ZERO) || ((fax+fay)!=0))
	{
		Fire(deltaTime);
	}

	acc=Vector2::ZERO;

	

	if (isUp)
		acc.y-=1;
	if (isDown)
		acc.y+=1;
	if (isLeft)
		acc.x-=1;
	if(isRight)
		acc.x+=1;

	acc.normalise();

	//计算摩擦力
	fx=-vx*k;
	fy=-vy*k;

	//计算速度
	vx+=(acc.x+ax+fx);
	vy+=(acc.y+ay+fy);

	//TODO: CrossoutMode
	if (crossoutEnable)
	{
		//if (isFire)
		//{
			Fire(deltaTime);
		//}
		cacc=Vector2::ZERO;
		vx=-10*player->shipYawNode->getOrientation().zAxis().x;
		vy=10*player->shipYawNode->getOrientation().zAxis().y;

		if (crossoutButton)
		{
			cacc.x=-player->shipYawNode->getOrientation().xAxis().x;
			cacc.y=player->shipYawNode->getOrientation().xAxis().y;
		}
		else
		{
			cacc.x=player->shipYawNode->getOrientation().xAxis().x;
			cacc.y=-player->shipYawNode->getOrientation().xAxis().y;
		}
		cacc.normalise();
		//INSTANCE(DisplayManager)->debugText->msg->setCaption(Ogre::StringConverter::toString(acc.x) + ", " + Ogre::StringConverter::toString(acc.y));
		//acc.normalise();
		vx+=(cacc.x);
		vy+=(cacc.y);
	}

	player->node->setPosition(0,0,0);
	player->node->translate(0,0,(INSTANCE(PlanetManager)->planet->radius+1.5),Node::TS_LOCAL);

	//四元数旋转
	//Quaternion yawq(Degree(vx*shipSpeedrate * deltaTime),Vector3::UNIT_Y);
	//Quaternion pitchq(Degree(vy*shipSpeedrate * deltaTime),Vector3::UNIT_X);
	//player->node->rotate(pitchq*yawq);

	//欧拉旋转
	player->node->yaw(Degree(vx*shipSpeedrate * deltaTime),Node::TS_LOCAL);
	player->node->pitch(Degree(vy*shipSpeedrate * deltaTime),Node::TS_LOCAL);


	player->shipYawNode->lookAt(Vector3(0,0,0),Node::TS_WORLD,Vector3::NEGATIVE_UNIT_Y);
	player->shipYawNode->lookAt(Vector3(vx,-vy,0),Node::TS_PARENT,Vector3::NEGATIVE_UNIT_Z);

	//移动音效
	/*
	if (!isUp && !isDown && !isLeft && !isRight)
	{
		INSTANCE(AudioManager)->soundMgr->pauseAudio(AudioName::SOUND_MOVE);
	}
	else
	{
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MOVE,false);
	}
	*/
	if (Math::Abs(acc.x) >0 || Math::Abs(acc.y) >0 || Math::Abs(ax) >0 || Math::Abs(ay) >0 || Math::Abs(ax) >0 || Math::Abs(cacc.x) >0  || Math::Abs(cacc.y) >0)
	{
		INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_MOVE,false);
	}
	else
	{
		INSTANCE(AudioManager)->soundMgr->pauseAudio(AudioName::SOUND_MOVE);
	}
		
}

//开启Crossout模式
void PlayerManager::Crossout()
{

	crossoutEnable=true;
}

void PlayerManager::AddTime(Real deltaTime)
{

	//Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(exploisionPS->getNumParticles()));
	
	//isGod=true;
	
	//简单的有限状态机
	switch(this->playerState)
	{
	case PlayerState::SPAWN:

		SpownToggle=SpownToggle-deltaTime;
		
		if (SpownToggle<0)
		{
			if (lifeNum<1)
			{
				playerState=PlayerState::GAMEOVER;
				break;
			}
			protectedBubble->setVisible(true);
			playerState=PlayerState::PROTECTED;
			player->isAlive=true;
			isGod=true;
			Show();
			SpownToggle=SPAWN_TOGGLE;//复活时间
			ProtectedToggle=PROTECTED_TOGGLE;
			isControllerOn=true;
		}
		break;
	case PlayerState::PROTECTED:
		exploisionPS->getEmitter(0)->setEnabled(false);
		
		ProtectedToggle=ProtectedToggle-deltaTime;
		isGod=true;
		UpdateShip(deltaTime);

		flashToggle=flashToggle-deltaTime;
		if (ProtectedToggle<2 && flashToggle<0)
		{
			protectedBubble->flipVisibility();
			flashToggle=0.1;

		}
		if (ProtectedToggle<0)
		{
			protectedBubble->setVisible(false);
			playerState=PlayerState::ALIVE;
			isGod=false;
		}
		break;
	case PlayerState::ALIVE:
		
		UpdateShip(deltaTime);
		boostPS->getEmitter(0)->setEnabled(false);
		//boostPS->setKeepParticlesInLocalSpace(true);
		if (!player->isAlive)
		{
			playerState=PlayerState::DYING;
		}
		
		break;
	case PlayerState::BOOSTING:
		isGod=true;
		boostingToogle=boostingToogle-deltaTime;
		vx=-50*player->shipYawNode->getOrientation().zAxis().x;
		vy=50*player->shipYawNode->getOrientation().zAxis().y;
		UpdateShip(deltaTime);
		boostPS->getEmitter(0)->setEnabled(true);
		boostPS->getEmitter(0)->setDirection( Vector3(player->shipYawNode->getOrientation().zAxis().x,player->shipYawNode->getOrientation().zAxis().y,-player->shipYawNode->getOrientation().zAxis().z));
		
		//boostPS->getEmitter(0)->setDirection(player->node->getAutoTrackLocalDirection());
		if (boostingToogle<0.0)
		{
			isGod=false;
			protectedBubble->setVisible(false);
			playerState=PlayerState::ALIVE;
		}
		break;
	case PlayerState::DYING:
		exploisionPS->getEmitter(0)->setEnabled(true);
		lifeNum--;
		playerState=PlayerState::DEAD;
		break;
	case PlayerState::DEAD:
		Hide();
		ResetShip();
		isControllerOn=false;
		playerState=PlayerState::SPAWN;
		break;
	case PlayerState::GAMEOVER:

		break;
	default:
		break;
	}

	
	
}
void PlayerManager::InjectKeyDown(const OIS::KeyEvent& evt)
{


	if(isControllerOn)
	{
		//if (evt.key == OIS::KC_W) moveDirection.y = -1;
		//else if (evt.key == OIS::KC_A) moveDirection.x = -1;
		//else if (evt.key == OIS::KC_S) moveDirection.y = 1;
		//else if (evt.key == OIS::KC_D) moveDirection.x = 1;
		if(crossoutEnable)
		{
			switch (evt.key)
			{
			case OIS::KC_RETURN:
				crossoutButton=true;
				break;
			case OIS::KC_SPACE:
				Bomb();
				break;
			case OIS::KC_LSHIFT:
				shipSpeedrate=1.6;
				break;
			case OIS::KC_1:
				SwitchBulletType(greenBulletConf);
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_ROCK_CRUSHER_ACTIVATED,true);
				fk= curBulletConf->turnRate;
				break;
			case OIS::KC_2:
				SwitchBulletType(blueBulletConf);
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_ICE_SPLITTER_ACTIVATED,true);
				fk= curBulletConf->turnRate;
				break;
			case OIS::KC_3:
				SwitchBulletType(redBulletConf);
				INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_GOLD_MELTER_ACTIVATED,true);
				fk= curBulletConf->turnRate;
				break;
			default:
				break;
			}
			return;
		}

		switch (evt.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			isUp=true;
			break;
		case OIS::KC_DOWN:
		case OIS::KC_S:
			isDown=true;
			break;

		case OIS::KC_LEFT:
		case OIS::KC_A:
			isLeft=true;
			break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:
			isRight=true;
			break;

		case OIS::KC_LSHIFT:
			shipSpeedrate=1.6;
			break;
		case OIS::KC_RSHIFT:
			SpeedUp();
			break;
		case OIS::KC_O:
			fireUp=true;
			break;
		case OIS::KC_K:
			fireLeft=true;
			break;
		case OIS::KC_SEMICOLON:
			fireRight=true;
			break;
		case OIS::KC_L:
			fireDown=true;
			break;
		case OIS::KC_SPACE:
			Bomb();
			break;
		case OIS::KC_1:
			SwitchBulletType(greenBulletConf);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_ROCK_CRUSHER_ACTIVATED,true);
			fk= curBulletConf->turnRate;
			break;
		case OIS::KC_2:
			SwitchBulletType(blueBulletConf);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_ICE_SPLITTER_ACTIVATED,true);
			fk= curBulletConf->turnRate;
			break;
		case OIS::KC_3:
			SwitchBulletType(redBulletConf);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_GOLD_MELTER_ACTIVATED,true);
			fk= curBulletConf->turnRate;
			break;


		default:
			break;
		}
	}
	
}
void PlayerManager::InjectKeyUp(const OIS::KeyEvent& 
	evt)
{
	
	if(isControllerOn)
	{
		//if (evt.key == OIS::KC_W && moveDirection.y == -1) moveDirection.y = 0;
		//else if (evt.key == OIS::KC_A && moveDirection.x == -1) moveDirection.x = 0;
		//else if (evt.key == OIS::KC_S && moveDirection.y == 1) moveDirection.y = 0;
		//else if (evt.key == OIS::KC_D && moveDirection.x == 1) moveDirection.x = 0;
		if(crossoutEnable)
		{
			switch (evt.key)
			{
			case OIS::KC_RETURN:
				crossoutButton=false;
				break;
			case OIS::KC_SPACE:
				isFire=false;
				break;
			case OIS::KC_LSHIFT:
				shipSpeedrate=3.0;
				break;
			default:
				break;
			}
			return;
		}

		switch (evt.key)
		{
		case OIS::KC_UP:
		case OIS::KC_W:
			isUp=false;
			break;

		case OIS::KC_DOWN:
		case OIS::KC_S:
			isDown=false;
			break;

		case OIS::KC_LEFT:
		case OIS::KC_A:
			isLeft=false;
			break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:
			isRight=false;
			break;

		case OIS::KC_LSHIFT:
			shipSpeedrate=3.0;
			break;
		case OIS::KC_RSHIFT:
			break;

		case OIS::KC_O:
			fireUp=false;
			break;
		case OIS::KC_K:
			fireLeft=false;
			break;
		case OIS::KC_SEMICOLON:
			fireRight=false;
			break;
		case OIS::KC_L:
			fireDown=false;
			break;
		default:
			break;
		}
	}
}

void PlayerManager::Reset()
{
	sceneMgr->destroyParticleSystem(exploisionPS);
	

	delete greenBulletConf;
	delete blueBulletConf;
	delete redBulletConf;

	delete player;
}

void PlayerManager::InjectButtonPressed( const OIS::JoyStickEvent &arg, int button )
{
	if(isControllerOn)
	{
		switch(button)
		{
			
		case 0://A
			SwitchBulletType(greenBulletConf);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_ROCK_CRUSHER_ACTIVATED,true);
			fk= curBulletConf->turnRate;
			break;
		case 1://B
			SwitchBulletType(redBulletConf);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_GOLD_MELTER_ACTIVATED,true);
			fk= curBulletConf->turnRate;
			break;
		case 2://X
			SwitchBulletType(blueBulletConf);
			INSTANCE(AudioManager)->soundMgr->playAudio(AudioName::SOUND_SPEECH_ICE_SPLITTER_ACTIVATED,true);
			fk= curBulletConf->turnRate;
			break;
		case 3://Y
			
			break;
		case 4://LA
			SpeedUp();
			break;
		case 5://RA
			Bomb();
			break;
		case 6://BACK
		
			break;
		case 7://START
		
			
			break;
		}
	}
}

void PlayerManager::InjectButtonReleased( const OIS::JoyStickEvent &arg, int button )
{

}

void PlayerManager::InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis )
{
	if(isControllerOn)
	{
		ax=arg.state.mAxes[1].abs*1.0/32767;
		ay=arg.state.mAxes[0].abs*1.0/32767;
	
		fax=-arg.state.mAxes[3].abs*1.0/32767;
		fay=arg.state.mAxes[2].abs*1.0/32767;

		if (Ogre::Math::Abs(ax)<0.2) ax=0;
		if (Ogre::Math::Abs(ay)<0.2) ay=0;

		if (Ogre::Math::Abs(fax)<0.2) fax=0;
		if (Ogre::Math::Abs(fay)<0.2) fay=0;
	}

	//INSTANCE(DisplayManager)->debugText->msg->setCaption(Ogre::StringConverter::toString(ax) + ", " + Ogre::StringConverter::toString(ay));
	
	


}
