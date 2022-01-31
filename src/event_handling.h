//besmellah

#pragma once

#include "logic.h"

int event_handling() {
	SDL_Event EVENT;
	while (SDL_PollEvent(&EVENT)) {
		if (EVENT.type == SDL_QUIT) MODE = EXIT;
	}
}
