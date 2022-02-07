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

void print_to_game_terminal(SDL_Renderer*, char*, int);

void show_game(SDL_Renderer*);
void show_pause(SDL_Renderer*);
void show_start(SDL_Renderer*);
void show_menu(SDL_Renderer*);
void show_leaderboard(SDL_Renderer*);
void show_choosemap(SDL_Renderer*);
void show_randommap(SDL_Renderer*);

void show(SDL_Renderer*);

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
				boxColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y2, GRID[i][j].Castle_ptr->Player->Color | (min(GRID[i][j].Castle_ptr->Soldiers_count, 255) * 0x01000000));
			}
			else {
				boxColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y2, 0xffff5000);
			}

			if (GRID[i][j].Border_shown[0]) {
				thickLineColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y1, BORDER_THICKNESS, 0xff111133);
			}

			if (GRID[i][j].Border_shown[1]) {
				thickLineColor(renderer, GRID[i][j].x2, GRID[i][j].y1, GRID[i][j].x2, GRID[i][j].y2, BORDER_THICKNESS, 0xff111133);
			}

			if (GRID[i][j].Border_shown[2]) {
				thickLineColor(renderer, GRID[i][j].x1, GRID[i][j].y2, GRID[i][j].x2, GRID[i][j].y2, BORDER_THICKNESS, 0xff111133);
			}

			if (GRID[i][j].Border_shown[3]) {
				thickLineColor(renderer, GRID[i][j].x1, GRID[i][j].y1, GRID[i][j].x1, GRID[i][j].y2, BORDER_THICKNESS, 0xff111133);
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
		if (Players[i].Soldiers_count > 0)
			thickLineColor(renderer, WINDOW_PADDING_LEFT + (int)(sum / TOTAL_SOLDIERS_COUNT * WIDTH), 20 + WINDOW_PADDING_UP / 2, WINDOW_PADDING_LEFT + (int)((sum + Players[i].Soldiers_count) / TOTAL_SOLDIERS_COUNT * WIDTH), 20 + WINDOW_PADDING_UP / 2, BAR_THICKNESS, Players[i].Color | 0xff000000);
		sum += Players[i].Soldiers_count;
	}
	if (Players[0].Soldiers_count <= 0) return;
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
	polygonColor(renderer, X, Y, 4, Color ^ 0x00ffffff);
}


void print_to_game_terminal(SDL_Renderer *renderer, char *str, int row) {
	SDL_Color Color = {0x44, 0xdd, 0x66};
	SDL_Surface *Text = TTF_RenderText_Solid(proFontWindows, str, Color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, Text);
	SDL_Rect TextBox = {WINDOW_PADDING_LEFT, WINDOW_PADDING_UP + row * Text->h, Text->w, Text->h};
	SDL_RenderCopy(renderer, texture, NULL, &TextBox);
	SDL_FreeSurface(Text);
	SDL_DestroyTexture(texture);
}


void show_game(SDL_Renderer *renderer) {
	show_background(renderer);
	show_map(renderer);
	show_bar(renderer);
	show_potion(renderer, 1, 1, "S1");
//	show_potion(renderer, 2, 2, "C2");
//	schedule_deployment(GRID[5][5].Castle_x, GRID[5][5].Castle_y, GRID[4][4].Castle_x, GRID[4][4].Castle_y, GRID[5][5].Castle_ptr->Player);
	show_soldiers(renderer);
}

void show_pause(SDL_Renderer *renderer) {
	boxColor(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x99000000);
	boxColor(renderer, SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 100, SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 + 100, 0xffffffff);
	boxColor(renderer, SCREEN_WIDTH / 2 + 25, SCREEN_HEIGHT / 2 - 100, SCREEN_WIDTH / 2 + 75, SCREEN_HEIGHT / 2 + 100, 0xffffffff);
}

void show_start(SDL_Renderer *renderer) {
	char str[150];
	char prefix[2];
	prefix[0] = prefix[1] = '\0';
	if ((SDL_GetTicks() / 500) % 2) prefix[0] = '|';
	sprintf(str, "> Enter your name:");
	print_to_game_terminal(renderer, str, 0);
	sprintf(str, "> %s%s", username, prefix);
	print_to_game_terminal(renderer, str, 1);
}

void show_menu(SDL_Renderer *renderer) {
	char str[200];
	sprintf(str, "> Hello, %s!", username);
	print_to_game_terminal(renderer, str, 0);
	if (STATE == NA) {
		print_to_game_terminal(renderer, "> Welcome to the game!", 1);
	}
	else if (STATE == WIN) {
		print_to_game_terminal(renderer, "> Well done, Congratulations!", 1);
	}
	else {
		print_to_game_terminal(renderer, "> Game over!", 1);
	}
	print_to_game_terminal(renderer, ">", 2);
	sprintf(str, "> Your current score is: %d", score);
	print_to_game_terminal(renderer, str, 3);
	print_to_game_terminal(renderer, ">", 4);
	char prefix[2];
	prefix[0] = prefix[1] = '\0';
	if ((SDL_GetTicks() / 500) % 2) prefix[0] = '|';
	sprintf(str, "> Press (Q) to quit, (S) to logout, (L) to see the leaderboard and (G) to start a new game.%s", prefix);
	print_to_game_terminal(renderer, str, 5);
}

void show_leaderboard(SDL_Renderer *renderer) {
	int cnt = LEADERBOARDCNT;
	int* a = LEADERBOARDA;
	char** strs = LEADERBOARDSTRS;
	char str[130];
	for (int i = 0; i < min(10, cnt); i++) {
		sprintf(str, ">   %-70s   %10d", strs[a[i]], read_specific_user(strs[a[i]]));
		print_to_game_terminal(renderer, str, i);
	}
	if (cnt <= 10)
		print_to_game_terminal(renderer, ">", min(10, cnt));
	else
		print_to_game_terminal(renderer, ">   ...", min(10, cnt));
	for (int i = min(10, cnt) + 1; i < 15; i++) {
		print_to_game_terminal(renderer, ">", i);
	}
	char prefix[2];
	prefix[0] = prefix[1] = '\0';
	if ((SDL_GetTicks() / 500) % 2) prefix[0] = '|';
	sprintf(str, "> Press (B) to return to the main menu.%s", prefix);
	print_to_game_terminal(renderer, str, 15);
}

void show_choosemap(SDL_Renderer* renderer) {
	show_background(renderer);
	show_map(renderer);
	print_to_game_terminal(renderer, "> Press (B) to return to the main menu, or use arrow keys to transform between maps.", -3);
	print_to_game_terminal(renderer, "> Press (G) to start the game. Press one number key between 1 to 5 as number of opponents", -2);
	print_to_game_terminal(renderer, "  to make a random map, or press 0 for the number being random.", -1);
	char str[50];
	sprintf(str, "> You'll gain %d scores for win, %d for lose.", map_score() * 2, -map_score());
	print_to_game_terminal(renderer, str, -4);
	sprintf(str, "> Map number: %d", shown_map + 1);
	print_to_game_terminal(renderer, str, -5);
}

void show_randommap(SDL_Renderer* renderer) {
	show_background(renderer);
	show_map(renderer);
	print_to_game_terminal(renderer, "> Press (B) to return to the main menu, (G) to start the game, or one number key between", -2);
	print_to_game_terminal(renderer, "  0 to 5 to make another random map", -1);
	if (hasbeensaved) {
		print_to_game_terminal(renderer, "> The map has been saved.", -3);
	}
	else {
		print_to_game_terminal(renderer, "> Press (S) to save the map", -3);
	}
	char str[50];
	sprintf(str, "> You'll gain %d scores for win, %d for lose.", map_score() * 2, -map_score());
	print_to_game_terminal(renderer, str, -4);
}

void show(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0x88, 0x77, 0x77, 0xff);
	SDL_RenderClear(renderer);
	if (MODE == GAME) {
		turn();
		show_game(renderer);
		check_wl();
	}
	else if (MODE == PAUSE) {
		show_game(renderer);
		show_pause(renderer);
	}
	else if (MODE == START) {
		show_start(renderer);
	}
	else if (MODE == MENU) {
		show_menu(renderer);
	}
	else if (MODE == LEADERBOARD) {
		show_leaderboard(renderer);
	}
	else if (MODE == CHOOSEMAP) {
		show_choosemap(renderer);
	}
	else if (MODE == RANDOMMAP) {
		show_randommap(renderer);
	}
}
