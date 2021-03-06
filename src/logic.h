//besmellah

#pragma once

#include "AI.h"
#include "users.h"
#include "event_handling.h"

int map_score();
int check_soldier_potion(int, int);
void soldiers_motion();
void add_soldier(float, float, float, float, int, int, int);
void remove_soldier(DEPLOYED_SOLDIER*);
void remove_all_soldiers();
void schedule_deployment(int, int, int, int, PLAYER*);
void deploy_all();
void product_soldiers();
void collision_check();
void check_wl();
void potion_check();
void add_potion();
void turn();

int map_score() {
	return NUMBER_OF_PLAYERS * NUMBER_OF_PLAYERS * 100 + GRID_WIDTH * GRID_HEIGHT;
}

int check_soldier_potion(int x, int y) {
	int cx = (x - WINDOW_PADDING_LEFT) / CELL_WIDTH;
	int cy = (y - WINDOW_PADDING_UP) / CELL_HEIGHT;
	int mx = (GRID[cx][cy].x1 + GRID[cx][cy].x2) / 2;
	int my = (GRID[cx][cy].y1 + GRID[cx][cy].y2) / 2;
	return abs(x - mx) + abs(y - my) <= CASTLE_SIZE / 2 + SOLDIER_SIZE;
}

void soldiers_motion() {
	DEPLOYED_SOLDIER *cur = HEAD;
	while (cur != NULL) {
		cur->x += cur->vx;
		cur->y += cur->vy;
		if (cur->Player->Potion_enabled == 0) {
			cur->x += cur->vx;
			cur->y += cur->vy;
		}
		else if (cur->Player->Potion_enabled == -1 && enabledpotion == 1) {
			cur->x -= cur->vx;
			cur->y -= cur->vy;
		}

		if (check_soldier_potion((int)(cur->x), (int)(cur->y))) {
			int cx = ((int)(cur->x) - WINDOW_PADDING_LEFT) / CELL_WIDTH;
			int cy = ((int)(cur->y) - WINDOW_PADDING_UP) / CELL_HEIGHT;
			if (!isCandid[cx][cy]) {
				if (CASTLE_PTRS[cx][cy] == NULL) {
					isCandid[cx][cy] = 1;
					TUPLE NEW;
					NEW.x1 = cx;
					NEW.x2 = cy;
					Candids[Candidcnt++] = NEW;
				}
			}
			else if (~shownpotion && xpotion == cx && ypotion == cy) {
				enabledpotion = shownpotion;
				enabledpotion = cur->Player->Potion_enabled = shownpotion;
				cur->Player->Potion_start = SDL_GetTicks();
				shownpotion = -1;
			}
		}
		int mx = (GRID[cur->Dest->x][cur->Dest->y].x1 + GRID[cur->Dest->x][cur->Dest->y].x2) / 2;
		int my = (GRID[cur->Dest->x][cur->Dest->y].y1 + GRID[cur->Dest->x][cur->Dest->y].y2) / 2;
		if ((int)(fabs(cur->x - mx)) <= CASTLE_SIZE / 2 && (int)(fabs(cur->y - my)) <= CASTLE_SIZE / 2) {
			DEPLOYED_SOLDIER *tmp = cur->nxt;
			if (cur->Dest->Player == cur->Player) {
				cur->Dest->Soldiers_count++;
			}
			else if (cur->Dest->Soldiers_count <= 0) {
				cur->Dest->Soldiers_count++;
				cur->Dest->Player = cur->Player;
			}
			else {
				cur->Dest->Soldiers_count--;
				cur->Dest->Player->Soldiers_count--;
				cur->Player->Soldiers_count--;
				TOTAL_SOLDIERS_COUNT -= 2;
			}
			remove_soldier(cur);
			cur = tmp;
		}
		else
			cur = cur->nxt;
	}
}

void add_soldier(float x, float y, float vx, float vy, int p, int dx, int dy) {
	DEPLOYED_SOLDIER *NEW = (DEPLOYED_SOLDIER*)malloc(sizeof(DEPLOYED_SOLDIER));
	NEW->Player = Players + p;
	NEW->Dest = CASTLE_PTRS[dx][dy];
	NEW->x = x;
	NEW->y = y;
	NEW->vx = vx;
	NEW->vy = vy;
	NEW->nxt = HEAD;
	NEW->prv = NULL;
	if (HEAD != NULL) HEAD->prv = NEW;
	HEAD = NEW;
}

void remove_soldier(DEPLOYED_SOLDIER *cur) {
	if (cur == NULL) return;
	if (cur->prv != NULL)
		cur->prv->nxt = cur->nxt;
	else
		HEAD = cur->nxt;
	if (cur->nxt != NULL)
		cur->nxt->prv = cur->prv;
	free(cur);
}

void remove_all_soldiers() {
	DEPLOYED_SOLDIER *cur = HEAD;
	while (cur != NULL) {
		DEPLOYED_SOLDIER *tmp = cur;
		cur = cur->nxt;
		remove_soldier(tmp);
	}
}

void schedule_deployment(int ox, int oy, int dx, int dy, PLAYER* p) {
	CASTLE_PTRS[ox][oy]->Deployment_dest_x = dx;
	CASTLE_PTRS[ox][oy]->Deployment_dest_y = dy;
	CASTLE_PTRS[ox][oy]->Deployer = p;
	CASTLE_PTRS[ox][oy]->to_be_deployed = CASTLE_PTRS[ox][oy]->Soldiers_count;
}

void deploy_all() {
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (CASTLE_PTRS[i][j] == NULL)
				continue;
			CASTLE_PTRS[i][j]->to_be_deployed = min(CASTLE_PTRS[i][j]->to_be_deployed, CASTLE_PTRS[i][j]->Soldiers_count);
			if (CASTLE_PTRS[i][j]->to_be_deployed <= 0)
				continue;
			if (SDL_GetTicks() - CASTLE_PTRS[i][j]->last_deploy < 1000/ DEPLOYMENT_RATE)
				continue;
			if (CASTLE_PTRS[i][j]->Deployer != CASTLE_PTRS[i][j]->Player) {
				CASTLE_PTRS[i][j]->to_be_deployed = 0;
				continue;
			}
			int di = CASTLE_PTRS[i][j]->Deployment_dest_x;
			int dj = CASTLE_PTRS[i][j]->Deployment_dest_y;

			float ox = (GRID[i][j].x1 + GRID[i][j].x2) / 2.0;
			float oy = (GRID[i][j].y1 + GRID[i][j].y2) / 2.0;
			float dx = (GRID[di][dj].x1 + GRID[di][dj].x2) / 2.0;
			float dy = (GRID[di][dj].y1 + GRID[di][dj].y2) / 2.0;
			float vx = SOLDIERS_SPEED * (dx - ox) / sqrt((dx - ox) * (dx - ox) + (dy - oy) * (dy - oy));
			float vy = SOLDIERS_SPEED * (dy - oy) / sqrt((dx - ox) * (dx - ox) + (dy - oy) * (dy - oy));
			add_soldier(ox, oy, vx, vy, CASTLE_PTRS[i][j]->Player-Players, di, dj);
			CASTLE_PTRS[i][j]->Soldiers_count--;
			CASTLE_PTRS[i][j]->to_be_deployed--;
			CASTLE_PTRS[i][j]->to_be_deployed = min(CASTLE_PTRS[i][j]->to_be_deployed, CASTLE_PTRS[i][j]->Soldiers_count);
			CASTLE_PTRS[i][j]->last_deploy = SDL_GetTicks();
		}
	}
}

void product_soldiers() {
	int time = SDL_GetTicks();
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (CASTLE_PTRS[i][j] == NULL || CASTLE_PTRS[i][j]->Player - Players <= 1) continue;
			int RATE = PRODUCTION_RATE;
			if (CASTLE_PTRS[i][j]->Player->Potion_enabled == 3) {
				RATE *= 2;
			}
			if (time - CASTLE_PTRS[i][j]->last_production < 1000 / RATE) continue;
			CASTLE_PTRS[i][j]->last_production = time;
			if (CASTLE_PTRS[i][j]->Soldiers_count < MAX_PRODUCTIVE_SOLDIERS || CASTLE_PTRS[i][j]->Player->Potion_enabled == 2) {
				CASTLE_PTRS[i][j]->Soldiers_count++;
				CASTLE_PTRS[i][j]->Player->Soldiers_count++;
				TOTAL_SOLDIERS_COUNT++;
			}
		}
	}
}

void collision_check() {
	for (int i = 0; i <= WIDTH; i++) {
		memset(collision_table[i], 0, sizeof(int) * (HEIGHT + 1));
	}
	DEPLOYED_SOLDIER *cur = HEAD;
	while (cur != NULL) {
		int x = cur->x;
		int y = cur->y;
		for (int i = x - SOLDIER_SIZE; i <= x + SOLDIER_SIZE; i++) {
			for (int j = y - SOLDIER_SIZE + abs(i - x); j <= y + SOLDIER_SIZE - abs(i - x); j++) {
				collision_table[i - WINDOW_PADDING_LEFT][j - WINDOW_PADDING_UP] |= 1 << (cur->Player - Players);
			}
		}
		cur = cur->nxt;
	}
	cur = HEAD;
	while (cur != NULL) {
		int x = cur->x;
		int y = cur->y;
		int f = 1 << (cur->Player - Players);
		for (int i = x - SOLDIER_SIZE; i <= x + SOLDIER_SIZE; i++) {
			for (int j = y - SOLDIER_SIZE + abs(i - x); j <= y + SOLDIER_SIZE - abs(i - x); j++) {
				f |= collision_table[i - WINDOW_PADDING_LEFT][j - WINDOW_PADDING_UP];
				if (f ^ (1 << (cur->Player - Players))) break;
			}
			if (f ^ (1 << (cur->Player - Players))) break;
		}
		if (f ^ (1 << (cur->Player - Players))) {
			DEPLOYED_SOLDIER *tmp = cur;
			tmp->Player->Soldiers_count--;
			TOTAL_SOLDIERS_COUNT--;
			cur = cur->nxt;
			remove_soldier(tmp);
		}
		else cur = cur->nxt;
	}
}

void check_wl() {
//	printf("%d\n", Players[2].Soldiers_count);
	if (Players[2].Soldiers_count <= 0) {
		STATE = LOSE;
		score -= map_score();
		clean_game();
		MODE = MENU;
		save_user();
	}
	else if (Players[2].Soldiers_count + Players[0].Soldiers_count == TOTAL_SOLDIERS_COUNT) {
		score += 2 * map_score();
		STATE = WIN;
		clean_game();
		MODE = MENU;
		save_user();
	}
}

void potion_check() {
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
		int time = SDL_GetTicks();
		if (Players[i].Potion_enabled == -1) continue;
		if (time - Players[i].Potion_start > 1000 * effectivetime[Players[i].Potion_enabled]) {
			Players[i].Potion_enabled = Players[i].Potion_start = -1;
			enabledpotion = -1;

		}
	}
}

void add_potion() {
	if (~enabledpotion || ~shownpotion || !Candidcnt) return;
	if (rand() % (int)(FPS * 30)) return;
	shownpotion = rand() % 4;
	int idx = rand() % Candidcnt;
	xpotion = Candids[idx].x1;
	ypotion = Candids[idx].x2;
}

void turn() {
	product_soldiers();
	soldiers_motion();
	do_ai();
	deploy_all();
	collision_check();
	potion_check();
	add_potion();
}
