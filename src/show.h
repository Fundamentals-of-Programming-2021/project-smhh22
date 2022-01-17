//besmellah
#include "read_map.h"

void show_map(SDL_Renderer*);
void show_bar(SDL_Renderer*);

void show_map(SDL_Renderer *renderer) {
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			boxColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y2, GRID[i][j].Castle_ptr->Player->Color | (GRID[i][j].Castle_ptr->Soldiers_count * 0x01000000));

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
			
			if (CASTLE_PTRS[i][j] != NULL) {
				int mx = (GRID[i][j].x1 + GRID[i][j].x2) / 2;
				int my = (GRID[i][j].y1 + GRID[i][j].y2) / 2;
				boxColor(renderer, mx - CASTLE_SIZE / 2, my - CASTLE_SIZE / 2, mx + CASTLE_SIZE / 2, my + CASTLE_SIZE / 2, CASTLE_PTRS[i][j]->Player->Color | 0xff000000);

				char *Sol_cnt = (char*)(malloc(sizeof(char) * 15));
				sprintf(Sol_cnt, "%d", CASTLE_PTRS[i][j]->Soldiers_count);
				stringColor(renderer, mx, my, Sol_cnt, CASTLE_PTRS[i][j]->Player->Color ^ 0xffffffff);
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
	for (int i = 1; i < NUMBER_OF_PLAYERS; i++) {
		thickLineColor(renderer, WINDOW_PADDING_LEFT + (int)(sum / TOTAL_SOLDIERS_COUNT * WIDTH), WINDOW_PADDING_UP / 2, WINDOW_PADDING_LEFT + (int)((sum + Players[i].Soldiers_count) / TOTAL_SOLDIERS_COUNT * WIDTH), WINDOW_PADDING_UP / 2, BAR_THICKNESS, Players[i].Color | 0xff000000);
		sum += Players[i].Soldiers_count;
	}
	thickLineColor(renderer, WINDOW_PADDING_LEFT + (int)(sum / TOTAL_SOLDIERS_COUNT * WIDTH), WINDOW_PADDING_UP / 2, WINDOW_PADDING_LEFT + (int)((sum + Players[0].Soldiers_count) / TOTAL_SOLDIERS_COUNT * WIDTH), WINDOW_PADDING_UP / 2, BAR_THICKNESS, Players[0].Color | 0xff000000);
}
