//bemellah

#pragma once

#include "header.h"

void Read_map(char *str);
int read_map_cnt();
void assign_map_cnt(int x);

void Read_map(char *str) {
	FILE* Map_file = fopen(str, "r");

	fscanf(Map_file, "%d ", &NUMBER_OF_PLAYERS);
	fscanf(Map_file, "%d ", &GRID_WIDTH);
	fscanf(Map_file, "%d ", &GRID_HEIGHT);

	Players = (PLAYER*)malloc(sizeof(PLAYER) * NUMBER_OF_PLAYERS);
	GRID = (CELL**)malloc(sizeof(CELL*) * GRID_WIDTH);
	CASTLE_PTRS = (CASTLE***)malloc(sizeof(CASTLE**) * GRID_WIDTH);
	for (int i = 0; i < GRID_WIDTH; i++) {
		GRID[i] = (CELL*)malloc(sizeof(CELL) * GRID_HEIGHT);
		CASTLE_PTRS[i] = (CASTLE**)malloc(sizeof(CASTLE*) * GRID_HEIGHT);
	}

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		fscanf(Map_file, "%x ", &Players[i].Color);
		Players[i].Potion_enabled = -1;
		Players[i].Soldiers_count = 0;
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			for (int k = 0; k < 4; k++) {
				fscanf(Map_file, "%hhd ", &GRID[i][j].Border_shown[k]);
			}

			int x, y;
			fscanf(Map_file, "%d %d ", &x, &y);
			if (CASTLE_PTRS[x][y] != NULL) {
				GRID[i][j].Castle_ptr = CASTLE_PTRS[x][y];
			}
			else {
				GRID[i][j].Castle_ptr = CASTLE_PTRS[x][y] = (CASTLE*)malloc(sizeof(CASTLE));
			}
		}
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			char* mode = (char*)malloc(sizeof(char) * 30);
			fscanf(Map_file, "%s ", mode);

			if (mode[0] != 'N') {
				fscanf(Map_file, "%d ", &(CASTLE_PTRS[i][j]->Soldiers_count));
				int p;
				fscanf(Map_file, "%d ", &p);
				CASTLE_PTRS[i][j]->Player = Players + p;
				CASTLE_PTRS[i][j]->Player->Soldiers_count += CASTLE_PTRS[i][j]->Soldiers_count;

				TOTAL_SOLDIERS_COUNT += CASTLE_PTRS[i][j]->Soldiers_count;
			}

			free(mode);
		}
	}
	fclose(Map_file);
}

int read_map_cnt() {
	FILE *file = fopen("maps/map_cnt.txt", "r");
	int ans;
	fscanf(file, "%d", &ans);
	fclose(file);
}

void assign_map_cnt(int x) {
	FILE *file = fopen("maps/map_cnt.txt", "w");
	fprintf(file, "%d", x);
	fclose(file);
}
