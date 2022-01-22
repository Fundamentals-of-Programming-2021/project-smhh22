//besmellah

#pragma once

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define min(x, y) x < y ? x : y
#define max(x, y) x > y ? x : y

//UP RIGHT DOWN LEFT
const int DELTA_X[4] = {0, +1, 0, -1};
const int DELTA_Y[4] = {-1, 0, +1, 0};

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

int WIDTH;
int HEIGHT;

int16_t CELL_WIDTH;
int16_t CELL_HEIGHT;

int GRID_WIDTH;
int GRID_HEIGHT;

int WINDOW_PADDING_UP;
int WINDOW_PADDING_RIGHT;
int WINDOW_PADDING_DOWN;
int WINDOW_PADDING_LEFT;

int CASTLE_SIZE;

const int BORDER_THICKNESS = 3;
const int BAR_THICKNESS = 8;
const int SOLDIER_SIZE = 5;

const int NEUTRAL_INITIAL_SOLDIERS = 100;
const int INITIAL_SOLDIERS = 125;

int TOTAL_SOLDIERS_COUNT;

int NUMBER_OF_PLAYERS; //NUMBER_OF_OPPONENTS + 3. Player 0: The gray one, Player 1: The sea, Player 2: User.

const double FPS = 60;

typedef struct CASTLE CASTLE;
typedef struct CELL CELL;
typedef struct PLAYER PLAYER;
typedef struct DEPLOYED_SOLDIER DEPLOYED_SOLDIER;
typedef struct TUPLE TUPLE;

struct CELL {
	int16_t x1, x2, y1, y2;
	int8_t Border_shown[4]; // UP, RIGHT, DOWN, LEFT
	CASTLE* Castle_ptr;
};

struct CASTLE {
	int x, y; //Lies in which cell?
	int Soldiers_count;
	int to_be_deployed;
	CASTLE* Deployment_dest;
	PLAYER* Player;
};

struct PLAYER {
	uint32_t Color;
	int Potion_enabled;
	int Soldiers_count;
};

struct DEPLOYED_SOLDIER {
	PLAYER* Player;
	CASTLE* Dest;
	int x, y;
	int vx, vy;
	DEPLOYED_SOLDIER *nxt, *prv;
};

struct TUPLE {
	int x1;
	int x2;
	int x3;
	int x4;
};

CELL** GRID;
CASTLE*** CASTLE_PTRS;
PLAYER* Players;

SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

DEPLOYED_SOLDIER *HEAD = NULL;
