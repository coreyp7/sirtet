#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

/* Project includes */
#include "include/util.h"

int init();

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

const int TILE_SIZE = 25;

SDL_Window *window;
SDL_Renderer *renderer;


SDL_Rect grid[GRID_WIDTH * GRID_HEIGHT]; // 0 - 199

void fillGrid(){
    for(int row=0; row<GRID_HEIGHT; row++){

        for(int column=0; column<GRID_WIDTH; column++){

            int rowStart = row * GRID_WIDTH; // first tile pos in this row
            grid[rowStart + column] = SDL_Rect{column*TILE_SIZE, row*TILE_SIZE, TILE_SIZE, TILE_SIZE};
        }
    }
    printf("(%i, %i)", grid[(GRID_WIDTH * GRID_HEIGHT)-1].x, grid[(GRID_WIDTH * GRID_HEIGHT)-1].y);
}


void gameLoop(){
    bool quit = false;

    SDL_Event event;
    

    while(!quit){

        while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // SDL_Rect gridViewport = 
        //     {(WINDOW_WIDTH+(GRID_WIDTH*TILE_SIZE))/2,
        //     (WINDOW_HEIGHT+(GRID_HEIGHT*TILE_SIZE))/2,
        //     GRID_WIDTH, GRID_HEIGHT
        // };
        // SDL_RenderSetViewport(renderer, &gridViewport);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // render grid
        for(int i=0; i<GRID_WIDTH*GRID_HEIGHT; i++){
            // SDL_RenderDrawPoint(renderer, grid[i].x * 5, grid[i].y * 5);
            if(SDL_RenderDrawRect(renderer, &grid[i])<0){
                printf("SDL_Error:%s\n", SDL_GetError());
            }
        }
        // SDL_Rect tile = {0, 0, TILE_SIZE, TILE_SIZE};
        // SDL_Rect tile2 = {0, TILE_SIZE, TILE_SIZE, TILE_SIZE};
        // SDL_Rect tile3 = {TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};

        // SDL_RenderDrawRect(renderer, &tile);
        // SDL_RenderDrawRect(renderer, &tile2);
        // SDL_RenderDrawRect(renderer, &tile3);

        SDL_RenderPresent(renderer);
    }
    
}

void cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]){
    int good = init();
    if(good<0){
        printf("not good %i", good);
        return -1;
    }

    // Testing
    fillGrid();

    gameLoop();

    cleanup();
    // TODO: cleanup function before closing
    return 0;
}

int init(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL couldn't be initialized, SDL error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Not tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    if(window == NULL){
        printf("Window couldn't be created, SDL error: %s\n", SDL_GetError());
        return -2;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
		printf( "Renderer couldn't be created, SDL Error: %s\n", SDL_GetError() );
        return -3;
    }

    // TODO: later I'll init SDL_img and all the other stuff too.
    return 0;
}