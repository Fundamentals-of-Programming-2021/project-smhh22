//besmellah

#pragma once

#include "logic.h"
#include "init.h"

void event_handling();
void ingame_event(SDL_Event*);
void pause_event(SDL_Event*);
void start_event(SDL_Event*);
void menu_event(SDL_Event*);
void leaderboard_event(SDL_Event*);
void choosemap_event(SDL_Event*);
void randommap_event(SDL_Event*);

void init_leaderboard();
void finish_leaderboard();

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
			else if (MODE == LEADERBOARD) {
				leaderboard_event(&EVENT);
			}
			else if (MODE == CHOOSEMAP) {
				choosemap_event(&EVENT);
			}
			else if (MODE == RANDOMMAP) {
				randommap_event(&EVENT);
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
			if (username[0] == '\0') return;
			SDL_StopTextInput();
			read_user();
			save_user();
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
			STATE = NA;
		}
		else if (EVENT->key.keysym.sym == SDLK_l) {
			init_leaderboard();
			MODE = LEADERBOARD;
		}
		else if (EVENT->key.keysym.sym == SDLK_g) {
			shown_map = 0;
			Read_map("maps/map0.txt");
			Define_global_size_variables();
			MODE = CHOOSEMAP;
		}
	}
}

void leaderboard_event(SDL_Event *EVENT) {
	if (EVENT->type == SDL_KEYDOWN) {
		if (EVENT->key.keysym.sym == SDLK_b) {
			finish_leaderboard();
			MODE = MENU;
		}
	}
}

void choosemap_event(SDL_Event *EVENT) {
	if (EVENT->type == SDL_KEYDOWN) {
		if (EVENT->key.keysym.sym == SDLK_b) {
			clean_game();
			MODE = MENU;
		}
		else if (EVENT->key.keysym.sym == SDLK_RIGHT) {
			if (shown_map == read_map_cnt() - 1) return;
			clean_game();
			shown_map++;
			char str[16];
			sprintf(str, "maps/map%d.txt", shown_map);
			Read_map(str);
			Define_global_size_variables();
		}
		else if (EVENT->key.keysym.sym == SDLK_LEFT) {
			if (shown_map == 0) return;
			clean_game();
			shown_map--;
			char str[16];
			sprintf(str, "maps/map%d.txt", shown_map);
			Read_map(str);
			Define_global_size_variables();
		}
		else if (EVENT->key.keysym.sym == SDLK_g) {
			MODE = GAME;
		}
		else if (EVENT->key.keysym.sym == SDLK_0 || EVENT->key.keysym.sym == SDLK_KP_0) {
			clean_game();
			make_random_map(-1);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_1 || EVENT->key.keysym.sym == SDLK_KP_1) {
			clean_game();
			make_random_map(1);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_2 || EVENT->key.keysym.sym == SDLK_KP_2) {
			clean_game();
			make_random_map(2);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_3 || EVENT->key.keysym.sym == SDLK_KP_3) {
			clean_game();
			make_random_map(3);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_4 || EVENT->key.keysym.sym == SDLK_KP_4) {
			clean_game();
			make_random_map(4);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_5 || EVENT->key.keysym.sym == SDLK_KP_5) {
			clean_game();
			make_random_map(5);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
	}
}

void randommap_event(SDL_Event *EVENT) {
	if (EVENT->type == SDL_KEYDOWN) {
		if (EVENT->key.keysym.sym == SDLK_b) {
			clean_game();
			MODE = MENU;
		}
		else if (EVENT->key.keysym.sym == SDLK_g) {
			MODE = GAME;
		}
		else if (EVENT->key.keysym.sym == SDLK_s) {
			if (hasbeensaved) return;
			Save_map_to_end();
			hasbeensaved = 1;
		}
		else if (EVENT->key.keysym.sym == SDLK_0 || EVENT->key.keysym.sym == SDLK_KP_0) {
			clean_game();
			make_random_map(-1);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_1 || EVENT->key.keysym.sym == SDLK_KP_1) {
			clean_game();
			make_random_map(1);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_2 || EVENT->key.keysym.sym == SDLK_KP_2) {
			clean_game();
			make_random_map(2);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_3 || EVENT->key.keysym.sym == SDLK_KP_3) {
			clean_game();
			make_random_map(3);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_4 || EVENT->key.keysym.sym == SDLK_KP_4) {
			clean_game();
			make_random_map(4);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
		else if (EVENT->key.keysym.sym == SDLK_5 || EVENT->key.keysym.sym == SDLK_KP_5) {
			clean_game();
			make_random_map(5);
			Define_global_size_variables();
			MODE = RANDOMMAP;
		}
	}
}


void init_leaderboard() {
	int cnt = 0;
	char str[110];
	FILE *file = fopen("users/users", "r");
	while (!feof(file)) {
		fgets(str, 105, file);
		cnt++;
	}
	cnt--;
	fclose(file);
	file = fopen("users/users", "r");
	char** strs = (char**)malloc(sizeof(char*) * (cnt + 1));
	for (int i = 0; i <= cnt; i++) {
		strs[i] = (char*)malloc(sizeof(char) * 110);
	}
	int* a = (int*)malloc(sizeof(int) * (cnt + 1));
	for (int i = 0; i < cnt; i++) {
		a[i] = i;
		fgets(strs[i], 105, file);
		strs[i][strlen(strs[i]) - 1] = '\0';
	}
	fclose(file);
	user_sort(strs, a, cnt);
	LEADERBOARDSTRS = strs;
	LEADERBOARDA = a;
	LEADERBOARDCNT = cnt;
}

void finish_leaderboard() {
	if (LEADERBOARDA == NULL) return;
	free(LEADERBOARDA);
	for (int i = 0; i <= LEADERBOARDCNT; i++) {
		free(LEADERBOARDSTRS[i]);
	}
	free(LEADERBOARDSTRS);
	LEADERBOARDCNT = 0;
	LEADERBOARDA = NULL;
	LEADERBOARDSTRS = NULL;
}


void clean_game() {
	remove_all_soldiers();
	if (Players != NULL)
		free(Players);
	Players = NULL;
	for (int i = 0; i < GRID_WIDTH; i++) {
		free(GRID[i]);
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (CASTLE_PTRS[i][j] != NULL)
				free(CASTLE_PTRS[i][j]);
		}
		free(CASTLE_PTRS[i]);
	}
	GRID_WIDTH = 0;
	GRID_HEIGHT = 0;
	if (GRID != NULL)
		free(GRID);
	GRID = NULL;
	if (CASTLE_PTRS != NULL)
		free(CASTLE_PTRS);
	CASTLE_PTRS = NULL;
	TOTAL_SOLDIERS_COUNT = 0;
	hasbeensaved = 0;
}
