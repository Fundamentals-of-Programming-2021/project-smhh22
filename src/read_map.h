//bemellah

#pragma once

#include "header.h"

void Read_map(char *str);
int read_map_cnt();
void assign_map_cnt(int x);
void Save_map_to_end();

void Read_map(char *str) {
	FILE* Map_file = fopen(str, "r");

	fscanf(Map_file, "%d ", &NUMBER_OF_PLAYERS);
	fscanf(Map_file, "%d ", &GRID_WIDTH);
	fscanf(Map_file, "%d ", &GRID_HEIGHT);

	Players = (PLAYER*)malloc(sizeof(PLAYER) * NUMBER_OF_PLAYERS);
	Candids = (TUPLE*)malloc(sizeof(TUPLE) * GRID_WIDTH * GRID_HEIGHT);
	memset(Players, 0, sizeof(PLAYER) * NUMBER_OF_PLAYERS);
	memset(Candids, 0, sizeof(TUPLE) * GRID_WIDTH * GRID_HEIGHT);
	GRID = (CELL**)malloc(sizeof(CELL*) * GRID_WIDTH);
	isCandid = (int**)malloc(sizeof(int*) * GRID_WIDTH);
	CASTLE_PTRS = (CASTLE***)malloc(sizeof(CASTLE**) * GRID_WIDTH);
	for (int i = 0; i < GRID_WIDTH; i++) {
		GRID[i] = (CELL*)malloc(sizeof(CELL) * GRID_HEIGHT);
		isCandid[i] = (int*)malloc(sizeof(int) * GRID_HEIGHT);
		memset(GRID[i], 0, sizeof(CELL) * GRID_HEIGHT);
		memset(isCandid[i], 0, sizeof(int) * GRID_HEIGHT);
		CASTLE_PTRS[i] = (CASTLE**)malloc(sizeof(CASTLE*) * GRID_HEIGHT);
		memset(CASTLE_PTRS[i], 0, sizeof(CASTLE*) * GRID_HEIGHT);
	}
	
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		fscanf(Map_file, "%x ", &Players[i].Color);
		Players[i].Potion_enabled = -1;
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			for (int k = 0; k < 4; k++) {
				fscanf(Map_file, "%hhd ", &GRID[i][j].Border_shown[k]);
			}

			fscanf(Map_file, "%d %d ", &GRID[i][j].Castle_x, &GRID[i][j].Castle_y);
			int x = GRID[i][j].Castle_x;
			int y = GRID[i][j].Castle_y;
			if (CASTLE_PTRS[x][y] != NULL) {
				GRID[i][j].Castle_ptr = CASTLE_PTRS[x][y];
			}
			else {
				GRID[i][j].Castle_ptr = CASTLE_PTRS[x][y] = (CASTLE*)malloc(sizeof(CASTLE));
				memset(CASTLE_PTRS[x][y], 0, sizeof(CASTLE));
			}
		}
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			char mode[30];
			fscanf(Map_file, "%s ", mode);

			if (mode[0] != 'N') {

				fscanf(Map_file, "%d ", &(CASTLE_PTRS[i][j]->Soldiers_count));

				int p;
				fscanf(Map_file, "%d ", &p);
				CASTLE_PTRS[i][j]->Player = Players + p;
				CASTLE_PTRS[i][j]->Player->Soldiers_count += CASTLE_PTRS[i][j]->Soldiers_count;
				CASTLE_PTRS[i][j]->x = i;
				CASTLE_PTRS[i][j]->y = j;

				TOTAL_SOLDIERS_COUNT += CASTLE_PTRS[i][j]->Soldiers_count;
			}
		}
	}
	fclose(Map_file);
}

void Save_map_to_end() {
	char str[100];
	int MAP_ID = read_map_cnt();
	sprintf(str, "maps/map%d.txt", MAP_ID);
	assign_map_cnt(MAP_ID + 1);

	FILE* Map_file = fopen(str, "w");

	fprintf(Map_file, "%d\n", NUMBER_OF_PLAYERS);
	fprintf(Map_file, "%d\n", GRID_WIDTH);
	fprintf(Map_file, "%d\n", GRID_HEIGHT);

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		fprintf(Map_file, "%x\n", Players[i].Color);
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			for (int k = 0; k < 4; k++) {
				fprintf(Map_file, "%hhd ", GRID[i][j].Border_shown[k]);
			}

			fprintf(Map_file, "\n");

			fprintf(Map_file, "%d %d\n", GRID[i][j].Castle_x, GRID[i][j].Castle_y);
		}
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			char mode[30];
			if (CASTLE_PTRS[i][j]) sprintf(mode, "%s", "Otherwise");
			else sprintf(mode, "%s", "Null");
			fprintf(Map_file, "%s\n", mode);

			if (mode[0] != 'N') {
				fprintf(Map_file, "%d\n", CASTLE_PTRS[i][j]->Soldiers_count);
				int p = CASTLE_PTRS[i][j]->Player - Players;
				fprintf(Map_file, "%d\n", p);
			}
		}
	}
	fclose(Map_file);
}

int read_map_cnt() {
	FILE *file = fopen("maps/map_cnt.txt", "r");
	int ans;
	fscanf(file, "%d\n", &ans);
	fclose(file);
	return ans;
}

void assign_map_cnt(int x) {
	FILE *file = fopen("maps/map_cnt.txt", "w");
	fprintf(file, "%d\n", x);
	fclose(file);
}
