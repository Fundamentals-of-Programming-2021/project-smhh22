//besmellah

#pragma once

#include "header.h"
#include "logic.h"

float deployment_value(CASTLE*, CASTLE*);

void ai_for_castle(CASTLE*);
void do_ai();

float deployment_value(CASTLE *Origin, CASTLE *Dest) {
	if (Dest->Player == Players + 1 || Origin->Soldiers_count < 20) return inf;
	int mxo = Origin->x;
	int myo = Origin->y;
	int mxd = Dest->x;
	int myd = Dest->y;
	float dist = sqrt((mxo - mxd) * (mxo - mxd) + (myo - myd) * (myo - myd));
	float ans = dist + 2 * Dest->Soldiers_count + (Dest->Player == Players + 2) * 10 - (Dest->Player == Players) * 50;
	return ans;
}

void ai_for_castle(CASTLE *Origin) {
	float mn = inf;
	CASTLE *Dest = Origin;
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (CASTLE_PTRS[i][j] != NULL && CASTLE_PTRS[i][j] != Origin) {
				float val = deployment_value(Origin, CASTLE_PTRS[i][j]);
				if (val < mn) {
					mn = val;
					Dest = CASTLE_PTRS[i][j];
				}
			}
		}
	}
	if (mn < 200)
		schedule_deployment(Origin->x, Origin->y, Dest->x, Dest->y, Origin->Player);
}

void do_ai() {
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			if (CASTLE_PTRS[i][j] == NULL || CASTLE_PTRS[i][j]->Player - Players <= 2) continue;
			ai_for_castle(CASTLE_PTRS[i][j]);
		}
	}
}
