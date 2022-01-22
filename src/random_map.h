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

	TUPLE Grid_cells[GRID_WIDTH * GRID_HEIGHT];

	int neutral_territories = rand() % NUMBER_OF_PLAYERS + 2 * NUMBER_OF_PLAYERS;
	int sea_zones = rand() % 3 + 3; 

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			for (int k = 0; k < 4; k++) {
				GRID[i][j].Border_shown[k] = 1;
			}
			Grid_cells[i * GRID_HEIGHT + j].x1 = i;
			Grid_cells[i * GRID_HEIGHT + j].x2 = j;
		}
	}

	random_shuffle(Grid_cells, GRID_WIDTH * GRID_HEIGHT);

	for (int i = 0; i < neutral_territories; i++) {
		int x = Grid_cells.x1;
		int y = Grid_cells.x2;
		GRID[x][y].Castle_ptr = CASTLE_PTRS[x][y] = (CASTLE*)malloc(sizeof(CASTLE));
		CASTLE_PTRS[x][y]->Soldiers_count = NEUTRAL_INITIAL_SOLDIERS;
		CASTLE_PTRS[x][y]->Player = Players + 0;
		CASTLE_PTRS[x][y]->Player->Soldiers_count += NEUTRAL_INITIAL_SOLDIERS;
		TOTAL_SOLDIERS_COUNT += NEUTRAL_INITIAL_SOLDIERS;
	}

	for (int i = neutral_territories; i < neutral_territories + sea_zones; i++) {
		int x = Grid_cells.x1;
		int y = Grid_cells.x2;
		GRID[x][y].Castle_ptr = CASTLE_PTRS[x][y] = (CASTLE*)malloc(sizeof(CASTLE));
		CASTLE_PTRS[x][y]->Soldiers_count = 0;
		CASTLE_PTRS[x][y]->Player = Players + 1;
	}

	for (int i = neutral_territories + sea_zones; i < neutral_territories + sea_zones + NUMBER_OF_PLAYERS - 2) {
		int x = Grid_cells.x1;
		int y = Grid_cells.x2;
		GRID[x][y].Castle_ptr = CASTLE_PTRS[x][y] = (CASTLE*)malloc(sizeof(CASTLE));
		CASTLE_PTRS[x][y]->Soldiers_count = INITIAL_SOLDIERS;
		CASTLE_PTRS[x][y]->Player = Players + 2 + i - neutral_territories - sea_zones;
		CASTLE_PTRS[x][y]->Player->Soldiers_count += INITIAL_SOLDIERS;
		TOTAL_SOLDIERS_COUNT += INITIAL_SOLDIERS;
	}

	TUPLE Borders[GRID_WIDTH * GRID_HEIGHT * 4 + 10];
	int ptr = 0;

	for (int i = 0; i < neutral_territories + sea_zones + NUMBER_OF_PLAYERS - 2; i++) {
		for (int j = 0; j < 4; j++) {
			Borders[ptr].x1 = Grid_cells[i].x1;
			Borders[ptr].x2 = Grid_cells[i].x2;
			Borders[ptr++].x2 = j
		}
	}
	
	random_shuffle(Borders, ptr);
}
