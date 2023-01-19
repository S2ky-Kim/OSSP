#pragma once

#include "board.h"
#include "fruit.h"
#include "ghost.h"
#include "pacman.h"
#include "pellet.h"
#include "object.h"
#include "main.h"

typedef enum {
	GameBeginState,
	LevelBeginState,
	GamePlayState,
	WinState,
	DeathState,
	GameoverState,
	ReviveState1,//#14 Kim : 이거 추가해서 ...해보자..그..뭐ㅓㅑ...
	ReviveState2,
	DeathState2,
	PauseState, // lemonwater 5.24 2player mode에서 게임을 종료할 지 다음 스테이지로 갈 지 선택하는 모드
	ContinueState // lemonwater 6.1 계속할건지 묻는 상태
} GameState;

//what you do in current state

//what causes you to transition from state A -> state B

//elevator stationary
//action: do nothing
//transition
//-> moving up (someone presses a button upstairs)
//-> moving down (someone presses a button downstairs)
//-> door opening (someone presses button on current level)
//-> go down/ up (timeout on a specific level)
typedef enum{
	Single,
	Multi,
	Online,
    Help,      //Lemonwater 5.4 add 'help' main.c의 inter_render함수에서 받을 state의 열거형
    Settings,  //Lemonwater 5.4 add 'settings'
	Online_Server,
	Online_Client,
	Multi_TA
}PlayMode;

typedef struct {
	GameState gameState;
	unsigned int ticksSinceModeChange;
	Pacman pacman[2]; // #8 Kim : 1.플레이어수 늘려주기 위해서 배열로 바꿈  Pacman pacman -> pacman[2];
	Ghost ghosts[2][4];
	Board board;

	PelletHolder pelletHolder;
	
	GameFruit gameFruit[2][5];
	//GameFruit gameFruit1, gameFruit2, gameFruit3, gameFruit4, gameFruit5;
	GameObject gameObject[2][5];
	//GameObject gameObject1, gameObject2, gameObject3, gameObject4, gameObject5;
	int highscore;
	int currentLevel;
	
	PlayMode playMode;
	
	int time;
	int get_ticks; // 게임 시작 시점 시간이 가는걸 멈추게 하기 위한 보정 변수. 없으면 게임이 시작하자마자 바로 흘러감.

	int pause_start;
	int pause_end;
	int pause_gap;
	//Lemonwater 6.4 declare three integer variable to restore time in 2player mode 
	int nextlevel_start;
	int nextlevel_end;
	int nextlevel_gap;
} PacmanGame;

//Updates the game 1 tick, or 1/60th of a second.
void game_tick(PacmanGame *game);

//Renders the game in its current state.
void game_render(PacmanGame *game);

//Returns true if the game is finished and is ready to hand back to the menu system.
bool is_game_over(PacmanGame *game);

//Call this at start of level 1 to initialize all entities and game objects.
void gamestart_init(PacmanGame *game);

//Call this at the start of each level to reinitialize all entities to a default state.
void level_init(PacmanGame *game);

//Call after pacman dies to reinitialize entities to continue the same level.
void pacdeath_init(PacmanGame *game,int player_num);

//Returns the length of the given integer.
int int_length(int num);

//#5 Yang : 4. 각 object 효과 구현
void game_object_function(GameObject *gameObject, PacmanGame *game, int playernum);
void game_object_function_end(GameObject *gameObject, PacmanGame *game, int playernum);
