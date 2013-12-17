#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include <SDL2/SDL.h>

#define rows 20
#define cols 10


int boxsize = 32;

char game_model[rows][cols];

char tetrominoes[7][4][4][4] = 

{
	{
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		}
	},
	{

		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
	},
	{
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 1},
			{0, 1, 1, 1},
			{0, 0, 0, 0}
		}
	},
	{
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 0, 0, 0},
			{1, 1, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{0, 0, 1, 0}
		},
	},
	{
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 1},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 1},
			{0, 0, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0}
		}
	},
	{
		{	
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0}
		},
		{	
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		},
		{	
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0}
		},
		{	
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		},
	},
	{
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		}
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

int current_rotation;


static void clear_board () {
	memset (game_model, 0, rows*cols);		
}


static void choose_random_piece () {
	current_piece = rand() % 8;
	current_piece = 3;
	current_rotation = 0;
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
			SDL_FillRect(surface, &rect, 0xffF82640);
		}
	}
}

static void draw_model (SDL_Surface *surface) {
	for (int row=0; row<rows; row++) {
		for (int col=0; col<cols; col++) {

			if (game_model[row][col]) {

			SDL_Rect board_block;
			board_block.y = row * boxsize;
			board_block.x = col * boxsize;
			board_block.h = boxsize;
			board_block.w = boxsize;

			SDL_FillRect(surface, &board_block, 0xff66D9EF);

			}

		}
	}
}


void print_board () {
	printf("%s\n", "board start: ");
	for (int row=0; row<rows; row++) {
		for (int col=0; col<cols; col++) {
			printf("%d", game_model[row][col]);
		}
		printf("\n");
	}
	printf("%s\n", "board end: ");

}

static void draw_screen () {
	// clear screen
	SDL_FillRect(surface, &clear_screen_rect, 0);		

	SDL_FillRect(surface, &board, 0xff272822);		

	draw_tetromino(surface, piecex * boxsize, piecey * boxsize, tetrominoes[current_piece][current_rotation]);
	draw_model(surface);
	
	// render screen
	SDL_UpdateTexture(sdl_texture, NULL, surface->pixels, surface->pitch);
	SDL_RenderCopy(renderer, sdl_texture, NULL, NULL);
	SDL_RenderPresent(renderer);		
}


static void clear_full_rows () {
	int row_offset = 0;
	for (int row=rows-1; row >= 0; row--) {

		int full = 1;
		for (int col=0; col<cols; col++) {
			if (!game_model[row][col]) {
				full = 0;
			}

			game_model[(row + row_offset)][col] = game_model[row][col]; 
		}
		row_offset += full;
	}

	for (int row=0; row<row_offset; row++) {
		memset (game_model, 0, row_offset*cols);		
	}
}


static int piece_collision () {
	for (int piece_row=0; piece_row<4; piece_row++) {
		for (int piece_col=0; piece_col<4; piece_col++) {
			if (tetrominoes[current_piece][current_rotation][piece_row][piece_col]) {
				int row = piece_row + piecey;
				int col = piece_col + piecex;

				if (row >= rows || row < 0 || col < 0 || col >= cols) {
					continue;
				}

				if (game_model[row][col]) {
					return 1;
				}
				
			}
		}
	}

	return 0;
}

#define max 10

int drop_countdown = max;

static void finish_piece () {
	for (int row=0; row<4; row++) {
		for (int col=0; col<4; col++) {
			int block = tetrominoes[current_piece][current_rotation][row][col];


			int absolute_row = row + piecey;
			int absolute_col = col + piecex;

			if (absolute_row >= rows || absolute_row < 0 || absolute_col < 0 || absolute_col >= cols) {
				continue;
			}

			if (block) {
				game_model[absolute_row][absolute_col] = 1;
			}
		}
	}

	clear_full_rows();
	choose_random_piece();

}

static int move_piece (int x, int y) {
	int old_x = piecex;
	int old_y = piecey;

	piecex += x;
	piecey += y;

	if (piece_collision()) {

		piecex = old_x;
		piecey = old_y;

		if (y) {
			finish_piece();
			return 1;
		}

		return 0;
	}

	for (int row=0; row<4; row++) {
		for (int col=0; col<4; col++) {

			if (!tetrominoes[current_piece][current_rotation][row][col]) {
				continue;
			}

			if (piecex + col < 0) {
				piecex = old_x;
				piecey = old_y;
				return 0;
			}

			if (piecex + col >= cols) {
				piecex = old_x;
				piecey = old_y;
				return 0;
			}

			if (piecey + row >= rows) {
				piecey = old_y;
				finish_piece();
				return 1;
			}


		}
	}

	return 0;

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
						current_rotation = (current_rotation + 1) % 4;
						break;

					case SDLK_DOWN:
						move_piece(0, 1);
						break;

					case SDLK_SPACE:
						while (!move_piece(0, 1)) {}
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
	clear_board();

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



	