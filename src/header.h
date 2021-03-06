//besmellah

#pragma once

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

//UP RIGHT DOWN LEFT
const int DELTA_X[4] = {0, +1, 0, -1};
const int DELTA_Y[4] = {-1, 0, +1, 0};

const float SOLDIERS_SPEED = 6;
const float DEPLOYMENT_RATE = 20;
const float PRODUCTION_RATE = 5;

const int SCREEN_WIDTH = 1240;
const int SCREEN_HEIGHT = 640;

int GRID_WIDTH;
int GRID_HEIGHT;

const int WINDOW_PADDING_UP = SCREEN_HEIGHT / 5;
const int WINDOW_PADDING_RIGHT = SCREEN_WIDTH / 15;
const int WINDOW_PADDING_DOWN = SCREEN_HEIGHT / 10;
const int WINDOW_PADDING_LEFT = SCREEN_WIDTH / 15;

int WIDTH = SCREEN_WIDTH - WINDOW_PADDING_RIGHT - WINDOW_PADDING_LEFT;
int HEIGHT = SCREEN_HEIGHT - WINDOW_PADDING_UP - WINDOW_PADDING_DOWN;

int16_t CELL_WIDTH;
int16_t CELL_HEIGHT;

int CASTLE_SIZE;

const int BORDER_THICKNESS = 3;
const int BAR_THICKNESS = 8;
const int SOLDIER_SIZE = 5;

const int NEUTRAL_INITIAL_SOLDIERS = 100;
const int INITIAL_SOLDIERS = 125;

const int MAX_PRODUCTIVE_SOLDIERS = 120;

int TOTAL_SOLDIERS_COUNT;

int NUMBER_OF_PLAYERS; //NUMBER_OF_OPPONENTS + 3. Player 0: The gray one, Player 1: The sea, Player 2: User.

double FPS = 30;

typedef enum Game_mode {START, MENU, LEADERBOARD, CHOOSEMAP, RANDOMMAP, GAME, PAUSE, EXIT} Game_mode;
typedef enum Game_state {NA, WIN, LOSE} Game_state;
typedef struct CASTLE CASTLE;
typedef struct CELL CELL;
typedef struct PLAYER PLAYER;
typedef struct DEPLOYED_SOLDIER DEPLOYED_SOLDIER;
typedef struct TUPLE TUPLE;

struct CELL {
	int16_t x1, x2, y1, y2;
	int8_t Border_shown[4]; // UP, RIGHT, DOWN, LEFT
	int Castle_x;
	int Castle_y;
	CASTLE* Castle_ptr;
};

struct CASTLE {
	int x, y; //Lies in which cell?
	int Soldiers_count;
	int to_be_deployed;
	int Deployment_dest_x;
	int Deployment_dest_y;
	int last_deploy;
	int last_production;
	PLAYER* Deployer;
	PLAYER* Player;
};

struct PLAYER {
	uint32_t Color;
	int Potion_enabled;
	int Potion_start;
	int Soldiers_count;
};

struct DEPLOYED_SOLDIER {
	PLAYER* Player;
	CASTLE* Dest;
	float x, y;
	float vx, vy;
	DEPLOYED_SOLDIER *nxt, *prv;
};

struct TUPLE {
	int x1;
	int x2;
	int x3;
	int x4;
};

CELL** GRID;
int** isCandid;
CASTLE*** CASTLE_PTRS;
PLAYER* Players;
TUPLE* Candids;
int Candidcnt;

SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

DEPLOYED_SOLDIER *HEAD = NULL;

Game_mode MODE = START;
Game_state STATE = NA;

CASTLE* Chosen = NULL;

int collision_table[1080][720];

const float inf = 2e9;

char username[100];
int score;

TTF_Font *proFontWindows;

int shown_map = 0;

char** LEADERBOARDSTRS;
int* LEADERBOARDA;
int LEADERBOARDCNT;

int hasbeensaved = 0;

const char potionstrs[4][3] = {"S1", "S3", "C1", "C4"};
const int effectivetime[4] = {20, 5, 10, 5};
int enabledpotion = -1;
int shownpotion = -1;
int xpotion = 0;
int ypotion = 0;
