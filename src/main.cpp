#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

/* Project includes */
#include "include/util.h"

typedef struct {
    int x, y;
} Pair;

typedef struct {
    int x, y; 
    Pair blocks[4];
} Piece; // right now hardcoded to one type of piece

int init();

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

const int TILE_SIZE = 25;

SDL_Window *window;
SDL_Renderer *renderer;

Pair pair = {1, 1};

Piece piece = {
    0,
    1,
    {Pair{piece.x, piece.y-1}, Pair{piece.x+1, piece.y}, Pair{piece.x+1, piece.y+1}}
};


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

// Get pointer to rect at position specified.
// (Top left going down)
// Returns NULL if the requested grid position is invalid.
SDL_Rect* getTileRect(int x, int y){
    if((x >= GRID_WIDTH) || (y >= GRID_HEIGHT)){
        return NULL;
    }

    int rowStart = y * GRID_WIDTH;
    return &grid[rowStart + x];
}


void gameLoop(){
    bool quit = false;

    SDL_Event event;

    SDL_Rect windowViewport = {
        0, 0, WINDOW_WIDTH, WINDOW_HEIGHT
    };

    // Viewport specifically for the tetris grid.
    SDL_Rect gridViewport = {
            ( WINDOW_WIDTH - (GRID_WIDTH*TILE_SIZE) )/2,
            WINDOW_HEIGHT - (GRID_HEIGHT*TILE_SIZE) - 50,
            GRID_WIDTH*TILE_SIZE, GRID_HEIGHT*TILE_SIZE
    };
    
    while(!quit){
        // event loop
        while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_s){
                        piece.y++;
                    }
                    break;
            }
        }

        // RENDERING //
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderSetViewport(renderer, &gridViewport);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // render grid
        for(int i=0; i<GRID_WIDTH*GRID_HEIGHT; i++){
            if(SDL_RenderDrawRect(renderer, &grid[i])<0){
                printf("SDL_Error:%s\n", SDL_GetError());
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        // SDL_RenderDrawRect(renderer, getTileRect(0, 0));
        // SDL_RenderDrawRect(renderer, getTileRect(0, 1));
        // SDL_RenderDrawRect(renderer, getTileRect(1, 1));
        // SDL_RenderDrawRect(renderer, getTileRect(1, 2));

        SDL_RenderDrawRect(renderer, getTileRect(piece.x, piece.y));

        Pair *currPair = piece.blocks;
        for(int i=0; i<4; i++){
            SDL_RenderDrawRect(renderer, getTileRect(currPair->x, currPair->y));
            currPair++;
        }



        SDL_Rect test = { 0, 0, 100, 100 };
        SDL_RenderSetViewport(renderer, &windowViewport);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(renderer, NULL);

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