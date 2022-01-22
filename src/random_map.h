//besmellah

#pragma once

#include "header.h"

void make_random_map(int number_of_opponents) {
	if (number_of_opponents == -1)
		number_of_opponents = rand() % 5 + 1;
	NUMBER_OF_PLAYERS = number_of_opponents + 3;
	CELL_WIDTH = rand() % 100 + 50;
	GRID_WIDTH = (SCREEN_WIDTH - WINDOW_PADDING_RIGHT - WINDOW_PADDING_LEFT) / CELL_WIDTH;
	GRID_HEIGHT = (SCREEN_HEIGHT - WINDOW_PADDING_UP - WINDOW_PADDING_DOWN) / CELL_WIDTH;

	Players = (Player*)malloc(sizeof(PLAYER) * NUMBER_OF_PLAYERS);
	GRID = (CELL**)malloc(sizeof(CELL*) * GRID_WIDTH);
	CASTLE_PTRS = (CASTLE***)malloc(sizeof(CASTLE**) * GRID_WIDTH);
	for (int i = 0; i < GRID_WIDTH; i++) {
		GRID[i] = (CELL*)malloc(sizeof(CELL) * GRID_HEIGHT);
		CASTLE_PTRS[i] = (CASTLE**)malloc(sizeof(CASTLE*) * GRID_HEIGHT);
	}

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		Players[i].Color = 0x00000000;
		if (i & (1 << 0))
			Players[i].Color |= 0x00ff0000;
		if (i & (1 << 1))
			Players[i].Color |= 0x0000ff00;
		if (i & (1 << 2))
			Players[i].Color |= 0x000000ff;
		Players[i].Potion_enabled = -1;
		Players[i].Soldiers_count = 0;
	}
}
