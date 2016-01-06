//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "Player.h"
#include "GreenBulletConfig.h"
#include "BlueBulletConfig.h"
#include "RedBulletConfig.h"


#define BOSTING_TOGGLE 0.6
#define SPAWN_TOGGLE 5
#define PROTECTED_TOGGLE 5
#define SPEEDAAC_TOGGLE -8	

class PlayerState
{
public:
	enum PlayerStateId
	{
		SPAWN,
		PROTECTED,
		ALIVE,
		BOOSTING,
		DYING,
		DEAD,
		GAMEOVER,

	};
};
class PlayerManager:public ObjectManager
{
private:
	
	
	//位移向量
	//Vector2 moveDirection;
	
	//开启Crossout模式
	bool crossoutEnable;
	bool crossoutButton;
	bool isFire;


	bool isDown;
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isMove;
	Vector2 acc;
	Vector2 cacc;

	bool fireUp;
	bool fireDown;
	bool fireLeft;
	bool fireRight;
	
	
	Vector2 facc;

	Real fax,fay,ffx,ffy,fk,fvx,fvy;
	Real ax,ay,fx,fy,k,vx,vy;

	Real shipSpeedrate;
	
	Real fireToggle;
	Real ProtectedToggle;
	Real SpownToggle;
	
	Real boostingToogle;
	int shipSpeedAcc;
	
	ParticleSystem *exploisionPS;
	ParticleSystem *boostPS;
	

	void SetupContent();
	void SpeedUp();

	//装弹
	void PrepareBulletList();
	void Fire(Real deltaTime);
	void Bomb();
	void UpdateShip(Real deltaTime);

	

	SceneNode *protectedBubble;
	Real flashToggle;
public:
	int playerState;

	Real speedAccToggle;

	SceneNode *cameraGoal;
	
	//准备好的子弹
	std::list<Bullet*> fireList;
	BulletConfig *curBulletConf;
	GreenBulletConfig *greenBulletConf;
	BlueBulletConfig *blueBulletConf;
	RedBulletConfig *redBulletConf;

	//换弹
	void SwitchBulletType(BulletConfig *bulletConfig);


	bool isGod;
	int bombNum;
	int lifeNum;
	void GetBomb();
	void GetLife();
	void Show();
	void Hide();
	


	void Crossout();


	//单件
	SINGLETON(PlayerManager);

	void Reset();

	PlayerManager(void);
	~PlayerManager(void);
	
	
	Player *player;
	bool isControllerOn;

	void Init();
	
	void ResetController();

	void ResetShip();

	void SetLifeNum(int life);

	void SetBombNum(int bomb);
	
	void AddTime(Real deltaTime);
	
	void InjectKeyDown(const OIS::KeyEvent& evt);

	void InjectKeyUp(const OIS::KeyEvent& evt);

	void InjectButtonPressed( const OIS::JoyStickEvent &arg, int button );
	void InjectButtonReleased( const OIS::JoyStickEvent &arg, int button );
	void InjectAxisMoved( const OIS::JoyStickEvent &arg, int axis );
};

