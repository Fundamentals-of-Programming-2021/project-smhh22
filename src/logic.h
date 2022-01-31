//besmellah

#pragma once

#include "header.h"

void soldiers_motion();
void add_soldier(float, float, float, float, int, int, int);
void remove_soldier(DEPLOYED_SOLDIER*);
void schedule_deployment(int, int, int, int, int);

void soldiers_motion() {
	DEPLOYED_SOLDIER *cur = HEAD;
	while (cur != NULL) {
		cur->x += cur->vx;
		cur->y += cur->vy;
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

void schedule_deployment(int ox, int oy, int dx, int dy, int p) {
	CASTLE_PTRS[ox][oy]->Deployment_dest_x = dx;
	CASTLE_PTRS[ox][oy]->Deployment_dest_y = dy;
	CASTLE_PTRS[ox][oy]->Deployer = Players + p;
	CASTLE_PTRS[ox][oy]->to_be_deployed = CASTLE_PTRS[ox][oy]->Soldiers_count;
}

void deploy_all() {
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (CASTLE_PTRS[i][j] == NULL)
				continue;
			if (!CASTLE_PTRS[i][j]->to_be_deployed)
				continue;
			if (SDL_GetTicks() - CASTLE_PTRS[i][j]->last_deploy < 1000/ DEPLOYMENT_RATE)
				continue;
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
