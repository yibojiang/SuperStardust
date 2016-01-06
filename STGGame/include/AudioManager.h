//Super Stardust for pc by yibojiang is licensed under a Creative Commons 署名-非商业性使用-相同方式共享 3.0 Unported License.
#pragma once
#include "libOpenAl.h"
#include "CSingleton.h"

class AudioName
{
public:
	enum AudioId{
		BGM_ORCHESTRAL_MENU=0,//标题菜单bgm
		BGM_ARCADE_PLANET_2,//游戏场景bgm
		BGM_ARCADE_BOSS,
		SOUND_SHOOT2,
		SOUND_SHOOT1,
		SOUND_SHUTDOWN,
		SOUND_MOVE,
		SOUND_SHIP_BOOST,
		SOUND_SHIP_BOOST_READY,
		SOUND_BREAK,
		SOUND_BACK,
		SOUND_SELECT,
		SOUND_MENUSTART,
		SOUND_ENTER,
		SOUND_PS3SOUND,
		SOUND_SHIP_TOKEN_COLLECTED,
		SOUND_SHIP_BOOST_NOTREADY,
		SOUND_SHIP_SPAWNSHIP_SPAWN,
		SOUND_SPEECH_WEAPON_UP,
		SOUND_SPEECH_WEAPON_MAXMIZED,
		SOUND_SPEECH_WEAPON_OVERDRIVE,
		SOUND_SPEECH_GOLD_MELTER_ACTIVATED,
		SOUND_SPEECH_ICE_SPLITTER_ACTIVATED,
		SOUND_VITTUMAINEN_CANNON,
		SOUND_PS3TROPHY,
		SOUND_WEAPON_OVERDRIVE_OVER,
		SOUND_WEAPON_PLASMA1_SHOT,
		SOUND_WEAPON_PLASMA2_HIT,
		SOUND_WEAPON_PLASMA3_SHOT,
		SOUND_WEAPON_BOMB_OUT_OF_BOMBS,
		SOUND_WEAPON_ANTIMATTER_PLANE,
		SOUND_SCORE_COUNT,
		SOUND_SHIP_DESTROYED,
		SOUND_CANNON_SHOTTTT,
		SOUND_SPEECH_EXTRA_SHIP,
		SOUND_SPEECH_BOMB,
		SOUND_SPEECH_ROCK_CRUSHER_ACTIVATED,
		SOUND_EXPLOSION_WITH_BASS2,
		SOUND_ENEMY_FOLLOWER_DESTROYED,
		SOUND_ENEMY_FOLLOWER_HIT,
		SOUND_ENEMY_FOLLOWER_SPAWNED,

		SOUND_MENU_ADJUST_SLIDER_OR_VALUE,
		SOUND_MENU_INVALID_SELECTION_OR_ACTI,
		SOUND_MENU_MOVE,
		SOUND_MENU_PREVIOUS_SCREEN,
		SOUND_MENU_SELECT,
		SOUND_NEW_LINE_SHOWN,

		SOUND_SPEECH_ACCELERATING,


	};
};


class AudioManager
{
public:
	void Init(void)
	{
		//播放BGM
		bgmMgr=SoundManager::createManager();//声音 
		bgmMgr->init();

		bgmMgr->setAudioPath((char*) "..\\resources\\bgm\\");

		bgmMgr->loadAudio( "orchestral_menu.ogg", &audioId, true);
		bgmMgr->loadAudio( "arcade_planet_2.ogg", &audioId, true);
		bgmMgr->loadAudio( "arcade_boss.ogg", &audioId, true);
		soundMgr=SoundManager::createManager();//声音 
		soundMgr->init();
		soundMgr->setAudioPath((char*) "..\\resources\\sound\\");

		soundMgr->loadAudio( "shoot2.wav", &audioId, false);
		soundMgr->loadAudio( "shoot1.wav", &audioId, false);
		soundMgr->loadAudio( "shotdown.wav", &audioId, false);
		soundMgr->loadAudio( "move.wav", &audioId, false);
		soundMgr->loadAudio( "ship_boost.wav", &audioId, false);
		soundMgr->loadAudio( "ship_boost_ready.wav", &audioId, false);
		soundMgr->loadAudio( "break.wav", &audioId, false);
		soundMgr->loadAudio("back.wav",&audioId,false);
		soundMgr->loadAudio("select.wav",&audioId,false);
		soundMgr->loadAudio("menustart.wav",&audioId,false);
		soundMgr->loadAudio("enter.wav",&audioId,false);
		soundMgr->loadAudio("PS3Sound.ogg",&audioId,false);

		soundMgr->loadAudio("ship_token_collected.wav",&audioId,false);
		soundMgr->loadAudio("ship_boost_notready.wav",&audioId,false);
		soundMgr->loadAudio("ship_spawn.wav",&audioId,false);
		soundMgr->loadAudio("speech_weapon_up.wav",&audioId,false);
		soundMgr->loadAudio("speech_weapon_maximized.wav",&audioId,false);
		soundMgr->loadAudio("speech_weapon_overdrive.wav",&audioId,false);
		soundMgr->loadAudio("speech_gold_melter_activated.wav",&audioId,false);
		soundMgr->loadAudio("speech_ice_splitter_activated.wav",&audioId,false);
		soundMgr->loadAudio("vittumainen_cannon.wav",&audioId,false);
		soundMgr->loadAudio("PS3trophy.wav",&audioId,false);
		soundMgr->loadAudio("weapon_overdrive_over.wav",&audioId,false);
		soundMgr->loadAudio("weapon_plasma1_shot.wav",&audioId,false);
		soundMgr->loadAudio("weapon_plasma2_hit.wav",&audioId,false);
		soundMgr->loadAudio("weapon_plasma3_shot.wav",&audioId,false);
		soundMgr->loadAudio("weapon_bomb_out_of_bombs.wav",&audioId,false);
		soundMgr->loadAudio("weapon_antimatter_plane.wav",&audioId,false);
		soundMgr->loadAudio("score_count.wav",&audioId,false);
		soundMgr->loadAudio("ship_destroyed.wav",&audioId,false);
		soundMgr->loadAudio("cannon_shotttt.wav",&audioId,false);
		soundMgr->loadAudio("speech_extra_ship.wav",&audioId,false);
		soundMgr->loadAudio("speech_bomb.wav",&audioId,false);
		soundMgr->loadAudio("speech_rock_crusher_activated.wav",&audioId,false);
		soundMgr->loadAudio("explosion_with_bass2.wav",&audioId,false);
		soundMgr->loadAudio("enemy_follower_destroyed.wav",&audioId,false);
		soundMgr->loadAudio("enemy_follower_hit.wav",&audioId,false);
		soundMgr->loadAudio("enemy_follower_spawned.wav",&audioId,false);

		soundMgr->loadAudio("menu_adjust_slider_or_value.wav",&audioId,false);
		soundMgr->loadAudio("menu_invalid_selection_or_acti.wav",&audioId,false);
		soundMgr->loadAudio("menu_move.wav",&audioId,false);
		soundMgr->loadAudio("menu_previous_screen.wav",&audioId,false);
		soundMgr->loadAudio("menu_select.wav",&audioId,false);
		soundMgr->loadAudio("new_line_shown.wav",&audioId,false);

		soundMgr->loadAudio("speech_accelerating.wav",&audioId,false);
		
	}
	SINGLETON(AudioManager);//单件
	unsigned int audioId;
	SoundManager* soundMgr;//音效
	SoundManager* bgmMgr;//背景音乐
	AudioManager(void)
	{
		Init();
	}
	~AudioManager(void)
	{

	}
	
};

