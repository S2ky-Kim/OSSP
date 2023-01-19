#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_imageFilter.h>
#include <SDL/SDL_rotozoom.h>

#include "imageloader.h"

#define DIR "images/"

#define PNT_DIR "pts/"

#define MAP_DIR "map/"
#define PEN_DIR "pen/"

#define FRUIT_DIR "fruit/"

//#5 Yang : 3. object renderering
#define OBJECT_DIR "object/"

#define ENTITIES_DIR "entities/"

#define GHOST_DIR "ghosts/"

#define RED_DIR "red/"
#define PINK_DIR "pink/"
#define CYAN_DIR "cyan/"
#define ORANGE_DIR "orange/"

#define EYES_DIR "eyes/"
#define SCARED_DIR "scared/"

#define PAC_DIR "pacman/"
#define PAC_DEATH_DIR "death/"

#define CHAR_DIR "realchar/"

#define LETTERS_DIR "letters/"
#define NUMS_DIR "nums/"
#define SPEC_DIR "special/"

#define HELP_DIR "help/"  //lemonwater 5.8 help폴더 디렉토리 추가
#define PAUSE_DIR "pause/"  //lemonwater 5.20 menu폴더 디렉토리 추가

//loads an image from filename and returns it as an SDL_Surface
SDL_Surface *load_image(const char *filename);

//
//hallway sprites
//
SDL_Surface *double_corner_imgs[4];
SDL_Surface *single_corner_imgs[4];
SDL_Surface *tleft_imgs[4];
SDL_Surface *tright_imgs[4];
SDL_Surface *middle_imgs[4];
SDL_Surface *hallway_imgs[4];

//
//pen sprites
//

SDL_Surface *pen_imgs[4];
SDL_Surface *penSide_imgs[4];
SDL_Surface *penGate;

//
//misc sprites
//

SDL_Surface *smallPellet;
SDL_Surface *largePellet;

SDL_Surface *ptsWhiteImage;
SDL_Surface *ptsPeachImage;

SDL_Surface *fruitPoints[NUM_FRUIT];
SDL_Surface *ghostPoints[4];

//#5 Yang : 3. obeject renderering
SDL_Surface *objectPoints[NUM_OBJECT];
//
//pacman sprites
//
SDL_Surface *pacman;
SDL_Surface *pacman2;
SDL_Surface *pacman3;
SDL_Surface *aniPacman[4][3];
SDL_Surface *aniPacman2[4][3];
SDL_Surface *aniPacmanBoost[4][3];
SDL_Surface *deathPacman[11];
SDL_Surface *deathPacman2[11];
SDL_Surface *pacmanLifeIcon;
SDL_Surface *pacmanLifeIcon2;

//
//ghost sprites
//

//ghosts have 4 colors * 2 images for main animatino
SDL_Surface *ghosts[4][4][2];
//2 images for ghost
SDL_Surface *ghostScared[2];
//4 images for eyes
SDL_Surface *ghostEyes[4];

//
//character/ text sprites
//
SDL_Surface *charImages[NUM_CHAR_IMAGES];
SDL_Surface *numImages[NUM_NUM_IMAGES];
SDL_Surface *specImages[NUM_SPEC_IMAGES];

//
//fruit images
//
SDL_Surface *cherryImage;
SDL_Surface *strawberryImage;
SDL_Surface *peachImage;
SDL_Surface *appleImage;
SDL_Surface *grapesImage;
SDL_Surface *galaxianImage;
SDL_Surface *bellImage;
SDL_Surface *keyImage;


//#5 Yang : 3. object renderering
//object images
SDL_Surface *ghostslowImage;
//#15 Yang : 1.라이프 추가
//Lemonwater Ice object 이미지 추가, image 폴더에 Ice.png
SDL_Surface *lifeImage;
SDL_Surface *godImage;
SDL_Surface *IceImage;
SDL_Surface *ThunderImage;



//
// Lemonwater 5.7 help image 추가
//
SDL_Surface *help1image;
SDL_Surface *help2image;
SDL_Surface *help3image;
SDL_Surface *help4image;
SDL_Surface *help5image;
SDL_Surface *help6image;
SDL_Surface *help7image;
SDL_Surface *help8image;
SDL_Surface *help9image;
SDL_Surface *help10image;



SDL_Surface *pauseimage;


void load_board_images(void);
void load_pacman_images(void);
void load_ghost_images(void);
void load_misc_images(void);
void load_char_images(void);
void load_fruit_images(void);
void load_object_images(void);
void load_help_images(void);
void load_pause_images(void);

void dispose_board_images(void);
void dispose_pacman_images(void);
void dispose_ghost_images(void);
void dispose_misc_images(void);
void dispose_char_images(void);
void dispose_fruit_images(void);
void dispose_object_images(void);
void dispose_help_images(void);
void dispose_pause_images(void);


void load_images(void)
{
	load_board_images();
	load_pacman_images();
	load_ghost_images();
	load_misc_images();
	load_char_images();
	load_fruit_images();
	load_object_images();
	load_help_images(); //lemonwater 5.8 모든 이미지를 로딩할 때 help이미지 10가지도 추가한다.
	load_pause_images();
}

void dispose_images(void)
{
	dispose_board_images();
	dispose_pacman_images();
	dispose_misc_images();
	dispose_char_images();
	dispose_fruit_images();
	dispose_object_images();
	dispose_pause_images(); //lemonwater 5.8 모든 이미지를 소거할 때 help이미지 3가지도 소거한다.
	
}


void load_diags(SDL_Surface *images[4], const char *file)
{
	char dirStr[256];
	const char *extensions[] = {"UL", "UR", "BL", "BR"};

	for (int i = 0; i < 4; i++)
	{
		sprintf(dirStr, "%s%s%s", file, extensions[i], ".png");
		images[i] = load_image(dirStr);
	}
}

void load_dirs(SDL_Surface *images[4], const char *file)
{
	char dirStr[256];
	const char *extensions[] = {"U", "B", "L", "R"};

	for (int i = 0; i < 4; i++)
	{
		sprintf(dirStr, "%s%s%s", file, extensions[i], ".png");
		images[i] = load_image(dirStr);
	}
}

void load_board_images(void)
{
	load_diags(double_corner_imgs, DIR MAP_DIR "doublecorner");
	load_diags(single_corner_imgs, DIR MAP_DIR "singlecorner");
	load_diags(tleft_imgs, DIR MAP_DIR "tleft");
	load_diags(tright_imgs, DIR MAP_DIR "tright");
	load_dirs(middle_imgs, DIR MAP_DIR "middle");
	load_dirs(hallway_imgs, DIR MAP_DIR "hallway");

	load_diags(pen_imgs, DIR MAP_DIR PEN_DIR "pen");
	load_dirs(penSide_imgs, DIR MAP_DIR PEN_DIR "pen");
	penGate = load_image(DIR MAP_DIR PEN_DIR "pengate.png");
}

void dispose_board_images(void)
{
	for (int i = 0; i < 4; i++)
	{
		SDL_FreeSurface(double_corner_imgs[i]);
		SDL_FreeSurface(single_corner_imgs[i]);
		SDL_FreeSurface(tleft_imgs[i]);
		SDL_FreeSurface(tright_imgs[i]);
		SDL_FreeSurface(middle_imgs[i]);
		SDL_FreeSurface(pen_imgs[i]);
		SDL_FreeSurface(penSide_imgs[i]);
	}

	SDL_FreeSurface(penGate);
}

void load_pacman_images(void)
{
	pacman = load_image(DIR ENTITIES_DIR PAC_DIR "pacman.png");
	pacman2 = load_image(DIR ENTITIES_DIR PAC_DIR "pacman2.png");
	pacman3 = load_image(DIR ENTITIES_DIR PAC_DIR "pacman3.png");

	pacmanLifeIcon = load_image(DIR ENTITIES_DIR PAC_DIR "pac_life_icon.png");
	pacmanLifeIcon2 = load_image(DIR ENTITIES_DIR PAC_DIR "pac_life_icon2.png");

	aniPacman[0][0] = load_image(DIR ENTITIES_DIR PAC_DIR "l0.png");
	aniPacman[0][1] = load_image(DIR ENTITIES_DIR PAC_DIR "l1.png");
	aniPacman[0][2] = aniPacman[0][0];

	aniPacman[1][0] = load_image(DIR ENTITIES_DIR PAC_DIR "u0.png");
	aniPacman[1][1] = load_image(DIR ENTITIES_DIR PAC_DIR "u1.png");
	aniPacman[1][2] = aniPacman[1][0];

	aniPacman[2][0] = load_image(DIR ENTITIES_DIR PAC_DIR "r0.png");
	aniPacman[2][1] = load_image(DIR ENTITIES_DIR PAC_DIR "r1.png");
	aniPacman[2][2] = aniPacman[2][0];

	aniPacman[3][0] = load_image(DIR ENTITIES_DIR PAC_DIR "d0.png");
	aniPacman[3][1] = load_image(DIR ENTITIES_DIR PAC_DIR "d1.png");
	aniPacman[3][2] = aniPacman[3][0];

	//2p pacman
	aniPacman2[0][0] = load_image(DIR ENTITIES_DIR PAC_DIR "l03.png");
	aniPacman2[0][1] = load_image(DIR ENTITIES_DIR PAC_DIR "l13.png");
	aniPacman2[0][2] = aniPacman2[0][0];

	aniPacman2[1][0] = load_image(DIR ENTITIES_DIR PAC_DIR "u03.png");
	aniPacman2[1][1] = load_image(DIR ENTITIES_DIR PAC_DIR "u13.png");
	aniPacman2[1][2] = aniPacman2[1][0];

	aniPacman2[2][0] = load_image(DIR ENTITIES_DIR PAC_DIR "r03.png");
	aniPacman2[2][1] = load_image(DIR ENTITIES_DIR PAC_DIR "r13.png");
	aniPacman2[2][2] = aniPacman2[2][0];

	aniPacman2[3][0] = load_image(DIR ENTITIES_DIR PAC_DIR "d03.png");
	aniPacman2[3][1] = load_image(DIR ENTITIES_DIR PAC_DIR "d13.png");
	aniPacman2[3][2] = aniPacman2[3][0];

	//Boost
	aniPacmanBoost[0][0] = load_image(DIR ENTITIES_DIR PAC_DIR "l02.png");
	aniPacmanBoost[0][1] = load_image(DIR ENTITIES_DIR PAC_DIR "l12.png");
	aniPacmanBoost[0][2] = aniPacmanBoost[0][0];

	aniPacmanBoost[1][0] = load_image(DIR ENTITIES_DIR PAC_DIR "u02.png");
	aniPacmanBoost[1][1] = load_image(DIR ENTITIES_DIR PAC_DIR "u12.png");
	aniPacmanBoost[1][2] = aniPacmanBoost[1][0];

	aniPacmanBoost[2][0] = load_image(DIR ENTITIES_DIR PAC_DIR "r02.png");
	aniPacmanBoost[2][1] = load_image(DIR ENTITIES_DIR PAC_DIR "r12.png");
	aniPacmanBoost[2][2] = aniPacmanBoost[2][0];

	aniPacmanBoost[3][0] = load_image(DIR ENTITIES_DIR PAC_DIR "d02.png");
	aniPacmanBoost[3][1] = load_image(DIR ENTITIES_DIR PAC_DIR "d12.png");
	aniPacmanBoost[3][2] = aniPacmanBoost[3][0];


	char dirStr[256];

	for (int i = 0; i < 11; i++)
	{
		sprintf(dirStr, "%s%s%d%s", DIR ENTITIES_DIR PAC_DIR PAC_DEATH_DIR, "death", i, ".png");

		deathPacman[i] = load_image(dirStr);
	}
	for (int i = 0; i < 11; i++)
	{
		sprintf(dirStr, "%s%s%d%s", DIR ENTITIES_DIR PAC_DIR PAC_DEATH_DIR, "death", i, "3.png");

		deathPacman2[i] = load_image(dirStr);
	}
}

void dispose_pacman_images(void)
{
	SDL_FreeSurface(pacman);
	SDL_FreeSurface(pacman2);
	SDL_FreeSurface(pacman3);

	SDL_FreeSurface(pacmanLifeIcon);
	SDL_FreeSurface(pacmanLifeIcon2);

	SDL_FreeSurface(aniPacman[0][0]);
	SDL_FreeSurface(aniPacman[0][1]);

	SDL_FreeSurface(aniPacman[1][0]);
	SDL_FreeSurface(aniPacman[1][1]);

	SDL_FreeSurface(aniPacman[2][0]);
	SDL_FreeSurface(aniPacman[2][1]);

	SDL_FreeSurface(aniPacman[3][0]);
	SDL_FreeSurface(aniPacman[3][1]);

	SDL_FreeSurface(aniPacman2[0][0]);
	SDL_FreeSurface(aniPacman2[0][1]);

	SDL_FreeSurface(aniPacman2[1][0]);
	SDL_FreeSurface(aniPacman2[1][1]);

	SDL_FreeSurface(aniPacman2[2][0]);
	SDL_FreeSurface(aniPacman2[2][1]);

	SDL_FreeSurface(aniPacman2[3][0]);
	SDL_FreeSurface(aniPacman2[3][1]);
	//Boost

	SDL_FreeSurface(aniPacmanBoost[0][0]);
	SDL_FreeSurface(aniPacmanBoost[0][1]);

	SDL_FreeSurface(aniPacmanBoost[1][0]);
	SDL_FreeSurface(aniPacmanBoost[1][1]);

	SDL_FreeSurface(aniPacmanBoost[2][0]);
	SDL_FreeSurface(aniPacmanBoost[2][1]);

	SDL_FreeSurface(aniPacmanBoost[3][0]);
	SDL_FreeSurface(aniPacmanBoost[3][1]);

	for (int i = 0; i < 11; i++)
	{
		SDL_FreeSurface(deathPacman[i]);
		SDL_FreeSurface(deathPacman2[i]);
	}
}

const char *red_dir = DIR ENTITIES_DIR GHOST_DIR RED_DIR;
const char *pink_dir = DIR ENTITIES_DIR GHOST_DIR PINK_DIR;
const char *cyan_dir = DIR ENTITIES_DIR GHOST_DIR CYAN_DIR;
const char *orange_dir = DIR ENTITIES_DIR GHOST_DIR ORANGE_DIR;

const char *get_ghost_dir(GhostType type)
{
	switch (type)
	{
		case Blinky: return red_dir;
		case Inky:   return cyan_dir;
		case Pinky:  return pink_dir;
		case Clyde:  return orange_dir;
	}

	return NULL;
}

void load_ghost_images(void)
{
	char dirStr[256];

	for (int col = 0; col < 4; col++)
	{
		for (int i = 0; i < 2; i++)
		{
			sprintf(dirStr, "%s%s%d%s", get_ghost_dir(col), "u", i, ".png");
			ghosts[col][0][i] = load_image(dirStr);

			sprintf(dirStr, "%s%s%d%s", get_ghost_dir(col), "d", i, ".png");
			ghosts[col][1][i] = load_image(dirStr);

			sprintf(dirStr, "%s%s%d%s", get_ghost_dir(col), "l", i, ".png");
			ghosts[col][2][i] = load_image(dirStr);

			sprintf(dirStr, "%s%s%d%s", get_ghost_dir(col), "r", i, ".png");
			ghosts[col][3][i] = load_image(dirStr);
		}
	}

	ghostScared[0] = load_image(DIR ENTITIES_DIR GHOST_DIR SCARED_DIR "scared0.png");
	ghostScared[1] = load_image(DIR ENTITIES_DIR GHOST_DIR SCARED_DIR "scared1.png");

	ghostEyes[0] = load_image(DIR ENTITIES_DIR GHOST_DIR EYES_DIR "u.png");
	ghostEyes[1] = load_image(DIR ENTITIES_DIR GHOST_DIR EYES_DIR "d.png");
	ghostEyes[2] = load_image(DIR ENTITIES_DIR GHOST_DIR EYES_DIR "l.png");
	ghostEyes[3] = load_image(DIR ENTITIES_DIR GHOST_DIR EYES_DIR "r.png");
}

void dispose_ghost_images(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			SDL_FreeSurface(ghosts[i][j][0]);
			SDL_FreeSurface(ghosts[i][j][1]);
		}
	}

	SDL_FreeSurface(ghostScared[0]);
	SDL_FreeSurface(ghostScared[1]);

	SDL_FreeSurface(ghostEyes[0]);
	SDL_FreeSurface(ghostEyes[1]);
	SDL_FreeSurface(ghostEyes[2]);
	SDL_FreeSurface(ghostEyes[3]);
}

void load_fruit_images(void)
{
	cherryImage     = load_image(DIR FRUIT_DIR "cherry.png");
	strawberryImage = load_image(DIR FRUIT_DIR "strawberry.png");
	peachImage      = load_image(DIR FRUIT_DIR "peach.png");
	appleImage      = load_image(DIR FRUIT_DIR "apple.png");
	grapesImage     = load_image(DIR FRUIT_DIR "grapes.png");
	galaxianImage   = load_image(DIR FRUIT_DIR "galaxian.png");
	bellImage       = load_image(DIR FRUIT_DIR "bell.png");
	keyImage        = load_image(DIR FRUIT_DIR "key.png");
}

void dispose_fruit_images(void)
{
	SDL_FreeSurface(cherryImage);
	SDL_FreeSurface(strawberryImage);
	SDL_FreeSurface(peachImage);
	SDL_FreeSurface(appleImage);
	SDL_FreeSurface(grapesImage);
	SDL_FreeSurface(galaxianImage);
	SDL_FreeSurface(bellImage);
	SDL_FreeSurface(keyImage);
}
//#5 Yang : 3. object renderering
void load_object_images(void)
{
	ghostslowImage = load_image(DIR OBJECT_DIR "ghostslow.png");
	lifeImage = load_image(DIR OBJECT_DIR "heart.png");
	godImage = load_image(DIR OBJECT_DIR "god.png");
	IceImage = load_image(DIR OBJECT_DIR "Ice.png");
	ThunderImage = load_image(DIR OBJECT_DIR "thunder.png");
	
}
void dispose_object_images(void)
{
	SDL_FreeSurface(ghostslowImage);
	SDL_FreeSurface(lifeImage);
	SDL_FreeSurface(godImage);
	SDL_FreeSurface(IceImage);
	SDL_FreeSurface(ThunderImage);
}

void load_misc_images(void)
{
	smallPellet = load_image(DIR "smallpellet.png");
	largePellet = load_image(DIR "largepellet.png");

	ptsWhiteImage = load_image(DIR "ptswhite.png");
	ptsPeachImage = load_image(DIR "ptspeach.png");

	char dirStr[256];

	const char *fruitPntStr[] = {"100", "300", "500", "700", "1000", "2000", "3000", "5000"};
	const char *ghostPntStr[] = {"200", "400", "800", "1600"};

	for (int i = 0; i < NUM_FRUIT; i++)
	{
		sprintf(dirStr, "%s%s%s%s", DIR PNT_DIR, "fruit", fruitPntStr[i], ".png");
		fruitPoints[i] = load_image(dirStr);
	}

	for (int i = 0; i < 4; i++)
	{
		sprintf(dirStr, "%s%s%s%s", DIR PNT_DIR, "ghost", ghostPntStr[i], ".png");
		ghostPoints[i] = load_image(dirStr);
	}
}

void dispose_misc_images(void)
{
	SDL_FreeSurface(smallPellet);
	SDL_FreeSurface(largePellet);

	SDL_FreeSurface(ptsWhiteImage);
	SDL_FreeSurface(ptsPeachImage);

	for (int i = 0; i < NUM_FRUIT; i++)
	{
		SDL_FreeSurface(fruitPoints[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		SDL_FreeSurface(ghostPoints[i]);
	}
}

void load_char_images(void)
{
	char dirStr[256];

	for (int i = 0; i < 26; i++)
	{
		char c = 'a';
		sprintf(dirStr, "%s%c%s", DIR CHAR_DIR LETTERS_DIR, (char) (c +i), ".png");

		charImages[i] = load_image(dirStr);
	}

	for (int i = 0; i < 10; i++)
	{
		char c = '0';
		sprintf(dirStr, "%s%c%s", DIR CHAR_DIR NUMS_DIR, (char) (c +i), ".png");

		numImages[i] = load_image(dirStr);
	}

	specImages[0] = load_image(DIR CHAR_DIR SPEC_DIR "space.png");
	specImages[1] = load_image(DIR CHAR_DIR SPEC_DIR "dot.png");
	specImages[2] = load_image(DIR CHAR_DIR SPEC_DIR "dash.png");
	specImages[3] = load_image(DIR CHAR_DIR SPEC_DIR "copyright.png");
	specImages[4] = load_image(DIR CHAR_DIR SPEC_DIR "exclamation.png");
	specImages[5] = load_image(DIR CHAR_DIR SPEC_DIR "forwardslash.png");
	specImages[6] = load_image(DIR CHAR_DIR SPEC_DIR "speechmark.png");
	specImages[7] = load_image(DIR CHAR_DIR SPEC_DIR "pacmanarrow.png"); // #13 Dong : 메뉴화면 선택 화살표 모양 추가
	specImages[8] = load_image(DIR CHAR_DIR SPEC_DIR "question.png"); //Lemonwater 6.3 add a new character: '?'
}

void dispose_char_images(void)
{
	for (int i = 0; i < 26; i++)
	{
		SDL_FreeSurface(charImages[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		SDL_FreeSurface(numImages[i]);
	}

	SDL_FreeSurface(specImages[0]);
	SDL_FreeSurface(specImages[1]);
	SDL_FreeSurface(specImages[2]);
	SDL_FreeSurface(specImages[3]);
	SDL_FreeSurface(specImages[4]);
	SDL_FreeSurface(specImages[5]);
	SDL_FreeSurface(specImages[6]);
	SDL_FreeSurface(specImages[7]); // # 13 Dong : 메뉴화면 선택 화살표모양 추가
	SDL_FreeSurface(specImages[8]); //Lemonwater 6.3 add a new character: '?'
}


// Lemonwater 5.7 add help images
SDL_Surface* help1_image(void) {return help1image;}
SDL_Surface* help2_image(void) {return help2image;}
SDL_Surface* help3_image(void) {return help3image;}
SDL_Surface* help4_image(void) {return help4image;}
SDL_Surface* help5_image(void) {return help5image;}
SDL_Surface* help6_image(void) {return help6image;}
SDL_Surface* help7_image(void) {return help7image;}
SDL_Surface* help8_image(void) {return help8image;}
SDL_Surface* help9_image(void) {return help9image;}
SDL_Surface* help10_image(void) {return help10image;}

//lemonwater 5.20 add pause image
SDL_Surface* pause_image(void)
{
    return pauseimage;
}



// Lemonwater 5.7 add help images
void load_help_images(void)
{
    help1image = load_image(DIR HELP_DIR "help1.png");
    help2image = load_image(DIR HELP_DIR "help2.png");
    help3image = load_image(DIR HELP_DIR "help3.png");
	help4image = load_image(DIR HELP_DIR "help4.png");
    help5image = load_image(DIR HELP_DIR "help5.png");
    help6image = load_image(DIR HELP_DIR "help6.png");
	help7image = load_image(DIR HELP_DIR "help7.png");
    help8image = load_image(DIR HELP_DIR "help8.png");
	help9image = load_image(DIR HELP_DIR "help9.png");
	help10image = load_image(DIR HELP_DIR "help10.png");
    
}
void dispose_help_images(void)
{
    SDL_FreeSurface(help1image);
    SDL_FreeSurface(help2image);
    SDL_FreeSurface(help3image);
	SDL_FreeSurface(help4image);
    SDL_FreeSurface(help5image);
    SDL_FreeSurface(help6image);
	SDL_FreeSurface(help7image);
    SDL_FreeSurface(help8image);
	SDL_FreeSurface(help9image);
	SDL_FreeSurface(help10image);

}

//lemonwater 5.20 add pause image

void load_pause_images(void)
{
	pauseimage = load_image(DIR PAUSE_DIR "pause.png");
}
void dispose_pause_images(void)
{
    SDL_FreeSurface(pauseimage);
}




SDL_Surface *load_image(const char *filename)
{
	printf("loading image: %s\n", filename);
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image using SDL_image
	loadedImage = IMG_Load(filename);

	//If the image loaded
	if(loadedImage != NULL)
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	}
	else
	{
		printf("Error opening image %s\n", filename);
		printf("Aborting.\n");
		exit(1);
	}

	//Return the optimized image
	return optimizedImage;
}

SDL_Surface* get_char_image(char c)
{
	if ('A' <= c && c <= 'Z') return charImages[c - 'A'];
	else return NULL;
}

SDL_Surface** get_char_images(void)
{
	return charImages;
}

SDL_Surface *get_num_image(char c)
{
	if ('0' <= c && c <= '9') return numImages[c - '0'];
	else return NULL;
}

SDL_Surface** get_num_images(void)
{
	return numImages;
}

SDL_Surface* get_spec_image(char c)
{
	switch (c)
	{
		case ' ': return specImages[0];
		case '.': return specImages[1];
		case '-': return specImages[2];
		case '@': return specImages[3];
		case '!': return specImages[4];
		case '/': return specImages[5];
		case '"': return specImages[6];
		case '#': return specImages[7]; // #13 Dong : 메뉴화면 화살표 추까
		case '?': return specImages[8]; // Lemonwater 6.3 add a new character: '?'
	}

	return NULL;
}

SDL_Surface** get_spec_images(void)
{
	return specImages;
}

SDL_Surface* double_corner_image(DiagDirection direction)
{
	return double_corner_imgs[direction];
}

SDL_Surface* single_corner_image(DiagDirection direction)
{
	return single_corner_imgs[direction];
}

SDL_Surface* middle_image(Direction direction)
{
	return middle_imgs[direction];
}

SDL_Surface* hallway_image(Direction direction)
{
	return hallway_imgs[direction];
}

SDL_Surface* tleft_image(DiagDirection direction)
{
	return tleft_imgs[direction];
}

SDL_Surface* tright_image(DiagDirection direction)
{
	return tright_imgs[direction];
}

SDL_Surface* pen_corner_image(DiagDirection direction)
{
	return pen_imgs[direction];
}

SDL_Surface* pen_side_image(Direction direction)
{
	return penSide_imgs[direction];
}

SDL_Surface* pen_gate_image(void)
{
	return penGate;
}

SDL_Surface* small_pellet_image(void)
{
	return smallPellet;
}

SDL_Surface* large_pellet_image(void)
{
	return largePellet;
}

SDL_Surface* pts_white_image(void)
{
	return ptsWhiteImage;
}

SDL_Surface* pts_peach_image(void)
{
	return ptsPeachImage;
}

SDL_Surface* pacman_image(void)
{
	return pacman;
}
SDL_Surface* pacman_image2(void)
{
	return pacman3;
}

SDL_Surface *pacman_ani_image(Direction dir, int frame)
{
	if (frame < 0 || frame > 4)
	{
		printf("invalid pacman frame: %d\n", frame);
		printf("aborting\n");
		exit(1);
	}

	if (frame == 0) return pacman;

	switch(dir)
	{
		case Left:  return aniPacman[0][frame - 1];
		case Up:    return aniPacman[1][frame - 1];
		case Right: return aniPacman[2][frame - 1];
		case Down:  return aniPacman[3][frame - 1];
	}

	printf("incorrect enum value\naborting\n");
	exit(1);
}
SDL_Surface *pacman_ani_image2(Direction dir, int frame)
{
	if (frame < 0 || frame > 4)
	{
		printf("invalid pacman frame: %d\n", frame);
		printf("aborting\n");
		exit(1);
	}

	if (frame == 0) return pacman;

	switch(dir)
	{
		case Left:  return aniPacman2[0][frame - 1];
		case Up:    return aniPacman2[1][frame - 1];
		case Right: return aniPacman2[2][frame - 1];
		case Down:  return aniPacman2[3][frame - 1];
	}

	printf("incorrect enum value\naborting\n");
	exit(1);
}

SDL_Surface *pacman_ani_boost_image(Direction dir, int frame)
{
	if (frame < 0 || frame > 4)
	{
		printf("invalid pacman frame: %d\n", frame);
		printf("aborting\n");
		exit(1);
	}

	if (frame == 0) return pacman2;

	switch(dir)
	{
		case Left:  return aniPacmanBoost[0][frame - 1];
		case Up:    return aniPacmanBoost[1][frame - 1];
		case Right: return aniPacmanBoost[2][frame - 1];
		case Down:  return aniPacmanBoost[3][frame - 1];
	}

	printf("incorrect enum value\naborting\n");
	exit(1);
}

SDL_Surface* pacman_death_image(int i)
{
	return deathPacman[i];
}
SDL_Surface* pacman_death_image2(int i)
{
	return deathPacman2[i];
}

SDL_Surface* pacman_life_image(void)
{
	return pacmanLifeIcon;
}
SDL_Surface* pacman_life_image2(void)
{
	return pacmanLifeIcon2;
}
SDL_Surface* ghost_image(GhostType type, Direction dir, int frame)
{
	if (frame < 0 || frame > 1)
	{
		printf("invalid ghost frame: %d\n", frame);
		printf("aborting\n");
		exit(1);
	}

	if (dir < 0 || dir > 4)
	{
		printf("invalid ghost direction: %d\n", dir);
		printf("aborting\n");
		exit(1);
	}

	if (frame < 0 || frame > 1)
	{
		printf("invalid ghost frame: %d\n", frame);
		printf("aborting\n");
		exit(1);
	}

	return ghosts[type][dir][frame];
}

SDL_Surface* scared_ghost_image(int frame)
{
	if (frame < 0 || frame > 1)
	{
		printf("invalid scared ghost frame: %d\n", frame);
		printf("aborting\n");
		exit(1);
	}

	return ghostScared[frame];
}

SDL_Surface* ghost_eye_image(Direction dir)
{
	if (dir < 0 || dir > 4)
	{
		printf("invalid ghost eye direction: %d\n", dir);
		printf("aborting\n");
		exit(1);
	}

	return ghostEyes[dir];
}

SDL_Surface* get_fruit_image(Fruit fruit)
{
	switch (fruit)
	{
		case Cherry:     return cherryImage;
		case Strawberry: return strawberryImage;
		case Peach:      return peachImage;
		case Apple:      return appleImage;
		case Grapes:     return grapesImage;
		case Galaxian:   return galaxianImage;
		case Bell:       return bellImage;
		case Key:        return keyImage;
	}

	printf("incorrect enum value\naborting\n");
	exit(1);
}

SDL_Surface* get_object_image(Object object)
{
	switch (object)
	{
		case Ghostslow:     return ghostslowImage;
		case Life: 		   return lifeImage; //#15 Yang : 1.생명추가 object 추가
		case God: 				return godImage; //#26 Yang : 1.godmode
		case Ice:			return IceImage;
		case Thunder:		return ThunderImage;
	}

	printf("incorrect enum value\naborting\n");
	exit(1);
}
SDL_Surface* get_fruit_score_image(Fruit fruit)
{
	switch (fruit)
	{
		case Cherry:     return fruitPoints[0];
		case Strawberry: return fruitPoints[1];
		case Peach:      return fruitPoints[2];
		case Apple:      return fruitPoints[3];
		case Grapes:     return fruitPoints[4];
		case Galaxian:   return fruitPoints[5];
		case Bell:       return fruitPoints[6];
		case Key:        return fruitPoints[7];
	}

	printf("incorrect fruitscore enum value\naborting\n");
	exit(1);
}

SDL_Surface* get_ghost_score_image(int i)
{
	if (i < 0 || i > 3)
	{
		printf("incorrect ghost score num: %d\nAborting\n", i);
		exit(1);
	}

	return ghostPoints[i];
}

