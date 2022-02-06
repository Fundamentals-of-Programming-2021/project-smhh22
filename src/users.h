//besmellah

#pragma once

#include "header.h"

void read_user();
void save_user();

void read_user() {
	char filename[110];
	sprintf(filename, "%s.txt", username);
	FILE *file = fopen(filename, "r");
	if (file != NULL) {
		fscanf(file, "%d", &score);
		fclose(file);
	}
}

void save_user() {
	char filename[110];
	sprintf(filename, "%s.txt", username);
	FILE *file = fopen(filename, "w");
	fprintf(file, "%d", score);
	fclose(file);
}
