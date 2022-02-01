//besmellah

#pragma once

#include "read_map.h"
#include "random_map.h"
#include "logic.h"

void show_background(SDL_Renderer*);
void show_map(SDL_Renderer*);
void show_bar(SDL_Renderer*);
void show_potion(SDL_Renderer*, int, int, char*);
void show_soldiers(SDL_Renderer*);

void diamondColor(SDL_Renderer*, int, int, int, uint32_t);

void show_sample(SDL_Renderer*);

void show_background(SDL_Renderer* renderer) {
	for (int i = 1; i <= 10; i++) {
		lineColor(renderer, 0, i * WINDOW_PADDING_UP / 5, (10 - i) * WINDOW_PADDING_UP / 5, 0, 0xaa000000 | (i * 0x00101000));
	}

	for (int i = 1; i <= 8; i++) {
		lineColor(renderer, SCREEN_WIDTH, SCREEN_HEIGHT - i * WINDOW_PADDING_UP / 5, SCREEN_WIDTH - (8 - i) * WINDOW_PADDING_UP / 5, SCREEN_HEIGHT, 0xaa000000 | (i * 0x00100005));
	}
}

void show_map(SDL_Renderer *renderer) {
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (GRID[i][j].Castle_ptr->Player != Players + 1) {
				boxColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y2, GRID[i][j].Castle_ptr->Player->Color | (GRID[i][j].Castle_ptr->Soldiers_count * 0x01000000));
			}
			else {
				boxColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y2, 0xffff5000);
			}

			if (GRID[i][j].Border_shown[0]) {
				thickLineColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y1, BORDER_THICKNESS, 0xff000000);
			}

			if (GRID[i][j].Border_shown[1]) {
				thickLineColor(renderer, GRID[i][j].x2, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y2, BORDER_THICKNESS, 0xff000000);
			}

			if (GRID[i][j].Border_shown[2]) {
				thickLineColor(renderer, GRID[i][j].x1, GRID[i][j].y2, GRID[i][j].x2, GRID[i][j].y2, BORDER_THICKNESS, 0xff000000);
			}

			if (GRID[i][j].Border_shown[3]) {
				thickLineColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x1, GRID[i][j].y2, BORDER_THICKNESS, 0xff000000);
			}
			
			if (CASTLE_PTRS[i][j] != NULL && CASTLE_PTRS[i][j]->Player != Players + 1) {
				int mx = (GRID[i][j].x1 + GRID[i][j].x2) / 2;
				int my = (GRID[i][j].y1 + GRID[i][j].y2) / 2;
				boxColor(renderer, mx - CASTLE_SIZE / 2, my - CASTLE_SIZE / 2, mx + CASTLE_SIZE / 2, my + CASTLE_SIZE / 2, CASTLE_PTRS[i][j]->Player->Color | 0xff000000);

				rectangleColor(renderer, mx - CASTLE_SIZE / 2, my - CASTLE_SIZE / 2, mx + CASTLE_SIZE / 2, my + CASTLE_SIZE / 2, CASTLE_PTRS[i][j]->Player->Color ^ 0xffffffff);

				char *Sol_cnt = (char*)(malloc(sizeof(char) * 15));
				int len;
				if (Chosen != CASTLE_PTRS[i][j])
					len = sprintf(Sol_cnt, "%d", CASTLE_PTRS[i][j]->Soldiers_count);
				else
					len = sprintf(Sol_cnt, "%d*", CASTLE_PTRS[i][j]->Soldiers_count);
				stringColor(renderer, mx - len * 4, my - 4, Sol_cnt, CASTLE_PTRS[i][j]->Player->Color ^ 0xffffffff);
			}
		}
	}
}

void show_bar(SDL_Renderer *renderer) {
	if (!TOTAL_SOLDIERS_COUNT) {
		printf("Error loading bar: Division by zero not allowed.\n");
		fflush(stdout);
	}

	double sum = 0;
	for (int i = 2; i < NUMBER_OF_PLAYERS; i++) {
		if (!Players[i].Soldiers_count) continue;
		thickLineColor(renderer, WINDOW_PADDING_LEFT + (int)(sum / TOTAL_SOLDIERS_COUNT * WIDTH), 20 + WINDOW_PADDING_UP / 2, WINDOW_PADDING_LEFT + (int)((sum + Players[i].Soldiers_count) / TOTAL_SOLDIERS_COUNT * WIDTH), 20 + WINDOW_PADDING_UP / 2, BAR_THICKNESS, Players[i].Color | 0xff000000);
		sum += Players[i].Soldiers_count;
	}
	if (!Players[0].Soldiers_count) return;
	thickLineColor(renderer, WINDOW_PADDING_LEFT + (int)(sum / TOTAL_SOLDIERS_COUNT * WIDTH), 20 + WINDOW_PADDING_UP / 2, WINDOW_PADDING_LEFT + (int)((sum + Players[0].Soldiers_count) / TOTAL_SOLDIERS_COUNT * WIDTH), 20 + WINDOW_PADDING_UP / 2, BAR_THICKNESS, Players[0].Color | 0xff000000);
}

void show_potion(SDL_Renderer *renderer, int x, int y, char *type) {
	int mx = (GRID[x][y].x1 + GRID[x][y].x2) / 2;
	int my = (GRID[x][y].y1 + GRID[x][y].y2) / 2;
	diamondColor(renderer, mx, my, CASTLE_SIZE / 2, GRID[x][y].Castle_ptr->Player->Color ^ 0xffffffff);

	filledCircleColor(renderer, mx, my, (int)sqrtl(CASTLE_SIZE * CASTLE_SIZE / 2) / 2, GRID[x][y].Castle_ptr->Player->Color ^ 0x80808080);

	stringColor(renderer, mx - 8, my - 4, type, GRID[x][y].Castle_ptr->Player->Color | 0xff000000);
}

void show_soldiers(SDL_Renderer *renderer) {
	DEPLOYED_SOLDIER *cur = HEAD;
	while (cur != NULL) {
		diamondColor(renderer, cur->x, cur->y, SOLDIER_SIZE, cur->Player->Color | 0xff000000);
		cur = cur->nxt;
	}
}


void diamondColor(SDL_Renderer *renderer, int x, int y, int r, uint32_t Color) {
	short X[4] = {x - r, x, x + r, x};
	short Y[4] = {y, y + r, y, y - r};
	filledPolygonColor(renderer, X, Y, 4, Color);
}


void show_sample(SDL_Renderer *renderer) {
	show_background(renderer);
	show_map(renderer);
	show_bar(renderer);
	show_potion(renderer, 1, 1, "S1");
//	show_potion(renderer, 2, 2, "C2");
	soldiers_motion();
//	schedule_deployment(GRID[5][5].Castle_x, GRID[5][5].Castle_y, GRID[4][4].Castle_x, GRID[4][4].Castle_y, GRID[5][5].Castle_ptr->Player);
	deploy_all();
	show_soldiers(renderer);
}
