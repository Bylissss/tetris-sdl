#include "SDL3/SDL.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_DisplayMode* mode;
SDL_Event event;

static int display_width;
static int display_height;

const int window_width = 480;
const int window_height = 640;

void window2center(SDL_Window* window){
	SDL_SetWindowPosition(window, display_width/2 , display_height/2 );
}

typedef enum tetris_states{
	NONE = 0,
	GAME_BEGIN,
	BLOCK_CHECK,
	BLOCK_FALLING,
	GAME_OVER,
	QUIT

}tetris_states;

static int state = NONE;

int tetris_init(){
	state = GAME_BEGIN;

	window = SDL_CreateWindow("tetris", window_height, window_width, 0);
	if(!window){
		return 1;
	}

	mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
	if(!mode){
		return 3;
	}

	display_width = mode->w;
	display_height = mode->h;
	
	window2center(window);

	renderer = SDL_CreateRenderer(window, NULL);
	if(!renderer){
		return 2;
	}

	return 0;
}


void tetris_loop(){

	while( state != QUIT ){

		SDL_SetRenderDrawColor(renderer, 255, 0, 127, 0);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event) != 0){
			if(event.type == SDL_EVENT_QUIT){
				state = QUIT;
			}
		}

	}
}


void tetris_deinit(){
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

int main(){

	tetris_init();
	tetris_loop();
	tetris_deinit();

/*
{
	switch(tetris_init()){
		case 1:
			SDL_log("Window init failed %s", SDL_GetError());
		case 2:
			SDL_log("Renderer init failed %s", SDL_getError());
	}
*/

	return 0;	 
}
