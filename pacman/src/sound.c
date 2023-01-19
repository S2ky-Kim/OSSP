#include "sound.h"

#include <SDL/SDL_mixer.h>

//sound filenames
//static const char *EFFECT_FILES[] = {"wakawaka.wav", "bdc"};
//static const char MUSIC_FILE[] = "Music.wav";

static float volume;
static bool muted;

static Mix_Music *music;
//static Mix_Chunk *effects[NUM_EFFECTS];
//Lemonwater 각종 효과음 및 배경음 추. 
static Mix_Chunk *levelStart; //게임 시작할 때 나는 소리
static Mix_Chunk *pacmanDeath; 
static Mix_Chunk *objectEat;
static Mix_Chunk *lobby;
static Mix_Chunk *nextStage;
static Mix_Chunk *gameOver;
static Mix_Chunk *nextStage;

static int levelStartChanel;
static int lobbyChanel;
static int eatChanel;
static int gameOverChanel;

void load_sounds(void)
{
	//22050 is sound frequency
	//MIX_DEFAULT_FORMAT is the sound format
	//2 is number of channels to use, we use 2 for stereo sound
	//4096 is the sample size
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Error creating sound effects.\n");
		printf("Aborting.\n");
		exit(1);
	}

	//now load the sounds and effects we're using
	//music = Mix_LoadMUS(MUSIC_FILE);

	//for (int i = 0; i < NUM_EFFECTS; i++)
	//{
		//effects[i] = Mix_LoadWAV(EFFECT_FILES[i]);
	//}

	//Lemonwater 효과음 연
	levelStart = Mix_LoadWAV("sound/pacintro2.wav");
	pacmanDeath = Mix_LoadWAV("sound/death.wav");
	objectEat = Mix_LoadWAV("sound/object.wav");
	lobby = Mix_LoadWAV("sound/lobby.wav");
	nextStage = Mix_LoadWAV("sound/nextstage.wav");
	gameOver = Mix_LoadWAV("sound/gameover.wav");
	nextStage = Mix_LoadWAV("sound/nextstage.wav");
	set_sound_volume(0.5);
	set_sound_muted(false);
}

void dispose_sounds(void)
{
	//for (int i = 0; i < NUM_EFFECTS; i++)
	//{
		//Mix_FreeChunk(effects[i]);
	//}

	Mix_FreeChunk(levelStart);

	Mix_FreeMusic(music);
}

void set_sound_volume(float vol)
{
	Mix_VolumeChunk(levelStart, vol * MIX_MAX_VOLUME);
	volume = vol;
}

float get_sound_volume(void)
{
	return volume;
}

void set_sound_muted(bool isMuted)
{
	if (isMuted)
	{
		Mix_VolumeChunk(levelStart, 0);
	}
	else
	{
		set_sound_volume(volume);
	}

	muted = isMuted;
}

bool is_sound_muted(void)
{
	return muted;
}


//Lemonwater 각 경우에 맞는 음악 연
void play_sound(SoundEffect effectName)
{
	Mix_Chunk *chunk;
	int *channel;

	switch (effectName)
	{
		case LevelStartSound:  chunk = levelStart; channel = &levelStartChanel; break;
		case WakawakaSound:    chunk = levelStart; channel = &levelStartChanel; break;
		case PacmanDeathSound: chunk = pacmanDeath; channel = &levelStartChanel; break;
		case objectEatSound:   chunk = objectEat; channel = &eatChanel; break;
		case GameoverSound:    chunk = gameOver; channel = &gameOverChanel; break;
		case LobbySound:       chunk = lobby; channel = &lobbyChanel; break;
		case NextStageSound:   chunk = nextStage; channel = &levelStartChanel; break;
	}

	*channel = Mix_PlayChannel(-1, chunk, 0);
}

void play_music(void)
{

}
//Lemonwater 음악 중단 
void stop_sound(SoundEffect effectName)
{
	int channel;

	switch (effectName)
	{
		case LevelStartSound:  channel = levelStartChanel; break;
		case WakawakaSound:    channel = levelStartChanel; break;
		case PacmanDeathSound: channel = levelStartChanel; break;
		case objectEatSound:    channel = eatChanel; break;
		case GameoverSound:    channel = gameOverChanel; break;
		case LobbySound:    channel = lobbyChanel; break;
		case NextStageSound : channel = levelStartChanel; break;
		default: printf("badsound\naborting\n"); exit(1); //TODO: fix this up
	}

	Mix_HaltChannel(channel);
}

void stop_music(void)
{

}
