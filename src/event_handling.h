//besmellah

#pragma once

#include "logic.h"

void event_handling();
void ingame_event(SDL_Event*);
void pause_event(SDL_Event*);
void start_event(SDL_Event*);
void menu_event(SDL_Event*);

void clean_game();

void event_handling() {
	SDL_Event EVENT;
	while (SDL_PollEvent(&EVENT)) {
		if (EVENT.type == SDL_QUIT) MODE = EXIT;
		else {
			if (MODE == GAME) {
				ingame_event(&EVENT);
			}
			else if (MODE == PAUSE) {
				pause_event(&EVENT);
			}
			else if (MODE == START) {
				start_event(&EVENT);
			}
			else if (MODE == MENU) {
				menu_event(&EVENT);
			}
		}
	}
}

void ingame_event(SDL_Event *EVENT) {
	if (Chosen != NULL && Chosen->Player != Players + 2)
		Chosen = NULL;
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
			if (CASTLE_PTRS[x][y]->Player == Players + 2) {
				Chosen = CASTLE_PTRS[x][y];
			}
		}
		else {
			if (Chosen->x != x || Chosen->y != y)
				schedule_deployment(Chosen->x, Chosen->y, x, y, Players + 2);
			Chosen = NULL;
		}
	}
	else if (EVENT->type == SDL_KEYDOWN) {
		if (EVENT->key.keysym.sym == SDLK_PAUSE || EVENT->key.keysym.sym == SDLK_SPACE || EVENT->key.keysym.sym == SDLK_ESCAPE) {
			MODE = PAUSE;
		}
	}
}

void pause_event(SDL_Event *EVENT) {
	if (EVENT->type == SDL_KEYDOWN) {
		if (EVENT->key.keysym.sym == SDLK_PAUSE || EVENT->key.keysym.sym == SDLK_SPACE || EVENT->key.keysym.sym == SDLK_ESCAPE) {
			MODE = GAME;
		}
	}
}

void start_event(SDL_Event *EVENT) {
	if (EVENT->type == SDL_TEXTINPUT) {
		strcat(username, EVENT->text.text);
	}
	else if (EVENT->type == SDL_KEYDOWN) {
		if (EVENT->key.keysym.sym == SDLK_BACKSPACE) {
			if (strlen(username)) {
				username[strlen(username) - 1] = '\0';
			}
		}
		else if (EVENT->key.keysym.sym == SDLK_RETURN || EVENT->key.keysym.sym == SDLK_KP_ENTER) {
			SDL_StopTextInput();
			read_user();
			MODE = MENU;
		}
	}
}

void menu_event(SDL_Event *EVENT) {
	if (EVENT->type == SDL_KEYDOWN) {
		if (EVENT->key.keysym.sym == SDLK_q) {
			MODE = EXIT;
		}
		else if (EVENT->key.keysym.sym == SDLK_s) {
			memset(username, 0, sizeof(username));
			score = 0;
			SDL_StartTextInput();
			MODE = START;
		}
		else if (EVENT->key.keysym.sym == SDLK_l) {
			MODE = LEADERBOARD;
		}
		else if (EVENT->key.keysym.sym == SDLK_g) {
			shown_map = 0;
			MODE = CHOOSEMAP;
		}
	}
}

void clean_game() {
	remove_all_soldiers();
	free(Players);
	for (int i = 0; i < GRID_WIDTH; i++) {
		free(GRID[i]);
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (CASTLE_PTRS[i][j] != NULL)
				free(CASTLE_PTRS[i][j]);
		}
		free(CASTLE_PTRS[i]);
	}
	free(GRID);
	free(CASTLE_PTRS);
}
