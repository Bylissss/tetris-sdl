#include "SDL3/SDL.h"
#include "stdio.h"

// GLOBALS

SDL_Window* window;
SDL_Renderer* renderer;
SDL_DisplayMode* mode;
SDL_Event event;

int score = 0;
char score_str[32];

int display_width;
int display_height;

int window_width = 360 * 1.5;
int window_height = 640 * 1.5;

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

void update_score(){
	snprintf(score_str, sizeof(score_str), "%d", score);

}

void window_to_center(SDL_Window* window){
	SDL_SetWindowPosition(window, display_width/2 - window_width/2, display_height/2 - window_height/2 );
}

void tetris_deinit(){
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void window_init(){
	window = SDL_CreateWindow("tetris", window_width, window_height, 0);
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

void logic_loop(){
	update_score();
}

void render_loop(){
	// Background
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// Score

	SDL_SetRenderScale(renderer, 4.0f, 4.0f);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDebugText(renderer, window_width / 2 / 4.5f, window_height / 10 / 4.5f, score_str);

	// Render

	SDL_RenderPresent(renderer);

}

void event_loop(){
	if(SDL_PollEvent(&event) != 0){

		if(event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_SPACE){
			score += 1;
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
