//besmellah
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define min(x, y) x < y ? x : y
#define max(x, y) x > y ? x : y

/* TO: DO
 * 1: Grid Size: 12 * P ?!
 * 2: Struct for each cell																	DONE
 * 	2.1: For each border determine that is this border showed?								DONE
 * 	`2.2: After making struct for each castle, give a pointer to the castle for the cell.	DONE
 * 3: 2D Array for grid Cells.
 * 4: Struct for each castle																DONE
 * 	4.1: Implement color.
 * 	`4.2: Pointer to a Player.
 * 5: Struct for each Player.
 */

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

int TOTAL_SOLDIERS_COUNT;

int NUMBER_OF_PLAYERS; //NUMBER_OF_OPPONENTS + 2. USER is player 1 & the gray one is player 2.

const int FPS = 60;

typedef struct CASTLE CASTLE;
typedef struct CELL CELL;
typedef struct PLAYER PLAYER;
typedef struct DEPLOYED_SOLDIER DEPLOYED_SOLDIER;

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

CELL** GRID;
CASTLE*** CASTLE_PTRS;
PLAYER* Players;

SDL_Window* WINDOW;
SDL_Renderer* RENDERER;

DEPLOYED_SOLDIER *HEAD = NULL;
