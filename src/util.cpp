#include "include/util.h"

// Get pointer to rect at position specified.
// (Top left going down)
// Returns NULL if the requested grid position is invalid.
Tile* getTile(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid){
    if((x >= GRID_WIDTH) || (y >= GRID_HEIGHT)){
        return NULL;
    }

    int rowStart = y * GRID_WIDTH;
    return &grid->at(rowStart + x);
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