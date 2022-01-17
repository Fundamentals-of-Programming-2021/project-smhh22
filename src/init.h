//besmellah
//#pragma once
#include "show.h"
//#include "read_map.h"

void init();
void Define_global_size_variables();

void init () {
	Read_map("maps/map.txt");
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	WINDOW = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 640, SDL_WINDOW_OPENGL);
	RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(RENDERER, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(RENDERER);
//	Add SDL_WINDOW_RESIZABLE to flags.
	Define_global_size_variables();
	SDL_Delay(10000);
}

void Define_global_size_variables() {
	SDL_GL_GetDrawableSize(WINDOW, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	WINDOW_PADDING_UP = SCREEN_HEIGHT / 5;
	WINDOW_PADDING_RIGHT = SCREEN_WIDTH / 20;
	WINDOW_PADDING_DOWN = SCREEN_HEIGHT / 10;
	WINDOW_PADDING_LEFT = SCREEN_WIDTH / 20;

	WIDTH = SCREEN_WIDTH - WINDOW_PADDING_RIGHT - WINDOW_PADDING_LEFT;
	HEIGHT = SCREEN_HEIGHT - WINDOW_PADDING_UP - WINDOW_PADDING_DOWN;
//	uint32_t color = 0xffffff00;
//	boxColor(RENDERER, 0, 0, SCREEN_WIDTH, WINDOW_PADDING_UP, color);
//	boxColor(RENDERER, 0, 0, WINDOW_PADDING_LEFT, SCREEN_HEIGHT, color);
//	boxColor(RENDERER, SCREEN_WIDTH - WINDOW_PADDING_RIGHT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
//	boxColor(RENDERER, 0, SCREEN_HEIGHT - WINDOW_PADDING_DOWN, SCREEN_WIDTH, SCREEN_HEIGHT, color);
//	SDL_RenderPresent(RENDERER);
//	SDL_SetRenderDrawColor(RENDERER, 0xff, 0xff, 0xff, 0xff);
	
//	NUMBER_OF_PLAYERS = 6;

//	GRID_WIDTH  = 15;
//	GRID_HEIGHT = NUMBER_OF_PLAYERS;
	
	CELL_WIDTH = WIDTH / GRID_WIDTH;
	CELL_HEIGHT = HEIGHT / GRID_HEIGHT;

	CASTLE_SIZE = min(CELL_WIDTH, CELL_HEIGHT) * 4 / 5;

//	GRID = (CELL**)malloc(sizeof(CELL*) * GRID_WIDTH);

	for (int i = 0; i < GRID_WIDTH; i++) {
//		GRID[i] = (CELL*)malloc(sizeof(CELL) * GRID_HEIGHT);
		for (int j = 0; j < GRID_HEIGHT; j++) {
			GRID[i][j].x1 = WINDOW_PADDING_RIGHT + i * CELL_WIDTH;
			GRID[i][j].y1 = WINDOW_PADDING_UP + j * CELL_HEIGHT;
			GRID[i][j].x2 = GRID[i][j].x1 + CELL_WIDTH;
			GRID[i][j].y2 = GRID[i][j].y1 + CELL_HEIGHT;
//			for (int k = 0; k < 4; k++) {
//				GRID[i][j].Border_shown[k] = 1;
//			}
//			boxColor(RENDERER, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y2, GRID[i][j].Castle_ptr->Player->Color);
		}
	}

	show_map(RENDERER);
	show_bar(RENDERER);

	uint32_t color = 0xffffff00;
//	boxColor(RENDERER, 0, 0, SCREEN_WIDTH, WINDOW_PADDING_UP, color);
//	boxColor(RENDERER, 0, 0, WINDOW_PADDING_LEFT, SCREEN_HEIGHT, color);
//	boxColor(RENDERER, SCREEN_WIDTH - WINDOW_PADDING_RIGHT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
//	boxColor(RENDERER, 0, SCREEN_HEIGHT - WINDOW_PADDING_DOWN, SCREEN_WIDTH, SCREEN_HEIGHT, color);
	SDL_RenderPresent(RENDERER);
//	SDL_SetRenderDrawColor(RENDERER, 0xff, 0xff, 0xff, 0xff);
}
