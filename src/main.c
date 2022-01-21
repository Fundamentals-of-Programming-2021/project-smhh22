//besmellah
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "init.h"

const int step = 5;
void moveCircle(SDL_Keycode key, double* snake_x, double* snake_y) {
	switch (key) {
		case SDLK_UP:
			*snake_y -= step;
			break;
		case SDLK_DOWN:
			*snake_y += step;
			break;
		case SDLK_RIGHT:
			*snake_x += step;
			break;
		case SDLK_LEFT:
			*snake_x -= step;
			break;
	}
}

bool hasEatenFood(double snake_x, double snake_y, double food_x, double food_y, double radius, double rx, double ry) {
	double distance = sqrt(pow(snake_x - food_x, 2) + pow(snake_y - food_y, 2));
	return distance < radius + (rx + ry) / 2;
}

void changeFoodLocation(double * food_x, double * food_y) {
	*food_x = rand() % 600 + 100;
	*food_y = rand() % 400 + 100;
}

const int EXIT = 12345;
int handleEvents(double* snake_x, double* snake_y) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    	if (event.type == SDL_QUIT)
    	    return EXIT;
    	if (event.type == SDL_KEYDOWN)
    		moveCircle(event.key.keysym.sym , snake_x, snake_y);
    }
}

int main() {
	double snake_x = 100;
	double snake_y = 100;
	double snake_radius = 20;
    int snake_score = 0;

	double food_x = 300;
	double food_y = 300;
	double food_rx = 15;
	double food_ry = 10;

	Read_map("maps/map0.txt");
	init();
	Define_global_size_variables();

	HEAD = (DEPLOYED_SOLDIER*)malloc(sizeof(DEPLOYED_SOLDIER));
	HEAD->x = 500;
	HEAD->y = 500;
	HEAD->nxt = HEAD->prv = NULL;
	HEAD->Player = Players + 1;
	
	show_sample(RENDERER);

	SDL_RenderPresent(RENDERER);
//	SDL_Delay(10000);

//	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("workshop", 20, 20, 800, 600, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int begining_of_time = SDL_GetTicks();
    const double FPS = 60;
    while (1) {
        int start_ticks = SDL_GetTicks();

        if (handleEvents(&snake_x, &snake_y) == EXIT) break;

    	SDL_SetRenderDrawColor(renderer, 120, 60, 80, 255);
    	SDL_SetRenderDrawColor(RENDERER, 0xdd, 0xdd, 0xdd, 0xff);
    	SDL_RenderClear(renderer);
    	SDL_RenderClear(RENDERER);

    	if (hasEatenFood(snake_x, snake_y, food_x, food_y, snake_radius, food_rx, food_ry)) {
    	   	snake_radius *= 1.2;
            snake_score++;
    	   	changeFoodLocation(&food_x, &food_y);
    	}

    	filledCircleRGBA(renderer, snake_x, snake_y, snake_radius, 0, 100, 100, 255);
    	filledEllipseRGBA(renderer, food_x, food_y, food_rx, food_ry, rand() % 255, rand() % 255, rand() % 255, 255);
        char* buffer = (char*)malloc(sizeof(char) * 50);
        sprintf(buffer, "score: %d   elapsed time: %dms", snake_score, start_ticks - begining_of_time);
        printf("%s", buffer);
        stringRGBA(renderer, 5, 5, buffer, 0, 0, 0, 255);

		show_sample(RENDERER);

    	SDL_RenderPresent(renderer);
    	SDL_RenderPresent(RENDERER);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_DestroyWindow(WINDOW);
    SDL_Quit();
    return 0;
}
