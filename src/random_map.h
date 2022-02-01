//besmellah

#pragma once

#include <time.h>
#include <assert.h>
#include "header.h"

void make_random_map(int);
void random_shuffle(TUPLE*, int);
void random_shuffle_from_end(TUPLE*, int, int, int);
void swap(TUPLE*, TUPLE*);

void make_random_map(int number_of_opponents) {
	srand(time(NULL));
	if (number_of_opponents == -1)
		number_of_opponents = rand() % 5 + 1;
	NUMBER_OF_PLAYERS = number_of_opponents + 3;
	CELL_WIDTH = rand() % 40 + 40;
	GRID_WIDTH = (SCREEN_WIDTH - WINDOW_PADDING_RIGHT - WINDOW_PADDING_LEFT) / CELL_WIDTH;
	GRID_HEIGHT = (SCREEN_HEIGHT - WINDOW_PADDING_UP - WINDOW_PADDING_DOWN) / CELL_WIDTH;

	Players = (PLAYER*)malloc(sizeof(PLAYER) * NUMBER_OF_PLAYERS);
	memset(Players, 0, sizeof(PLAYER) * NUMBER_OF_PLAYERS);
	GRID = (CELL**)malloc(sizeof(CELL*) * GRID_WIDTH);
	CASTLE_PTRS = (CASTLE***)malloc(sizeof(CASTLE**) * GRID_WIDTH);
	for (int i = 0; i < GRID_WIDTH; i++) {
		GRID[i] = (CELL*)malloc(sizeof(CELL) * GRID_HEIGHT);
		memset(GRID[i], 0, sizeof(CELL) * GRID_HEIGHT);
		CASTLE_PTRS[i] = (CASTLE**)malloc(sizeof(CASTLE*) * GRID_HEIGHT);
		for (int j = 0; j < GRID_HEIGHT; j++) {
			CASTLE_PTRS[i][j] = NULL;
			GRID[i][j].Castle_ptr = NULL;
		}
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

	int neutral_territories = rand() % (NUMBER_OF_PLAYERS) + NUMBER_OF_PLAYERS;
	int sea_zones = rand() % 4 + 3; 

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			for (int k = 0; k < 4; k++) {
				GRID[i][j].Border_shown[k] = 1;
			}
			GRID[i][j].Castle_ptr = NULL;
			Grid_cells[i * GRID_HEIGHT + j].x1 = i;
			Grid_cells[i * GRID_HEIGHT + j].x2 = j;
		}
	}

	random_shuffle(Grid_cells, GRID_WIDTH * GRID_HEIGHT);

	for (int i = 0; i < neutral_territories; i++) {
		int x = Grid_cells[i].x1;
		int y = Grid_cells[i].x2;
		GRID[x][y].Castle_ptr = CASTLE_PTRS[x][y] = (CASTLE*)malloc(sizeof(CASTLE));
		memset(CASTLE_PTRS[x][y], 0, sizeof(CASTLE));
		GRID[x][y].Castle_x = x;
		GRID[x][y].Castle_y = y;
		CASTLE_PTRS[x][y]->Soldiers_count = NEUTRAL_INITIAL_SOLDIERS;
		CASTLE_PTRS[x][y]->Player = Players + 0;
		CASTLE_PTRS[x][y]->Player->Soldiers_count += NEUTRAL_INITIAL_SOLDIERS;
		CASTLE_PTRS[x][y]->x = x;
		CASTLE_PTRS[x][y]->y = y;
		TOTAL_SOLDIERS_COUNT += NEUTRAL_INITIAL_SOLDIERS;
	}

	for (int i = neutral_territories; i < neutral_territories + sea_zones; i++) {
		int x = Grid_cells[i].x1;
		int y = Grid_cells[i].x2;
		GRID[x][y].Castle_ptr = CASTLE_PTRS[x][y] = (CASTLE*)malloc(sizeof(CASTLE));
		memset(CASTLE_PTRS[x][y], 0, sizeof(CASTLE));
		GRID[x][y].Castle_x = x;
		GRID[x][y].Castle_y = y;
		CASTLE_PTRS[x][y]->Soldiers_count = 0;
		CASTLE_PTRS[x][y]->Player = Players + 1;
		CASTLE_PTRS[x][y]->x = x;
		CASTLE_PTRS[x][y]->y = y;
	}

	for (int i = neutral_territories + sea_zones; i < neutral_territories + sea_zones + NUMBER_OF_PLAYERS - 2; i++) {
		int x = Grid_cells[i].x1;
		int y = Grid_cells[i].x2;
		GRID[x][y].Castle_ptr = CASTLE_PTRS[x][y] = (CASTLE*)malloc(sizeof(CASTLE));
		memset(CASTLE_PTRS[x][y], 0, sizeof(CASTLE));
		GRID[x][y].Castle_x = x;
		GRID[x][y].Castle_y = y;
		CASTLE_PTRS[x][y]->Soldiers_count = INITIAL_SOLDIERS;
		CASTLE_PTRS[x][y]->Player = Players + 2 + i - neutral_territories - sea_zones;
		CASTLE_PTRS[x][y]->Player->Soldiers_count += INITIAL_SOLDIERS;
		CASTLE_PTRS[x][y]->x = x;
		CASTLE_PTRS[x][y]->y = y;
		TOTAL_SOLDIERS_COUNT += INITIAL_SOLDIERS;
	}

	TUPLE Borders[GRID_WIDTH * GRID_HEIGHT * 4 + 10];
	int ptr = 0;

	for (int i = 0; i < neutral_territories + sea_zones + NUMBER_OF_PLAYERS - 2; i++) {
		for (int j = 0; j < 4; j++) {
			Borders[ptr].x1 = Grid_cells[i].x1;
			Borders[ptr].x2 = Grid_cells[i].x2;
			Borders[ptr++].x3 = j;
		}
	}

	random_shuffle(Borders, ptr);

	for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT * 4; i++) {
//		printf("SALAM %d %d\n", i, GRID_WIDTH * GRID_HEIGHT * 4);
//		fflush(stdout);
		int x = Borders[i].x1;
		int y = Borders[i].x2;
		int k = Borders[i].x3;
//		printf("SALAM %d %d %d\n", x, y, k);
//		fflush(stdout);
		int nx = x + DELTA_X[k];
		int ny = y + DELTA_Y[k];
//		printf("SALAM %d %d\n", x, y);
//		fflush(stdout);
		if (nx < 0 || ny < 0 || nx >= GRID_WIDTH || ny >= GRID_HEIGHT) continue;
		if (GRID[nx][ny].Castle_ptr == NULL) {
			GRID[nx][ny].Castle_ptr = GRID[x][y].Castle_ptr;
			GRID[nx][ny].Castle_x = GRID[x][y].Castle_x;
			GRID[nx][ny].Castle_y = GRID[x][y].Castle_y;
			GRID[x][y].Border_shown[k] = 0;
			for (int k2 = 0; k2 < 4; k2++) {
				Borders[ptr].x1 = nx;
				Borders[ptr].x2 = ny;
				Borders[ptr++].x3 = k2;
			}
			random_shuffle_from_end(Borders, i + 1, ptr - 4, ptr);
		}
		else if (GRID[nx][ny].Castle_ptr == GRID[x][y].Castle_ptr) {
			GRID[x][y].Border_shown[k] = 0;
		}
		else {
			continue;
		}
	}
}

void random_shuffle(TUPLE* list, int n) {
	for (int t = 0; t < n; t++) {
		int x = rand() % (n - t) + t;
		for (int i = x; i > t; i--) {
			swap(list + i, list + i - 1);
		}
	}
}

void random_shuffle_from_end(TUPLE* list, int l, int m, int r) {
	srand(time(NULL));
	for (int i = m; i < r; i++) {
		int x = rand() % (r - l) + l;
		for (int j = i; j > x; j--) {
			swap(list + j, list + j - 1);
		}
	}
}

void swap(TUPLE* A, TUPLE* B) {
	TUPLE Z = *A;
	*A = *B;
	*B = Z;
}
