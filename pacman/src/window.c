#include "window.h"

static SDL_Surface *screen;

bool init_window(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

	if (screen == NULL)
	{
		return false;
	}

	SDL_WM_SetCaption(title, NULL);

	return true;
}

void dispose_window(void)
{
	SDL_FreeSurface(screen);
}

SDL_Surface *get_screen(void)
{
	return screen;
}

void clear_screen(int r, int g, int b, int a)
{
	Uint32 col = SDL_MapRGBA(screen->format, r, g, b, a);

	SDL_FillRect(screen, NULL, col);
}

void apply_surface(int x, int y, SDL_Surface* source) //lemonwater 0605 게임 플레이시 맵과 펠렛들 크기 키우기
{
	SDL_Rect offset;

	offset.x = 2*x;
	offset.y = 2*y;

	SDL_BlitSurface(source, NULL, screen, &offset);
}

void flip_screen(void)
{
	SDL_Flip(screen);
}
