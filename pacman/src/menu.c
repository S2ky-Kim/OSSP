#include "menu.h"
#include "stdlib.h"
#include <stdbool.h>

#include <SDL/SDL_keysym.h>

#include "ghost.h"
#include "main.h"
#include "renderer.h"
#include "server.h"
#include "client.h"
#include "sound.h"
#include "input.h"

//time till ghost-rows start appearing
#define GHOST_START 500

//time between each ghost-row appearance
#define GHOST_BETWEEN 500
static char tmp[100]={"0.0.0.0"};
static int index_num=0;
static int s_c_num = 0;
//static int s_c_num_change=0;

static void draw_vanity_screen(MenuSystem *menuSystem);
static void draw_info_screen(void);
static void draw_ghost_line(GhostDisplayRow *row, int y, unsigned int dt);
static void draw_player_info(void);

static GhostDisplayRow enemyRows[4] = {
		{Blinky, "-SHADOW",  "\"BLINKY\"", RedText},
		{Pinky,  "-SPEEDY",  "\"PINKY\"",  PinkText},
		{Inky,   "-BASHFUL", "\"INKY\"",   CyanText},
		{Clyde,  "-POKEY",   "\"CLYDE\"",  OrangeText}
};

void menu_init(MenuSystem *menuSystem)
{
	menuSystem->action = Nothing;
	menuSystem->ticksSinceModeChange = SDL_GetTicks();
	menuSystem->playMode=Single;
}
// #8 Kim : 3. 메뉴 만들기
// int 반환 하도록 함
//  메뉴에서  key up하면 -1  ,down 하면 1 . 아무것도 아니면 0
int menu_tick(MenuSystem *menuSystem)
{
	bool startNew = key_released(SDLK_KP_ENTER) || key_released(SDLK_RETURN);
	//#19 Kim : 2. 엔터 누르면 keyHeld 라서 다음 장면에서도 엔터가 적용되어서 바로 넘어가버리는 버그 잡기위해 released 로 바꿈

	if (startNew)
	{
		if (5000>(SDL_GetTicks() - menuSystem->ticksSinceModeChange))//#35 Kim : 이부분 설명 하자면
			menuSystem->ticksSinceModeChange=SDL_GetTicks()-5000;//  현재의틱 하고 애가 들어갈떄의 틱하고 비교해서
		
		else if(menuSystem->playMode==Online)						//시간이 얼마나 지났는가 확인하는건데 이게 5000미만일 떄 엔터를 눌르면 올려주는거임
			menuSystem->action = GoToJoin;// #19 Kim : 1. 여기서 저게 온라인게임으로 되미녀 엑션 바뀌
		else if (menuSystem -> playMode == Multi)
			menuSystem->action = GoToMulti;		
		
		else if (menuSystem -> playMode == Help) //Lemonwater 5.4 add 'help'. 위에 startNew가 참이면 tick값을 받아 game.h의 playMode가 Help인 상태일 시 menuSystem->action에 GoToHelp를 대입
			menuSystem->action = GoToHelp;
        else if (menuSystem -> playMode == Settings) //Lemonwater 5.4 add 'settings'
			menuSystem->action = GoToSettings;
		
		else
			menuSystem->action = GoToGame;
		return 0;
	}
	// #13 Kim : 1 Key held로 하면 계속 눌린거로 되서 released를 사용
	if (key_released(SDLK_UP))
		return -1;
	else if(key_released(SDLK_DOWN))
		return 1;
	else
		return 0;
}

void menu_render(MenuSystem *menuSystem)
{
	if (num_credits() == 0) draw_vanity_screen(menuSystem);
	else draw_info_screen();
}

static void draw_vanity_screen(MenuSystem *menuSystem)
{
	unsigned int dt = SDL_GetTicks() - menuSystem->ticksSinceModeChange;
	play_sound(LobbySound); // Lemonwater 메인 로비 음악 구현. 참고
	draw_player_info();
	draw_vanity_charnickname();

	for (int i = 0; i < 4; i++)
	{
		unsigned int current = GHOST_START + i * GHOST_BETWEEN;
		if (dt < current) break;

		GhostDisplayRow r = enemyRows[i];
		draw_ghost_line(&r, 7 + 3 * i, dt - current);
	}
	//#13 Kim : 일단 이부분좀 빠르게 지바꿔놓을까 생각중
	//if (dt > 3000) draw_vanity_pellet_info(false);
	if(dt>3000)	draw_playMode(menuSystem->playMode);
	if (dt > 4000) 	draw_vanity_corporate_info();
	if (dt > 5000) 	draw_vanity_animation(dt - 5000);


}

int getKey(void)// #19 Kim : 1. 여기서 키값 받아서 와따가따리 
//lemonwater 5.16 키값을 여기서 다 받아줍니다. 따라서 받고싶은 키가 있다면 여기서 설정해줍니다.
{
	for(int i = 48 ; i <=57 ; i ++) //lemonwater 5.10 ip주소 받기
	{
		if(key_released(i))
			return i;
	}

	for(int i = 97 ; i <=122 ; i ++) //lemonwater 5.10 알파벳. 대문자는 생략.
	{
		if(key_released(i))
			return i;
	}

	if(key_released(SDLK_KP0)) //lemonwater 5.16 keypad 0 - 10
		return SDLK_KP0;
	else if(key_released(SDLK_KP1)) 
		return SDLK_KP1;
	else if(key_released(SDLK_KP2)) 
		return SDLK_KP2;
	else if(key_released(SDLK_KP3)) 
		return SDLK_KP3;
	else if(key_released(SDLK_KP4)) 
		return SDLK_KP4;
	else if(key_released(SDLK_KP5)) 
		return SDLK_KP5;
	else if(key_released(SDLK_KP6)) 
		return SDLK_KP6;
	else if(key_released(SDLK_KP7)) 
		return SDLK_KP7;
	else if(key_released(SDLK_KP8)) 
		return SDLK_KP8;
	else if(key_released(SDLK_KP9)) 
		return SDLK_KP9;
	

	else if(key_released(SDLK_PERIOD)) //lemonwater 5.16 기타 입력키
		return '.';
	else if(key_released(SDLK_COMMA))
		return ',';
	else if(key_released(SDLK_SLASH))
		return '/';
	else if(key_released(SDLK_QUOTE))
		return '\'';
	else if(key_released(SDLK_LEFTBRACKET))
		return '[';
	else if(key_released(SDLK_RIGHTBRACKET))
		return ']';
	else if(key_released(SDLK_SEMICOLON))
		return ';';
	else if(key_released(SDLK_BACKSLASH))
		return '\\';
	else if(key_released(SDLK_EQUALS))
		return '=';
	else if(key_released(SDLK_MINUS))
		return '-';


	else if(key_released(SDLK_UP)) //방향키
		return SDLK_UP;
	else if(key_released(SDLK_DOWN))
		return SDLK_DOWN;
        else if(key_released(SDLK_LEFT))
		return SDLK_LEFT;
	else if(key_released(SDLK_RIGHT))
		return SDLK_RIGHT;


	else if(key_released(SDLK_KP_ENTER)||key_released(SDLK_RETURN))
		return SDLK_KP_ENTER;// #19 Kim : 2. 엔터가 아니라 SDLK_RETURN 인듯. 엔터치면 ㅇㅅㅇ
	else if(key_released(SDLK_BACKSPACE))//#25 ip 칠때 지워지도록.
		return SDLK_BACKSPACE;
	else	
		return 0;
}



int multi_mode_render(MenuSystem *menuSystem)// # 9 Dong : 확장맵 테스트를 위한 추가
{
	int get= getKey();

	//if(menuSystem->action == ScoreMode)
	
		menuSystem->playMode = Multi;
		return 2;
	
	/*else if(menuSystem->action == TimeAttackMode)
	{
		menuSystem->playMode = Multi_TA;
		return 3;
	}

	if(get==SDLK_UP&&s_c_num==1)
	{
		s_c_num = 0;
	}
	else if(get==SDLK_DOWN&&s_c_num==0)
	{
		s_c_num = 1;
	}
	else if(get == SDLK_KP_ENTER)
	{
		if(s_c_num == 0) // # 9 Dong : 2. 작은 맵
		{
			menuSystem->action=ScoreMode;
		}
		else if(s_c_num == 1) // # 9 Dong : 2. 큰 맵
		{
			menuSystem->action=TimeAttackMode;
		}
	}
	draw_multi_mode(&s_c_num);
	return 1;*/
}

int online_mode_render(MenuSystem *menuSystem)// #19 Kim : 2. 여기서 그려줌
{
	int get= getKey();
	if(menuSystem->action==WaitClient)
	{
		makeServer();
		menuSystem->action=GoToGame;
		menuSystem->playMode=Online_Server;// #12 Kim : 2. 잠시 테스트용
		return WaitClient;
	}
	else if(menuSystem->action==JoinServer)
	{
		connectServer(tmp);
		menuSystem->action = GoToGame;
		menuSystem->playMode = Online_Client;//#25 클라이언트쪽 접속하는 코드 추
		return JoinServer;
	}
	// 정리 Kim : 코드정리함
	if(s_c_num==0)
	{//make room 부분일 때
		if(get==SDLK_DOWN)s_c_num++;
		else if(get==SDLK_KP_ENTER)
		{
			draw_input_string("WAITING CLIENT",4,15);// #19 Kim : 2. waiting client 그려줌 이름을 맞게 바꿔줌
			menuSystem->action=WaitClient;
			return 0;
		}
		else if(get==SDLK_BACKSPACE)//#35 makeRoom 에서 백스페이스 누를시에는 메인메뉴로감
		{
			menuSystem->action = Nothing;
			return ReturnMenu;
		}

	}
	else if(s_c_num==1)
	{//Join room 부분일 때임
		if(get==SDLK_UP)	s_c_num--;
		else if((get>=48&&get<=57) ||get==SDLK_PERIOD) //#25 닷 찍으면 문자열 들어가도록.
			tmp[index_num++] = (char)get;
		else if(get == SDLK_BACKSPACE)//# 35 백스페이스 적용 되게 했음
		{if(index_num!=0)tmp[--index_num]='\0';}
		else if(get==SDLK_KP_ENTER)
		{
			draw_input_string("CONNECT SERVER",4,15);
			menuSystem->action = JoinServer;
			return 0;
		}
	}
	draw_online_mode(&s_c_num,tmp);
	return 1;
}
// Lemonwater 5.7 add help images
int help_render(MenuSystem *menuSystem)
{
    int get=getKey(); //lemonwater 5.8 키 입력 받기
    
	if(get==SDLK_BACKSPACE)//lemonwater 5.8 help1, help2, help3 어디에서든 backspace받을 시 main menu로 돌아간다.
		{	
			s_c_num = 0; //lemonwater 5.17 초기화
			menuSystem->action = Nothing;
			return ReturnMenu;
		}


	//lemonwater 5.7 s_c_num은 원래 0, 현재 help1창
	
	if(get==SDLK_RIGHT && (s_c_num >=0 && s_c_num <=8)) s_c_num += 1;
	else if (get==SDLK_LEFT && (s_c_num >=1 && s_c_num <=9)) s_c_num -=1;

    draw_help_mode(&s_c_num);
    return 0;
}

//
//lemonwater key_setting창

int settings_render(MenuSystem *menuSystem)
{
	int get= getKey();//lemonwater 5.16 프로그램이 무한히 반복되면서 키값을 받습니다. 이 때, 아무것도 눌러지지 않은 상태는 0입니다.
	
	if(get==SDLK_BACKSPACE) //lemonwater 5.8 메인메뉴로 돌아가기
		{
			s_c_num = 0; //lemonwater 5.17 초기화
			menuSystem->action = Nothing;
			return ReturnMenu;
		}


	switch(get) {
            case SDLK_DOWN:
                    if (s_c_num>=0 && s_c_num<7) {s_c_num=s_c_num+1;}
		    else if (s_c_num>=8 && s_c_num<16) {get_Change_Key(get,s_c_num);}
		//lemonwater 5.16 위아래 방향키가 이미 조건으로 쓰이고 있어서, 키 입력상태를 나눠주어 따로 설정해줍니다.
		 
            break;
            case SDLK_UP:
                    if (s_c_num>=1 && s_c_num<8) {s_c_num=s_c_num-1;}
		    else if (s_c_num>=8 && s_c_num<16) {get_Change_Key(get,s_c_num);}
		//lemonwater 5.16 위아래 방향키가 이미 조건으로 쓰이고 있어서, 키 입력상태를 나눠주어 따로 설정해줍니다.
		    
            break;
            case SDLK_KP_ENTER: //Lemonwater 5.10 if you press 'enter', then you can change the direction keys
            if (s_c_num>=0 && s_c_num<8)
			s_c_num=s_c_num+8;
						//lemonwater 5.13 enter쳐서 돌아오기
        	else if (s_c_num>=8 && s_c_num<16) 
			{
			s_c_num = s_c_num-8;
			}
			break;
			/*case SDLK_RIGHT:
			if (s_c_num_change==0) s_c_num_change=1;
			else if (s_c_num_change==1) s_c_num_change=2;
			break;
			case SDLK_LEFT:
			if (s_c_num_change==0) s_c_num_change=1;
			else if (s_c_num_change==1) s_c_num_change=2;*/
	    default : //lemonwater 5.16 나머지 키가 입력되는 경우를 의미합니다.
		get_Change_Key(get,s_c_num); //lemonwater 5.16 키를 바꿔줍니다.
		break;
        }

	draw_settings_mode(&s_c_num);

	return 0;
}



//}
static void draw_info_screen(void)
{
	draw_player_info();
	draw_instrc_info();
	draw_instrc_corporate_info();

}

static void draw_player_info(void)
{
	draw_common_oneup(false, 0);
	draw_common_twoup(false, 0,0);
	draw_common_highscore(0);

	draw_credits(num_credits());
}

static void draw_ghost_line(GhostDisplayRow *row,  int y, unsigned int dt)
{
	bool drawDescription = dt > 1000;
	bool drawName = dt > 1500;

	draw_vanity_ghostline(row, y, drawDescription, drawName);
}
