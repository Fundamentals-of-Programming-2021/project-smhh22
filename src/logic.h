//besmellah

#pragma once

#include "AI.h"

void soldiers_motion();
void add_soldier(float, float, float, float, int, int, int);
void remove_soldier(DEPLOYED_SOLDIER*);
void remove_all_soldiers();
void schedule_deployment(int, int, int, int, PLAYER*);
void deploy_all();
void product_soldiers();
void collision_check();
void turn();

void soldiers_motion() {
	DEPLOYED_SOLDIER *cur = HEAD;
	while (cur != NULL) {
		cur->x += cur->vx;
		cur->y += cur->vy;
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
	if (time - last_production < 1000 / PRODUCTION_RATE) return;
	last_production = time;
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (CASTLE_PTRS[i][j] == NULL || CASTLE_PTRS[i][j]->Player == Players + 1) continue;
			if (CASTLE_PTRS[i][j]->Soldiers_count < MAX_PRODUCTIVE_SOLDIERS) {
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

void turn() {
	product_soldiers();
	soldiers_motion();
	do_ai();
	deploy_all();
	collision_check();
}
