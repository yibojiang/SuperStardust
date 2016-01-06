#include "AudioManager.h"
AudioManager::AudioManager(void)
{
	Init();
}

AudioManager::~AudioManager(void)
{

}

void AudioManager::Init(void)
{
	//²¥·ÅBGM
	bgmMgr=SoundManager::createManager();//ÉùÒô 
	bgmMgr->init();
	
	bgmMgr->setAudioPath((char*) "..\\resources\\bgm\\");

	bgmMgr->loadAudio( "SND0.AT3.ogg", &audioId, true);
	bgmMgr->loadAudio( "arcade_planet_2.ogg", &audioId, true);
	bgmMgr->loadAudio( "arcade_boss.ogg", &audioId, true);
	soundMgr=SoundManager::createManager();//ÉùÒô 
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
	
	
	

	
}
