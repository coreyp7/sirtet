#include "include/util.h"

void test(){
    printf("Hello from sdl_setup.cpp!");
}

// int init(SDL_Window* window, SDL_Renderer *renderer, int windowWidth, int windowHeight){
//     if(SDL_Init(SDL_INIT_VIDEO) < 0){
//         printf("SDL couldn't be initialized, SDL error: %s\n", SDL_GetError());
//         return -1;
//     }

//     window = SDL_CreateWindow("Not tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
//     if(window == NULL){
//         printf("Window couldn't be created, SDL error: %s\n", SDL_GetError());
//         return -2;
//     }

//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if(renderer == NULL){
// 		printf( "Renderer couldn't be created, SDL Error: %s\n", SDL_GetError() );
//         return -3;
//     }

//     // TODO: later I'll init SDL_img and all the other stuff too.
//     return 0;
// }