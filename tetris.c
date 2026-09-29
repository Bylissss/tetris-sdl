#include "SDL3/SDL.h"
#include "stdio.h"

#include "tetris_blocks.h"

// GLOBALS

SDL_Window* window;
SDL_Renderer* renderer;
SDL_DisplayMode* mode;
SDL_Event event;

int score = 0;
char score_str[32];

int display_width;
int display_height;

int *current_block = box;

#define WINDOW_WIDTH 540
#define WINDOW_HEIGHT 960

SDL_FPoint borders[4] = { { WINDOW_WIDTH / 10 , WINDOW_HEIGHT / 10 }, 
						  { WINDOW_WIDTH / 10 , WINDOW_HEIGHT / 10 * 9 } ,
						  { WINDOW_WIDTH / 10 * 9 , WINDOW_HEIGHT / 10 * 9 },
						  { WINDOW_WIDTH / 10 * 9 , WINDOW_HEIGHT / 10  }
 };


int grid[10][20] = {1};
SDL_FRect rect[10][20] = {0};

int state = 0; // NONE
// ENUMS

typedef enum tetris_states{
	NONE = 0,
	GAME_BEGIN,
	BLOCK_CHECK,
	BLOCK_FALLING,
	PAUSE,
	GAME_OVER,
	QUIT
	
}tetris_states;

// FUNCTIONS

void grid_to_rects(){
	for (int i = 0; i < SDL_arraysize(grid) ; i++){
		for(int j = 0; j < SDL_arraysize(grid[j]) ; j++){
			//SDL_Log("%d %d %d", SDL_arraysize(grid[j]), i, j);
			rect[i][j].x =  WINDOW_WIDTH / 15 * (i + 2.5f) ;
			rect[i][j].y =  WINDOW_WIDTH / 15 * (j + 3);
			rect[i][j].h =  WINDOW_WIDTH / 15 - 4;
			rect[i][j].w =  WINDOW_WIDTH / 15 - 4;
		}
	}
}

void update_score(){
	snprintf(score_str, sizeof(score_str), "%d", score);

}

void window_to_center(SDL_Window* window){
	SDL_SetWindowPosition(window, display_width/2 - WINDOW_WIDTH / 2, display_height/2 - WINDOW_HEIGHT/2 );
}

void tetris_deinit(){
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void window_init(){
	window = SDL_CreateWindow("tetris", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if(!window){
		SDL_Log("Window Init failed! exiting");
		tetris_deinit();
	}

	mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
	if(!mode){
		SDL_Log("Getting display mode failed! exiting");
		tetris_deinit();
	}

	display_width = mode->w;
	display_height = mode->h;
	
	window_to_center(window);
}

void renderer_init(){
	renderer = SDL_CreateRenderer(window, NULL);
	if(!renderer){
		SDL_Log("Renderer Init failed! exiting");
		tetris_deinit();
	}
}

void tetris_init(){
	state = GAME_BEGIN;

	window_init();
	renderer_init();
	
}

void logic_init(){

}

void logic_loop(){
	update_score();
	grid_to_rects();
}

void render_loop(){

	SDL_SetRenderVSync(renderer, 1);

	// Background
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// Score

	SDL_SetRenderScale(renderer, 4.0f, 4.0f);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDebugText(renderer, WINDOW_WIDTH / 2 / 4.3f, WINDOW_HEIGHT / 20 / 4.3f, score_str);
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);

	// Lines

	SDL_RenderLines( renderer, borders, SDL_arraysize(borders) );

	// Grid

	for (int i = 0; SDL_arraysize(rect) > i ;i++){
		SDL_RenderRects(renderer, rect[i], SDL_arraysize(rect[i]));
	}

	for (int i = 0; i < SDL_arraysize(grid) ; i++){
		for(int j = 0; j < SDL_arraysize(grid[j]) ; j++){
			SDL_Log("Filled %d %d", i, j);
		}
	}

	// Render

	SDL_RenderPresent(renderer);

}

void event_loop(){
	if(SDL_PollEvent(&event) != 0){

		if(event.type == SDL_EVENT_KEY_DOWN){
			if(event.key.scancode == SDL_SCANCODE_A){

			}

			if (event.key.scancode == SDL_SCANCODE_S){
			
			}

			if (event.key.scancode == SDL_SCANCODE_D)
			{

			}
			
			 
		}

		if(event.type == SDL_EVENT_QUIT){
			state = QUIT;
		}
	}
}

void tetris_loop(){

	while( state != QUIT ){

		event_loop();
		logic_loop();
		render_loop();

	}
}


int main(){

	tetris_init();
	tetris_loop();
	tetris_deinit();

	return 0;	 
}
