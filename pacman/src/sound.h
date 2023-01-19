#pragma once

#include <stdbool.h>

//The number of sound effects.
//Lemonwater sound effect Ice의 경우를 추가하여 NUM_EFFECTS 7로 수정.
#define NUM_EFFECTS 7

//The different sound effects we can use.
//Lemonwater 각종 효과음 및 배경음 열거형에 추가
typedef enum
{
	LevelStartSound,
	WakawakaSound,
	PacmanDeathSound,
	objectEatSound, //아이템 먹을 때 소
	GameoverSound, // 게임 오버 소리
	LobbySound,//메인 메뉴 소리
	NextStageSound,//다음 레벨 넘어갈 때 소
} SoundEffect;

//Initializes and loads all sounds. Must be called before playing any sounds.
void load_sounds(void);

//Disposes the loaded sounds after we've finished using them.
void dispose_sounds(void);

//Sets the volume to the given value, between 0 - 1.
void set_sound_volume(float volume);

//Gets the sound volume, between 0 - 1.
float get_sound_volume(void);

//Sets the sound to be muted or not.
void set_sound_muted(bool isMuted);

//Checks if the sound is muted or not.
bool is_sound_muted(void);

//Plays the given sound effect.
void play_sound(SoundEffect effectName);

//Stops the given sound effect.
void stop_sound(SoundEffect effectName);

//Plays the music.
void play_music(void);

//Stops the music.
void stop_music(void);
