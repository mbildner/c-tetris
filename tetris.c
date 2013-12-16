#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <SDL2/SDL.h>




int main (int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Event event;

	SDL_Window *window;

	window = SDL_CreateWindow(
		"This is our motherfucking title",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800,
		800,
		0
		);

	assert(window);

	int running = 1;

	while (running) {
		while ( SDL_PollEvent( &event ) ) {
			switch ( event.type ) {
				case SDL_KEYDOWN:
					printf ("key: %d\n", event.key.keysym.sym);
					break;

				case SDL_KEYUP:
					break;

				case SDL_QUIT:
					running = 0;

				default:
					printf("nope\n");
					break;

			} 
		}
	}



	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}




