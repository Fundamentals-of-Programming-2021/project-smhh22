//besmellah

#pragma once

#include "header.h"

void read_user();
void save_user();

int read_specific_user(char*);

void user_sort(char** strs, int* a, int cnt);

void read_user() {
	char filename[110];
	sprintf(filename, "users/%s.txt", username);
	FILE *file = fopen(filename, "r");
	if (file != NULL) {
		fscanf(file, "%d", &score);
		fclose(file);
	}
}

void save_user() {
	char filename[110];
	sprintf(filename, "users/%s.txt", username);
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		file = fopen("users/users", "a");
		fprintf(file, "%s\n", username);
	}
	fclose(file);
	file = fopen(filename, "w");
	fprintf(file, "%d\n", score);
	fclose(file);
}


int read_specific_user(char *str) {
	char filename[110];
	sprintf(filename, "users/%s.txt", str);
	int ans;
	FILE *file = fopen(filename, "r");
	fscanf(file, "%d", &ans);
	fclose(file);
	return ans;
}


void user_sort(char** strs, int* a, int cnt) {
	for (int t = 0; t < cnt; t++) {
		for (int i = t; i < cnt - 1; i++) {
			if (read_specific_user(strs[a[i]]) > read_specific_user(strs[a[i + 1]])) {
				a[cnt] = a[i];
				a[i] = a[i + 1];
				a[i + 1] = a[cnt];
			}
		}
	}
}
