#pragma once

#include <stdbool.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "direction.h"
#include "main.h"
#include "fruit.h"
#include "ghost.h"
#include "object.h"

#define NUM_CHAR_IMAGES 26
#define NUM_NUM_IMAGES 10
#define NUM_SPEC_IMAGES 9 // # 13 Dong : 갯수 수정 //Lemonwater 6.3 modify the number of special images


SDL_Surface* double_corner_image(DiagDirection direction);
SDL_Surface* single_corner_image(DiagDirection direction);

SDL_Surface* tleft_image(DiagDirection direction);
SDL_Surface* tright_image(DiagDirection direction);

SDL_Surface* middle_image(Direction direction);
SDL_Surface* hallway_image(Direction direction);

SDL_Surface* pen_corner_image(DiagDirection direction);
SDL_Surface* pen_side_image(Direction direction);
SDL_Surface* pen_gate_image(void);

SDL_Surface* small_pellet_image(void);
SDL_Surface* large_pellet_image(void);

SDL_Surface* pts_white_image(void);
SDL_Surface* pts_peach_image(void);

SDL_Surface* pacman_image(void);
SDL_Surface* pacman_image2(void);
SDL_Surface* pacman_ani_image(Direction dir, int frame);
SDL_Surface* pacman_ani_image2(Direction dir, int frame);
SDL_Surface* pacman_ani_boost_image(Direction dir, int frame);
SDL_Surface* pacman_death_image(int i);
SDL_Surface* pacman_life_image(void);
SDL_Surface* pacman_death_image2(int i);
SDL_Surface* pacman_life_image2(void);

SDL_Surface* ghost_image(GhostType type, Direction dir, int frame);
SDL_Surface* scared_ghost_image(int frame);
SDL_Surface* ghost_eye_image(Direction dir);

SDL_Surface* get_char_image(char c);
SDL_Surface* get_num_image(char c);
SDL_Surface* get_spec_image(char c);

SDL_Surface** get_char_images(void);
SDL_Surface** get_num_images(void);
SDL_Surface** get_spec_images(void);

SDL_Surface* get_fruit_image(Fruit fruit);

//#5 Yang : 3. obeject renderering
SDL_Surface* get_object_image(Object object);

SDL_Surface* get_ghost_score_image(int i);
SDL_Surface* get_fruit_score_image(Fruit fruit);

//Lemonwater 5.7 add help images
SDL_Surface* help1_image(void);
SDL_Surface* help2_image(void);
SDL_Surface* help3_image(void);
SDL_Surface* help4_image(void);
SDL_Surface* help5_image(void);
SDL_Surface* help6_image(void);
SDL_Surface* help7_image(void);
SDL_Surface* help8_image(void);
SDL_Surface* help9_image(void);
SDL_Surface* help10_image(void);


SDL_Surface* pause_image(void);
