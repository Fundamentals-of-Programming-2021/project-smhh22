//besmellah
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "init.h"
#include "event_handling.h"

void moveCircle(SDL_Keycode key) {
	switch (key) {
		case SDLK_UP:
			break;
		case SDLK_DOWN:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_LEFT:
			break;
	}
}

int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    	if (event.type == SDL_KEYDOWN)
    		moveCircle(event.key.keysym.sym);
    }
}

int main() {
//	Read_map("maps/map1.txt");

	init();

	make_random_map(-1);
	Define_global_size_variables();
//	Save_map_to_end();

	add_soldier(500, 500, 1, -1, 1, 2, 2);
	add_soldier(600, 600, 0.5, -1, 2, 2, 2);
	
	show_sample(RENDERER);

	SDL_RenderPresent(RENDERER);

//	SDL_Window* window = SDL_CreateWindow("workshop", 20, 20, 800, 600, SDL_WINDOW_OPENGL);
//	SDL_HideWindow(window);
    SDL_Renderer* renderer = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

    int begining_of_time = SDL_GetTicks();
    const double FPS = 60;
    while (1) {
        int start_ticks = SDL_GetTicks();

        event_handling();
		if (MODE == EXIT) break;

    	SDL_SetRenderDrawColor(renderer, 120, 60, 80, 255);
    	SDL_SetRenderDrawColor(RENDERER, 0xee, 0xdd, 0xdd, 0xff);
    	SDL_RenderClear(renderer);
    	SDL_RenderClear(RENDERER);

		show_sample(RENDERER);

    	SDL_RenderPresent(RENDERER);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

    SDL_DestroyRenderer(renderer);
	SDL_DestroyRenderer(RENDERER);
//	SDL_DestroyWindow(window);
	SDL_DestroyWindow(WINDOW);
    SDL_Quit();
    return 0;
}
