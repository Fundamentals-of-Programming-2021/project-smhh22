//besmellah

#pragma once

#include "logic.h"

void event_handling();
void ingame_event(SDL_Event*);

void event_handling() {
	SDL_Event EVENT;
	while (SDL_PollEvent(&EVENT)) {
		if (EVENT.type == SDL_QUIT) MODE = EXIT;
		else {
			if (MODE == GAME) {
				ingame_event(&EVENT);
			}
		}
	}
}

void ingame_event(SDL_Event *EVENT) {
//	if (Chosen != NULL && Chosen->Player != Players + 2)
//		Chosen = NULL;
	if (EVENT->type == SDL_MOUSEBUTTONDOWN) {
		int bx = EVENT->button.x;
		int by = EVENT->button.y;
		if (bx < WINDOW_PADDING_RIGHT || by < WINDOW_PADDING_UP) {
			Chosen = NULL;
			return;
		}
		int x = (bx - WINDOW_PADDING_RIGHT) / CELL_WIDTH;
		int y = (by - WINDOW_PADDING_UP) / CELL_HEIGHT;
		if (x >= GRID_WIDTH || y >= GRID_HEIGHT) {
			Chosen = NULL;
			return;
		}
		if (CASTLE_PTRS[x][y] == NULL || CASTLE_PTRS[x][y]->Player == Players + 1) return;
		int mx = (GRID[x][y].x1 + GRID[x][y].x2) / 2;
		int my = (GRID[x][y].y1 + GRID[x][y].y2) / 2;
		if (abs(bx - mx) > CASTLE_SIZE / 2 || abs(by - my) > CASTLE_SIZE / 2) return;
		if (Chosen == NULL) {
//			if (CASTLE_PTRS[x][y]->Player == Players + 2) {
				Chosen = CASTLE_PTRS[x][y];
//			}
		}
		else {
			if (Chosen->x != x || Chosen->y != y)
				schedule_deployment(Chosen->x, Chosen->y, x, y, Chosen->Player);
			//Players+2
			Chosen = NULL;
		}
	}
}
