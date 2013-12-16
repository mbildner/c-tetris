#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <SDL2/SDL.h>

#define rows 20
#define cols 10


int boxsize = 32;

char game_model[rows][cols] = {0};

char tetrominoes[7][4][4] = {
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 1, 0},
		{0, 1, 1, 1},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 1, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0, 0}
	}
};


int piecex = 0;
int piecey = 0;



static void draw_tetromino (SDL_Surface *surface, int x, int y, char tetromino[4][4]) {
	for (int row=0; row<4; row++) {
		for (int col=0; col<4; col++) {
			if (!tetromino[row][col]) {
				continue;
			}

			SDL_Rect rect;
			rect.x = x + (boxsize * col);
			rect.y = y + (boxsize * row);
			rect.w = boxsize;
			rect.h = boxsize;
			SDL_FillRect(surface, &rect, 0xff797800);
		}
	}
}


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

	int board_width = boxsize * cols;
	int board_height = boxsize * rows;

	SDL_Rect board;
	board.x = 0;
	board.y = 0;
	board.w = board_width;
	board.h = board_height;

	const int speed = 1;

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
			piecex -= speed;

		}

		if (state[SDL_SCANCODE_RIGHT]) {
			piecex += speed;

		}

		if (state[SDL_SCANCODE_UP]) {
			piecey -= speed;

		}

		if(state[SDL_SCANCODE_DOWN]) {
			piecey += speed;
		}

		// clear screen
		SDL_FillRect(surface, &clear_screen_rect, 0);		
		SDL_FillRect(surface, &board, 0xff990099);		
		draw_tetromino(surface, piecex * boxsize, piecey * boxsize, tetrominoes[2]);

		// render screen
		SDL_UpdateTexture(sdl_texture, NULL, surface->pixels, surface->pitch);
		SDL_RenderCopy(renderer, sdl_texture, NULL, NULL);
		SDL_RenderPresent(renderer);		
	}



	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}



	