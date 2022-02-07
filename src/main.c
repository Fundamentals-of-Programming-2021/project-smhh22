//besmellah
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "init.h"
#include "event_handling.h"

int main() {
//	Read_map("maps/map1.txt");

	init();

	make_random_map(-1);
	Define_global_size_variables();
//	Save_map_to_end();

	show(RENDERER);

	SDL_RenderPresent(RENDERER);

//	SDL_Window* window = SDL_CreateWindow("workshop", 20, 20, 800, 600, SDL_WINDOW_OPENGL);
//	SDL_HideWindow(window);

    int begining_of_time = SDL_GetTicks();
    while (1) {
        int start_ticks = SDL_GetTicks();

        event_handling();
		if (MODE == EXIT) break;

		show(RENDERER);

    	SDL_RenderPresent(RENDERER);

        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }

	SDL_DestroyRenderer(RENDERER);
	SDL_DestroyWindow(WINDOW);
    SDL_Quit();
	clean_game();
}
