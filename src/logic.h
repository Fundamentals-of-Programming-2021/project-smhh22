//besmellah

#pragma once

#include "header.h"

void soldiers_motion();
void add_soldier(float, float, float, float, int, int, int);
void remove_soldier(DEPLOYED_SOLDIER*);
void schedule_deployment(int ox, int oy, int dx, int dy, int p);

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
	CASTLE_PTRS[ox][oy]->Deployment_dest = CASTLE_PTRS[dx][dy];
	CASTLE_PTRS[ox][oy]->Deployer = Players + p;
	CASTLE_PTRS[ox][oy]->to_be_deployed = CASTLE_PTRS[ox][oy]->Soldiers_count;
}
