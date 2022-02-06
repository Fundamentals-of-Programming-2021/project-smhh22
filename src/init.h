//besmellah

#pragma once

#include "show.h"

void init();
void Define_global_size_variables();

void init () {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	TTF_Init();
	proFontWindows = TTF_OpenFont("fonts/ProFontWindows/ProFontWindows.ttf", 24);
	WINDOW = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(RENDERER, 0xee, 0xdd, 0xcc, 0xff);
	SDL_RenderClear(RENDERER);
	SDL_StartTextInput();
}

void Define_global_size_variables() {
	CELL_WIDTH = WIDTH / GRID_WIDTH;
	CELL_HEIGHT = HEIGHT / GRID_HEIGHT;

	WIDTH = GRID_WIDTH * CELL_WIDTH;
	HEIGHT = GRID_HEIGHT * CELL_HEIGHT;

	int mn = min(CELL_WIDTH, CELL_HEIGHT);

	CASTLE_SIZE = mn * 4.0 / 5.0;
	
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			GRID[i][j].x1 = WINDOW_PADDING_RIGHT + i * CELL_WIDTH;
			GRID[i][j].y1 = WINDOW_PADDING_UP + j * CELL_HEIGHT;
			GRID[i][j].x2 = GRID[i][j].x1 + CELL_WIDTH;
			GRID[i][j].y2 = GRID[i][j].y1 + CELL_HEIGHT;
		}
	}
}
