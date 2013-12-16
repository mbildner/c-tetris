#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <SDL2/SDL.h>






int main (int argc, char *argv[]) {
	int windowWidth = 800;
	int windowHeight = 800;

	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Event event;

	SDL_Window *window;

	window = SDL_CreateWindow(
		"This is our motherfucking title",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth,
		windowHeight,
		0
		);

	assert(window);

	SDL_Renderer *renderer;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture *sdl_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

	assert(sdl_texture);

	SDL_Surface *surface = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32,
			0x00FF0000,
         	0x0000FF00,
            0x000000FF,
            0xFF000000);

	if (!surface) {
		printf("%s\n", SDL_GetError());
		return -1;
	}


	SDL_Rect clear_screen_rect;
	clear_screen_rect.x = 0;
	clear_screen_rect.y = 0;
	clear_screen_rect.w = windowWidth;
	clear_screen_rect.h = windowHeight;

	SDL_Rect pretty_rect;
	pretty_rect.x = 10;
	pretty_rect.y = 10;
	pretty_rect.w = 100;
	pretty_rect.h = 100;

	const int speed = 5;


	int running = 1;
	while (running) {
		// take input
		while ( SDL_PollEvent( &event ) ) {
			switch ( event.type ) {
				case SDL_KEYDOWN:
					break;

				case SDL_QUIT:
					running = 0;
					break;

				default:
					break;

			}
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_LEFT]) {
			pretty_rect.x -= speed;

		}

		if (state[SDL_SCANCODE_RIGHT]) {
			pretty_rect.x += speed;

		}

		if (state[SDL_SCANCODE_UP]) {
			pretty_rect.y -= speed;

		}

		if(state[SDL_SCANCODE_DOWN]) {
			pretty_rect.y += speed;
		}

		// clear screen
		SDL_FillRect(surface, &clear_screen_rect, 0);		
		SDL_FillRect(surface, &pretty_rect, 0xffffffff);		



		// render screen
		SDL_UpdateTexture(sdl_texture, NULL, surface->pixels, surface->pitch);
		SDL_RenderCopy(renderer, sdl_texture, NULL, NULL);
		SDL_RenderPresent(renderer);		
	}



	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}



	