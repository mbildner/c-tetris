#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


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
		{0, 0, 0, 0},
		{0, 0, 1, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0}
	}
};


int current_piece = 1;

SDL_Rect clear_screen_rect;
SDL_Surface *surface;
SDL_Rect board;

SDL_Renderer *renderer;


SDL_Texture *sdl_texture;

int piecex = 3;
int piecey = 0;

int running = 1;

static void choose_random_piece () {
	current_piece = rand() % 8;
	piecex = 3;
	piecey = 0;
}

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


static void draw_screen () {
	// clear screen
	SDL_FillRect(surface, &clear_screen_rect, 0);		
	SDL_FillRect(surface, &board, 0xff990099);		
	draw_tetromino(surface, piecex * boxsize, piecey * boxsize, tetrominoes[current_piece]);
	
	// render screen
	SDL_UpdateTexture(sdl_texture, NULL, surface->pixels, surface->pitch);
	SDL_RenderCopy(renderer, sdl_texture, NULL, NULL);
	SDL_RenderPresent(renderer);		
}

#define max 10

int drop_countdown = max;

static void finish_piece () {
	choose_random_piece();
}

static void move_piece (int x, int y) {
	piecex += x;
	piecey += y;

	for (int row=0; row<4; row++) {
		for (int col=0; col<4; col++) {
			if (!tetrominoes[current_piece][row][col]) {
				continue;
			}
			if (piecex + col < 0) {
				piecex -= x;				
			}
			if (piecex + col >= cols) {
				piecex -= x;
			}
			if (piecey + row >= rows) {
				piecey -= y;
				finish_piece();
			}
		}
	}

}


static void update () {
	if (!drop_countdown) {
		move_piece(0, 1);
		drop_countdown = max;
	}
	drop_countdown -= 1;

}

static void flush_events () {
	SDL_Event event;

	while ( SDL_PollEvent( &event ) ) {
		switch ( event.type ) {
			case SDL_KEYDOWN:
				switch ( event.key.keysym.sym ) {
					case SDLK_LEFT:
						move_piece(-1, 0);
						break;

					case SDLK_RIGHT:
						move_piece(1, 0);
						break;

					case SDLK_UP:
						// piecey -= 1;
						break;

					case SDLK_DOWN:
						move_piece(0, 1);
						break;

					case SDLK_SPACE:
						break;
				}

				break;

			case SDL_QUIT:
				running = 0;
				break;

			default:
				break;

		}
	}
}

int main (int argc, char *argv[]) {
	srand (time(NULL));
	int windowWidth = 800;
	int windowHeight = 800;

	SDL_Init(SDL_INIT_VIDEO);
	
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


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	sdl_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

	assert(sdl_texture);

	surface = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32,
			0x00FF0000,
         	0x0000FF00,
            0x000000FF,
            0xFF000000);

	if (!surface) {
		printf("%s\n", SDL_GetError());
		return -1;
	}



	clear_screen_rect.x = 0;
	clear_screen_rect.y = 0;

	clear_screen_rect.w = windowWidth;
	clear_screen_rect.h = windowHeight;

	int board_width = boxsize * cols;
	int board_height = boxsize * rows;

	board.x = 0;
	board.y = 0;
	board.w = board_width;
	board.h = board_height;

	const int speed = 1;

	choose_random_piece();

	while (running) {
		// take input
		flush_events();
		update();
		draw_screen();
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}



	