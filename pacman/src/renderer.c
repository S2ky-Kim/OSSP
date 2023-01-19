#include "renderer.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "animation.h"
#include "imageloader.h"
#include "text.h"
#include "window.h"
#include "ghost.h"
#include "input.h"
//#include "game.h"
//

//
void draw_online_mode(int *s_c_num ,char* tmp);//#19 Kim : 2.menu.c 에있는거 열로 옮겼음
void draw_input_string(const char tmp[],int x,int y);//#19 Kim : 2. 클라이언트 기다리는거 화면 추가. 이름을 맞게 바꿔줌
void draw_multi_mode(int *s_c_num);
void draw_help_mode(int *s_c_num); //Lemonwater 5.4 add 'help'
void draw_settings_mode(int *s_c_num); //Lemonwater 5.4 add 'settings'
void draw_pause(void);

//draws an image at a board coordinate
void draw_image_coord(SDL_Surface *surface, int x, int y);
void draw_image_coord_offset(SDL_Surface *surface, int x, int y, int xOffset, int yOffset);
void draw_playMode(PlayMode playMode);//#13 : 2.메뉴 뷰 테스트중 일단 pellet 인포 지워버리자
//Offset the board is off from the top of the screen
//Needed because some items are stored in board (x,y) coords and need to be rendered at an offset
#define Y_OFFSET 3
static int offset = 3 * 16;


void draw_image_coord(SDL_Surface *surface, int x, int y)
{
	draw_image_coord_offset(surface, x, y, 0, 0);
}

void draw_image_coord_offset(SDL_Surface *surface, int x, int y, int xOffset, int yOffset)
{
	int pixPerTile = 16;
	apply_surface(pixPerTile * x + xOffset, pixPerTile * y + yOffset, surface);
}

//
//
// Vanity screen rendering
//
//

void draw_vanity_ghostline(GhostDisplayRow *row, int y, bool drawDescription, bool drawName)
{
	draw_image_coord(ghost_image(row->type, Right, 0), 4, y);

	if (drawDescription)
	{
		set_text_color(row->color);
		draw_text_coord(get_screen(), row->description, 7, y);
	}

	if (drawName)
	{
		draw_text_coord(get_screen(), row->name, 18, y);
	}
}

void draw_playMode(PlayMode playMode)//#13 : 2.메뉴 뷰 테스트중 일단 pellet 인포 지우고 처리해보자
{
	set_text_color(WhiteText); // #13 Dong : 2. Menu 화면에서 각 모드선택지 마다 빨간색으로 되도록 바꿈
	draw_text_coord(get_screen(), "SINGLE", 10, 20);
	draw_text_coord(get_screen(), "2 PLAYER", 10, 22);
	draw_text_coord(get_screen(), "ONLINE", 10, 24);
    draw_text_coord(get_screen(), "HELP", 10, 26);       //Lemonwater 5.4 add 'help' 초기 메인화면에 help선택지 추가
    draw_text_coord(get_screen(), "SETTINGS", 10, 28);   //Lemonwater 5.4 add 'settings' 초기 메인화면에 settings선택지 추가
	switch(playMode)
	{
	case 0:
		set_text_color(RedText);	// #13 Dong : 2.
		draw_text_coord(get_screen(), "#", 8, 20);
		draw_text_coord(get_screen(), "SINGLE", 10, 20);
		break;
	case 1:
		set_text_color(RedText);	// #13 Dong : 2.
		draw_text_coord(get_screen(), "#", 8, 22);
		draw_text_coord(get_screen(), "2 PLAYER", 10, 22);
		break;
	case 2:
		set_text_color(RedText);	// #13 Dong : 2.
		draw_text_coord(get_screen(), "#", 8, 24);
		draw_text_coord(get_screen(), "ONLINE", 10, 24);
		break;
        case 3:
		set_text_color(RedText);	//Lemonwater 5.4 add 'help'
		draw_text_coord(get_screen(), "#", 8, 26);
		draw_text_coord(get_screen(), "HELP", 10, 26);
		break;
        case 4:
		set_text_color(RedText);	//Lemonwater 5.4 add 'settings'
		draw_text_coord(get_screen(), "#", 8, 28);
		draw_text_coord(get_screen(), "SETTINGS", 10, 28);
		break;
	default :break;

	}
}
void draw_vanity_charnickname(void)
{
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), "CHARACTER / NICKNAME", 7, 5);
}

void draw_vanity_corporate_info(void)
{
	set_text_color(PinkText);
	draw_text_coord(get_screen(), "@      MIDWAY MFG.CO.", 4, 31);
	draw_numtext_coord(get_screen(), "  1980", 4, 31);
}

void draw_vanity_pellet_info(bool flashing)
{
	//TODO: use this properly
	if (flashing) return;

	set_text_color(WhiteText);

	draw_image_coord(small_pellet_image(), 10, 24);
	draw_numtext_coord(get_screen(), "10", 12, 24);
	draw_image_coord(pts_white_image(), 15, 24);

	draw_image_coord(large_pellet_image(), 10, 26);
	draw_numtext_coord(get_screen(), "50", 12, 26);
	draw_image_coord(pts_white_image(), 15, 26);
}

void draw_vanity_animation(int dt)
{
	//TODO do this later
	if (dt)
	{

	}
}

//
//
// Instructions screen renderering
//
//

void draw_instrc_info(void)
{
	set_text_color(OrangeText);
	draw_text_coord(get_screen(), "PUSH START BUTTON", 6, 16);

	set_text_color(CyanText);
	draw_text_coord(get_screen(), "  PLAYER ONLY", 8, 20);
	draw_numtext_coord(get_screen(), "1", 8, 20);

	set_text_color(PeachText);
	draw_text_coord(get_screen(), "BONUS PAC-MAN FOR", 1, 24);
	draw_numtext_coord(get_screen(), "                  10000", 1, 24);
	draw_image_coord(pts_peach_image(), 25, 24);
}

void draw_instrc_corporate_info(void)
{
	set_text_color(PinkText);
	draw_text_coord(get_screen(), "@      MIDWAY MFG.CO.", 4, 28);
	draw_numtext_coord(get_screen(), "  1980", 4, 28);
}

//
//
// Common menu rendering
//
//

void draw_common_oneup(bool flashing, int score)
{
	set_text_color(WhiteText);
	draw_numtext_coord(get_screen(), "1", 3, 0);
	draw_text_coord(get_screen(), "UP", 4, 0);

	if (flashing && animation_get_frame(265, 2)) return;

	char scoreStr[256];
	sprintf(scoreStr, "%01i", score);
	draw_text_coord(get_screen(), scoreStr, 6 - int_length(score), 1);
}

void draw_common_twoup(bool flashing, int score, int flag)
{
	if(flag){
		set_text_color(WhiteText);
		draw_numtext_coord(get_screen(), "2", 22, 0);
		draw_text_coord(get_screen(), "UP", 23, 0);

		if (flashing && animation_get_frame(265, 2)) return;

		char scoreStr[256];
		sprintf(scoreStr, "%01i", score);
		draw_text_coord(get_screen(), scoreStr, 25 - int_length(score), 1);// #37 Ya록ng : 2P UI 추가 :점수보이도
	}
	else{
		set_text_color(WhiteText);
		draw_numtext_coord(get_screen(), "2", 53, 0);
		draw_text_coord(get_screen(), "UP", 54, 0);

		if (flashing && animation_get_frame(265, 2)) return;

		char scoreStr[256];
		sprintf(scoreStr, "%01i", score);
		draw_text_coord(get_screen(), scoreStr, 55 - int_length(score), 1);// #37 Ya록ng : 2P UI 추가 :점수보이도
	}
}

void draw_common_highscore(int highscore)
{
	set_text_color(WhiteText);
	//draw_text_coord(get_screen(), "HIGH SCORE", 9, 0);

	//game doesn't render highscore if it is 0 for some reason. Emulate this behaviour
	if (highscore == 0) return;

	char scoreStr[256];
	sprintf(scoreStr, "%01i", highscore);
	//draw_text_coord(get_screen(), scoreStr, 16 - int_length(highscore), 1);
}
void draw_game_time(int time)
{
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), "TIME", 12, 0);
	char timeStr[256];
	sprintf(timeStr, "%01i", time);
	draw_text_coord(get_screen(), timeStr, 15 - int_length(time), 1);
}

void draw_credits(int numCredits)
{
	if (numCredits < 0)
	{
		printf("negative number credits: %d\naborting\b", numCredits);
		exit(1);
	}

	char scoreStr[256];
	sprintf(scoreStr, "   %i", numCredits);

	//draw credit + number of credits at the appropriate place
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), "CREDIT", 2, 35);

	draw_numtext_coord(get_screen(), scoreStr, 8 - int_length(numCredits), 35);
}

//
// Game-only word rendering
//
//Lemonwater 6.3 delete useless words
/*void draw_game_playerone_start(void)
{
	set_text_color(CyanText);
	draw_text_coord(get_screen(), "PLAYER ONE", 9, 14);
}

void draw_game_playertwo_start(void)
{

}*/

void draw_game_ready(void)
{
	set_text_color(YellowText);
	draw_text_coord(get_screen(), "READY!", 11, 20);
}

void draw_game_gameover(void)
{
	set_text_color(RedText);
	draw_text_coord(get_screen(), "GAME  OVER", 9, 20);
}
//#30 Yang :winner 표시 뷰
//Lemonwater 6.3 add a new words whether you continue a game or not
void draw_game_playerone_win(int*s_c_num_game)
{
	set_text_color(RedText);
	draw_text_coord(get_screen(), "PLAYER 1 WIN!", 7, 20);
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), "CONTINUE?", 9, 22);
	draw_text_coord(get_screen(), "YES", 7, 24);
	draw_text_coord(get_screen(), "NO", 18, 24);
	if (*s_c_num_game==0) {
		set_text_color(RedText);
		draw_text_coord(get_screen(), "YES", 7, 24);
	}
	else if (*s_c_num_game==1) {
		set_text_color(RedText);
		draw_text_coord(get_screen(), "NO", 18, 24);
	}
}
void draw_game_playertwo_win(int*s_c_num_game)
{
	set_text_color(RedText);
	draw_text_coord(get_screen(), "PLAYER 2 WIN!", 7, 20);
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), "CONTINUE?", 9, 22);
	draw_text_coord(get_screen(), "YES", 7, 24);
	draw_text_coord(get_screen(), "NO", 18, 24);
	if (*s_c_num_game==0) {
		set_text_color(RedText);
		draw_text_coord(get_screen(), "YES", 7, 24);
	}
	else if (*s_c_num_game==1) {
		set_text_color(RedText);
		draw_text_coord(get_screen(), "NO", 18, 24);
	}
}
//
//
// Fruit renderering
//
//

void draw_fruit_indicators(int currentLevel)
{
	if (currentLevel < 1)
	{
		printf("invalid level number for drawing fruit: %d\naborting\n", currentLevel);
		exit(1);
	}
	if(Multi_flags() == 1) // # 9 Dong : 2P 맵 추가를 위한 수정
	{
		int x = 54 * 16;
		int y = 34 * 16;
		int index = currentLevel > 7 ? 7 : currentLevel;

		for (int i = index; i > 0; i--)
		{
			Fruit fruit = fruit_for_level(currentLevel - (index - i));
			SDL_Surface *image = get_fruit_image(fruit);

			apply_surface(x - i * 16 * 2, y, image);
		}
	}
	else
	{
		int x = 26 * 16;
		int y = 34 * 16;
		int index = currentLevel > 7 ? 7 : currentLevel;

		for (int i = index; i > 0; i--)
		{
			Fruit fruit = fruit_for_level(currentLevel - (index - i));
			SDL_Surface *image = get_fruit_image(fruit);

			apply_surface(x - i * 16 * 2, y, image);
		}
	}

}

//Draws the fruit in the middle of the level.
void draw_fruit_game(int currentLevel, GameFruit *gameFruit)
{
	Fruit fruit = fruit_for_level(currentLevel);
	SDL_Surface *image = get_fruit_image(fruit);

	//TODO: maybe this offset isn't the same for all fruit. Investigate
	draw_image_coord_offset(image, gameFruit->x, gameFruit->y + 2, -5, 8);
}


//#5 Yang : 3. object renderering
void draw_object_indicator(int currentLevel)
{
	if (currentLevel < 1)
		{
			printf("invalid level number for drawing fruit: %d\naborting\n", currentLevel);
			exit(1);
		}
	if(Multi_flags() == 1) // # 9 Dong : 2P 맵 추가를 위한 수정
	{
		int x = 54 * 16;
		int y = 34 * 16;
		int index = currentLevel > 7 ? 7 : currentLevel;

		for (int i = index; i > 0; i--)
		{
			Object object = random_object();
			SDL_Surface *image = get_object_image(object);

			apply_surface(x - i * 16 * 2, y, image);
		}
	}
	else
	{
		int x = 26 * 16;
		int y = 34 * 16;
		int index = currentLevel > 7 ? 7 : currentLevel;

		for (int i = index; i > 0; i--)
		{
			Object object = random_object();
			SDL_Surface *image = get_object_image(object);

			apply_surface(x - i * 16 * 2, y, image);
		}
	}
}
void draw_object_game (int curruntLevel, GameObject *gameObject)
{
	Object object = gameObject->object;
		SDL_Surface *image = get_object_image(object); //#3 Yang : 6.object 출현 방식 수정

		draw_image_coord_offset(image, gameObject->x, gameObject->y + 2, -5, 8);
}
//
// Pellet renderering
//
//

void draw_pellet_small(Pellet *p)
{
	draw_image_coord(p->image, p->x, p->y);
}

void draw_pellet_power(Pellet *p, bool flashing)
{
	//do this properly
	if (flashing) return;

	draw_image_coord(p->image, p->x, p->y);
}

void draw_small_pellets(PelletHolder *ph)
{
	for (int i = 0; i < NUM_PELLETS; i++)
	{
		Pellet p = ph->pellets[i];

		if (p.type != SmallPellet) continue;
		if (p.eaten) continue;

		apply_surface(p.x * 16, offset + p.y * 16, p.image);
	}
}

void draw_large_pellets(PelletHolder *ph, bool flashing)
{
	//actual tick rate is 10 * (1 / 60), or 10 frames
	//this comes out to 166.666 ms
	int frame = animation_get_frame(167, 2);

	for (int i = 0; i < NUM_PELLETS; i++)
	{
		Pellet p = ph->pellets[i];

		if (p.type != LargePellet) continue;
		if (p.eaten) continue;
		if (flashing && frame == 1) continue;

		apply_surface(p.x * 16, offset + p.y * 16, p.image);
	}
}

//
//
// Pacman renderering
//
//

void draw_pacman(Pacman *pacman, int num)
{
	int frame;

	Direction aniDir;

	if (pacman->movementType == Stuck)
	{
		//if left/ down, he needs full open frame
		//if up/ right, he uses semi-open frame
		aniDir = pacman->lastAttemptedMoveDirection;
		if (aniDir == Left || aniDir == Down)
		{
			frame = 2;
		}
		else
		{
			frame = 1;
		}
	}
	else
	{
		aniDir = pacman->body.curDir;
		frame = animation_get_frame(50, 4);
	}

	int xOffset = pacman->body.xOffset - 4;
	int yOffset = offset + pacman->body.yOffset - 4;

	if(!num){
		if(!pacman->boostOn) {
			draw_image_coord_offset(pacman_ani_image(aniDir, frame), pacman->body.x, pacman->body.y, xOffset, yOffset);
		} else {
			draw_image_coord_offset(pacman_ani_boost_image(aniDir, frame), pacman->body.x, pacman->body.y, xOffset, yOffset);
		}
	}else{
		if(!pacman->boostOn) {
			draw_image_coord_offset(pacman_ani_image2(aniDir, frame), pacman->body.x, pacman->body.y, xOffset, yOffset);
		} else {
			draw_image_coord_offset(pacman_ani_boost_image(aniDir, frame), pacman->body.x, pacman->body.y, xOffset, yOffset);
		}
	}
}

void draw_pacman_static(Pacman *pacman, int num)
{
	int xOffset = pacman->body.xOffset - 4;
	int yOffset = offset + pacman->body.yOffset - 6;

	if(!num) draw_image_coord_offset(pacman_image(), pacman->body.x, pacman->body.y, xOffset, yOffset);
	else draw_image_coord_offset(pacman_image2(), pacman->body.x, pacman->body.y, xOffset, yOffset);
}

void draw_pacman_death(Pacman *pacman, unsigned int dt, int num)
{
	//hangs on first image for 200ms
	//cycles through rest of images at constant rate
	//hangs on "plop" image for a while

	unsigned int hang1 = 200;
	unsigned int perFrame = 140;
	unsigned int hang2 = 200;

	int numFrames = 11;

	SDL_Surface *image;
	if(!num){
		if (dt < hang1)
		{
			image = pacman_death_image(0);
		}
		else if (dt < (hang1 + numFrames * perFrame))
		{
			int i = animation_get_frame_dt(dt - hang1, perFrame, numFrames);

			image = pacman_death_image(i);
		}
		else if (dt < (hang1 + numFrames * perFrame + hang2))
		{
			//draw last frame
			image = pacman_death_image(10);
		}
		else
		{
			//draw nothing
			return;
		}
	}else{
		if (dt < hang1)
		{
			image = pacman_death_image2(0);
		}
		else if (dt < (hang1 + numFrames * perFrame))
		{
			int i = animation_get_frame_dt(dt - hang1, perFrame, numFrames);

			image = pacman_death_image2(i);
		}
		else if (dt < (hang1 + numFrames * perFrame + hang2))
		{
			//draw last frame
			image = pacman_death_image2(10);
		}
		else
		{
			//draw nothing
			return;
		}
	}
	int xOffset = pacman->body.xOffset - 4;
	int yOffset = offset + pacman->body.yOffset - 6;

	draw_image_coord_offset(image, pacman->body.x, pacman->body.y, xOffset, yOffset);
}

void draw_pacman_lives(int numLives1, int numLives2,int flag)
{
	int x1 = 2 * 16;
	int x2;
	if(flag) x2 = 20*16;
	else x2 = 40*16;
	int y = 34 * 16;

	for (int i = 0; i < numLives1; i++)
	{
		apply_surface(x1, y, pacman_life_image());

		x1 += 16 * 2;
	}
	for (int i = 0; i < numLives2; i++)
		{
			apply_surface(x2, y, pacman_life_image2());

			x2 += 16 * 2;
		}
}

//
// Ghost rendering
//

void draw_ghost(Ghost *ghost)
{
	SDL_Surface *image = ghost_image(ghost->ghostType, ghost->body.curDir, 0);

	int x = ghost->body.x;
	int y = ghost->body.y + Y_OFFSET;

	int xOffset = ghost->body.xOffset - 6;
	int yOffset = ghost->body.yOffset - 6;

	draw_image_coord_offset(image, x, y, xOffset, yOffset);
}

bool draw_scared_ghost(Ghost *ghost, unsigned int dt)
{
	//hangs on first image for 200ms
	//cycles through rest of images at constant rate
	//hangs on "plop" image for a while

	unsigned int perFrame = 1000;

	int numFrames = 10;

	SDL_Surface *image;

	if(dt < numFrames * perFrame) {
		if((dt/500) % 2 == 0){
			image = scared_ghost_image(0);
		} else {
			image = scared_ghost_image(1);
		}
	} else {
		return false;
	}

	int x = ghost->body.x;
	int y = ghost->body.y + Y_OFFSET;

	int xOffset = ghost->body.xOffset - 6;
	int yOffset = ghost->body.yOffset - 6;

	draw_image_coord_offset(image, x, y, xOffset, yOffset);
	return true;
}

void draw_eyes(Ghost *ghost) {
	//ghost dead
	SDL_Surface *image = ghost_eye_image(ghost->body.curDir);

	int x = ghost->body.x;
	int y = ghost->body.y + Y_OFFSET;

	int xOffset = ghost->body.xOffset - 6;
	int yOffset = ghost->body.yOffset - 6;

	draw_image_coord_offset(image, x, y, xOffset, yOffset);
}

//
// Points rendering
//

void draw_fruit_pts(GameFruit *gameFruit)
{
	Fruit f = gameFruit->fruit;
	SDL_Surface *image = get_fruit_score_image(f);

	draw_image_coord(image, gameFruit->x, gameFruit->y + 3);
}

void draw_ghost_pts(GameFruit *gameFruit)
{
	Fruit f = gameFruit->fruit;
	SDL_Surface *image = get_fruit_score_image(f);

	draw_image_coord(image, gameFruit->x, gameFruit->y + 3);
}

//
//
// Board rendering
//
//

void draw_board(Board *board)
{
	if(Multi_flags() == 1) // #9 Dong : 2p 맵 연동
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			for (int x = 0; x < 56; x++)
			{
				apply_surface(x * 16, offset + y * 16, (board->boardSquares[x][y]).image);
			}
		}
	}
	else
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			for (int x = 0; x < 28; x++)
			{
				apply_surface(x * 16, offset + y * 16, (board->boardSquares[x][y]).image);
			}
		}
	}
}

void draw_board_flash(Board *board)
{
	int animate = animation_get_frame(250, 2);

	//TODO: make this draw the different colored board instead of just not drawing
	if (animate) return;

	if(Multi_flags() == 1) // #9 Dong : 2p 맵 연동
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			for (int x = 0; x < 56; x++)
			{
				apply_surface(x * 16, offset + y * 16, (board->boardSquares[x][y]).image);
			}
		}
	}
	else
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			for (int x = 0; x < 28; x++)
			{
				apply_surface(x * 16, offset + y * 16, (board->boardSquares[x][y]).image);
			}
		}
	}
}
void draw_help_mode(int *s_c_num) // Lemonwater 5.4 add help, 실제로 help1,2,3 이미지를 구현해주는 함수
{
    SDL_Surface *image;
	switch(*s_c_num)
	{
	case 0:
		image = help1_image();
		apply_surface(10, 8, image);
		break;
	case 1:
		image = help2_image();
		apply_surface(10, 8, image);
		break;
        
	case 2:
		image = help3_image();
		apply_surface(10, 8, image);
		break;
	case 3:
		image = help4_image();
		apply_surface(10, 8, image);
		break;
	case 4:
		image = help5_image();
		apply_surface(10, 8, image);
		break;
	case 5:
		image = help6_image();
		apply_surface(10, 8, image);
		break;
	case 6:
		image = help7_image();
		apply_surface(10, 8, image);
		break;
	case 7:
		image = help8_image();
		apply_surface(10, 8, image);
		break;
	case 8:
		image = help9_image();
		apply_surface(10, 8, image);
		break;
	case 9:
		image = help10_image();
		apply_surface(10, 8, image);
		break;

	}
}

void draw_pause(void) 
{
	SDL_Surface *image;
	image = pause_image();
	apply_surface(100,100,image);
}


void draw_change_keys(SDL_Surface *surface, int key, int x, int y) //lemonwater 5.15 문자에 해당되는 아스키코드 값을 입력해야함.
{
	char string[2];
	string[0] = key; string[1] = '\0';

	if(key>=SDLK_a && key<=SDLK_z) //a-z
	{	
		string[0] = string[0]-32; //화면상 출력은 대문자이므로, 아스키코드 값 32를 빼줍니다.
		draw_text_coord(surface,string,x,y);	
	}


	else if(key==0) //lemonwater 5.16 키입력이 아무것도 입력되지 않는 상태. test용
		draw_text_coord(surface,"NP",x,y);
	

	else if(key>=SDLK_0 && key<=SDLK_9) //0-9
		draw_text_coord(surface, string, x, y);

	else if(key==SDLK_UP) //lemonwater 5.16 기본방향키
		draw_text_coord(surface, "UP", x, y);
	else if(key==SDLK_DOWN) 
		draw_text_coord(surface, "DOWN", x, y);
	else if(key==SDLK_LEFT) 
		draw_text_coord(surface, "LEFT", x, y);
	else if(key==SDLK_RIGHT) 
		draw_text_coord(surface, "RIGHT", x, y);


	else if(key==SDLK_KP0) // lemonwater 5.16 keypad 0 - 9
		draw_text_coord(surface,"KP0",x,y);
	else if(key==SDLK_KP1) 
		draw_text_coord(surface,"KP1",x,y);
	else if(key==SDLK_KP2) 
		draw_text_coord(surface,"KP2",x,y);
	else if(key==SDLK_KP3) 
		draw_text_coord(surface,"KP3",x,y);
	else if(key==SDLK_KP4) 
		draw_text_coord(surface,"KP4",x,y);
	else if(key==SDLK_KP5) 
		draw_text_coord(surface,"KP5",x,y);
	else if(key==SDLK_KP6) 
		draw_text_coord(surface,"KP6",x,y);
	else if(key==SDLK_KP7) 
		draw_text_coord(surface,"KP7",x,y);
	else if(key==SDLK_KP8) 
		draw_text_coord(surface,"KP8",x,y);
	else if(key==SDLK_KP9) 
		draw_text_coord(surface,"KP9",x,y);	


	else if(key==SDLK_COMMA) // lemonwater 5.16 기타문자
		draw_text_coord(surface,"COMMA",x,y);
	else if(key==SDLK_PERIOD) 
		draw_text_coord(surface,"PERIOD",x,y);
	else if(key==SDLK_SLASH) 
		draw_text_coord(surface,"SLASH",x,y);
	else if(key==SDLK_SEMICOLON) 
		draw_text_coord(surface,"SEMICOLON",x,y);
	else if(key==SDLK_QUOTE) 
		draw_text_coord(surface,"QUOTE",x,y);
	else if(key==SDLK_LEFTBRACKET)
		draw_text_coord(surface,"LBRACKET",x,y);
	else if(key==SDLK_RIGHTBRACKET)
		draw_text_coord(surface,"RBRACKET",x,y);
	else if(key==SDLK_MINUS)
		draw_text_coord(surface,"MINUS",x,y);
	else if(key==SDLK_EQUALS)
		draw_text_coord(surface,"EQUAL",x,y);
	else if(key==SDLK_BACKSLASH)
		draw_text_coord(surface,"BACKSLASH",x,y);
	else if(key==SDLK_KP_ENTER)
		draw_text_coord(surface,"ENTER",x,y);
	else 
		draw_text_coord(surface, "INVALID", x,y);
	
}


void draw_settings_mode(int *s_c_num) // Lemonwater 5.4 add settings 5.16 글자 위치 변경. 도움말 추가
{
	set_text_color(WhiteText);

	draw_text_coord(get_screen(), "1.PRESS ENTER", 1, 2);
	draw_text_coord(get_screen(), "2.PRESS THE KEY TO CHANGE", 1, 4);

	draw_text_coord(get_screen(), "1P UP KEY", 4, 8);     draw_change_keys(get_screen(), Player_keys_array1(0) ,18,8); 
	draw_text_coord(get_screen(), "1P DOWN KEY", 4, 10);  draw_change_keys(get_screen(), Player_keys_array1(1) ,18,10); 
	draw_text_coord(get_screen(), "1P LEFT KEY", 4, 12);  draw_change_keys(get_screen(), Player_keys_array1(2) ,18,12); 
	draw_text_coord(get_screen(), "1P RIGHT KEY", 4, 14); draw_change_keys(get_screen(), Player_keys_array1(3) ,18,14); 
	draw_text_coord(get_screen(), "2P UP KEY", 4, 18);    draw_change_keys(get_screen(), Player_keys_array2(0) ,18,18); 
	draw_text_coord(get_screen(), "2P DOWN KEY", 4, 20);  draw_change_keys(get_screen(), Player_keys_array2(1) ,18,20); 
	draw_text_coord(get_screen(), "2P LEFT KEY", 4, 22);  draw_change_keys(get_screen(), Player_keys_array2(2) ,18,22); 
	draw_text_coord(get_screen(), "2P RIGHT KEY", 4, 24); draw_change_keys(get_screen(), Player_keys_array2(3) ,18,24); 
	
	set_text_color(PinkText);
	draw_text_coord(get_screen(), "PRESS BACKSPACE TO MENU", 3, 33);

	switch(*s_c_num)
	{
	case 0:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 8);
		draw_text_coord(get_screen(), "1P UP KEY", 4, 8);
		break;
	case 1:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 10);
		draw_text_coord(get_screen(), "1P DOWN KEY", 4, 10);
		break;
	case 2:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 12);
		draw_text_coord(get_screen(), "1P LEFT KEY", 4, 12);
		break;
	
	case 3:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 14);
		draw_text_coord(get_screen(), "1P RIGHT KEY", 4, 14);
		break;
	
	case 4:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 18);
		draw_text_coord(get_screen(), "2P UP KEY", 4, 18);
		break;
	
	case 5:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 20);
		draw_text_coord(get_screen(), "2P DOWN KEY", 4, 20);
		break;
	case 6:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 22);
		draw_text_coord(get_screen(), "2P LEFT KEY", 4, 22);
		break;
	case 7:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 24);
		draw_text_coord(get_screen(), "2P RIGHT KEY", 4, 24);
		break;
    case 8:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 8);
		draw_text_coord(get_screen(), "1P UP KEY ", 4, 8);
        draw_change_keys(get_screen(), Player_keys_array1(0) ,18,8);
		break;
	case 9:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 10);
		draw_text_coord(get_screen(), "1P DOWN KEY", 4, 10);
		draw_change_keys(get_screen(), Player_keys_array1(1) ,18,10);
		break;
	case 10:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 12);
		draw_text_coord(get_screen(), "1P LEFT KEY", 4, 12);
        draw_change_keys(get_screen(), Player_keys_array1(2) ,18,12);
		break;
	
	case 11:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 14);
		draw_text_coord(get_screen(), "1P RIGHT KEY", 4, 14);
        draw_change_keys(get_screen(), Player_keys_array1(3) ,18,14);
		break;
	
	case 12:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 18);
		draw_text_coord(get_screen(), "2P UP KEY", 4, 18);
        draw_change_keys(get_screen(), Player_keys_array2(0) ,18,18);
		break;
	
	case 13:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 20);
		draw_text_coord(get_screen(), "2P DOWN KEY", 4, 20);
        draw_change_keys(get_screen(), Player_keys_array2(1) ,18,20);
		break;
	case 14:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 22);
		draw_text_coord(get_screen(), "2P LEFT KEY", 4, 22);
        draw_change_keys(get_screen(), Player_keys_array2(2) ,18,22);
		break;
	case 15:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 3, 24);
		draw_text_coord(get_screen(), "2P RIGHT KEY", 4, 24);
        draw_change_keys(get_screen(), Player_keys_array2(3) ,18,24);
		break;
	}
}
/*void draw_ischangekey(int *s_c_num_change)
{
	set_text_color(RedText);
	draw_text_coord(get_screen(), "THAT KEY DUPLICATES ANOTHER KEY.", 1, 26);
	draw_text_coord(get_screen(), "DO YOU CHANGE THEM?", 1, 28);
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), "YES", 15, 28);
	draw_text_coord(get_screen(), "NO", 20, 28);
	if (*s_c_num_change==0) {
		set_text_color(RedText);
		draw_text_coord(get_screen(), "YES", 15, 28);
	}
	else if (*s_c_num_change==1) {
		set_text_color(RedText);
		draw_text_coord(get_screen(), "NO", 20, 28);
	}
}*/




void draw_multi_mode(int *s_c_num) // # 9 Dong : 확장맵 테스트를 위한 메뉴 렌더
{
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), "SCORE MODE", 10, 8);
	draw_text_coord(get_screen(), "TIME ATTACK", 10, 13);
	switch(*s_c_num)
	{
	case 0:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 8, 8);
		draw_text_coord(get_screen(), "SCORE MODE", 10, 8);
		break;
	case 1:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 8, 13);
		draw_text_coord(get_screen(), "TIME ATTACK", 10, 13);
		break;
	}
}

void draw_online_mode(int *s_c_num ,char* tmp)//#19 Kim : 1. 일단 메뉴에서 눌렀을때 들어가서 조작하는 화면 만들어보기
{
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), "MAKE ROOM", 10, 8);
	draw_text_coord(get_screen(), "JOIN ROOM", 10, 13);
	switch(*s_c_num)
	{
	case 0:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 8, 8);
		draw_text_coord(get_screen(), "MAKE ROOM", 10, 8);
		break;
	case 1:
		set_text_color(RedText);
		draw_text_coord(get_screen(), "#", 8, 13);
		draw_text_coord(get_screen(), "JOIN ROOM", 10, 13);
		draw_text_coord(get_screen(), "WRITE SERVER IP", 7, 18);
		set_text_color(WhiteText);
		draw_text_coord(get_screen(), tmp, 7, 23	);
		break;
	}
}
void draw_input_string(const char tmp[],int x,int y)
{// #20 Kim : 1. 편하게 쓰기위해서 매개변수로 메세지 맘대로 할수있게
	// #35 Kim 이거 한 이유는 그냥 앞에 set color 랑 텍스트 써주는거 매번 두개쓰기싫어섬임.
	set_text_color(WhiteText);
	draw_text_coord(get_screen(), tmp, x, y);

}


