#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

/* Project includes */
#include "include/Piece.h"
#include "include/Tile.h"

int init();
void cleanup();

// enum Direction {
//     UP, DOWN, LEFT, RIGHT
// };

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

const int TILE_SIZE = 25;

SDL_Window *window;
SDL_Renderer *renderer;


Tile grid[GRID_WIDTH * GRID_HEIGHT]; // 0 - 199
Piece testPiece = Piece{1, 1};

// void renderPiece(Piece *piece){
//     // Render piece at base position
//     SDL_RenderDrawRect(renderer, getTileRect(piece->x, piece->y));

//     Pair *currPair = piece->blocks;
//     for(int i=0; i<3; i++){
//         SDL_RenderDrawRect(renderer, getTileRect(currPair->x, currPair->y));
//         currPair++;
//     }
//     //currPair = NULL;
// }

// void movePiece(Piece *piece, Direction direction){
//     int xMove = 0;
//     int yMove = 0;

//     switch (direction){
//         case UP:
//             yMove--;
//             break;
//         case DOWN:
//             yMove++;
//             break;
//         case LEFT:
//             xMove--;
//             break;
//         case RIGHT:
//             xMove++;
//             break;
//     }

//     piece->x += xMove;
//     piece->y += yMove;

//     Pair *currPair = piece->blocks;
//     for(int i=0; i<3; i++){
//         currPair->x += xMove;
//         currPair->y += yMove;
//         currPair++;
//     }
// }

void fillGrid(){
    for(int row=0; row<GRID_HEIGHT; row++){

        for(int column=0; column<GRID_WIDTH; column++){

            int rowStart = row * GRID_WIDTH; // first tile pos in this row
            // grid[rowStart + column] = SDL_Rect{column*TILE_SIZE, row*TILE_SIZE, TILE_SIZE, TILE_SIZE};
            grid[rowStart + column] = Tile{column, row, NULL};
        }
    }
    //printf("(%i, %i)", grid[(GRID_WIDTH * GRID_HEIGHT)-1].x, grid[(GRID_WIDTH * GRID_HEIGHT)-1].y);
}

// Get pointer to rect at position specified.
// (Top left going down)
// Returns NULL if the requested grid position is invalid.
Tile* getTileRect(int x, int y){
    if((x >= GRID_WIDTH) || (y >= GRID_HEIGHT)){
        return NULL;
    }

    int rowStart = y * GRID_WIDTH;
    return &grid[rowStart + x];
}

void handleInput(SDL_Keycode key){
    switch(key){
        case SDLK_w:
            testPiece.move(UP);
            break;
        case SDLK_a:
            testPiece.move(LEFT);
            break;
        case SDLK_s:
            testPiece.move(DOWN);
            break;
        case SDLK_d:
            testPiece.move(RIGHT);
            break;
    }
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

    Uint32 startOfFrame;
    Uint32 endOfFrame;
    
    while(!quit){

        // event loop
        while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    handleInput(event.key.keysym.sym);
                    break;
            }
        }

        // RENDERING //
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Start rendering tetris grid, pieces, etc.
        SDL_RenderSetViewport(renderer, &gridViewport);

        // render grid
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for(int i=0; i<GRID_WIDTH*GRID_HEIGHT; i++){
            SDL_Rect rect = {grid[i].x * TILE_SIZE, grid[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if(SDL_RenderDrawRect(renderer, &rect)<0){
                printf("SDL_Error:%s\n", SDL_GetError());
            }
        }

        // render piece
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        Block *block = testPiece.blocks;
        for(int i=0; i<4; i++){
            SDL_Rect rect = {block->x * TILE_SIZE, block->y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if(SDL_RenderDrawRect(renderer, &rect)<0){
                printf("SDL_Error:%s\n", SDL_GetError());
            }
            block++;
        }

        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        //renderPiece(&piece);
        SDL_RenderPresent(renderer);

    }
    
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
		printf( "Renderer couldn't be created, SDL Error: %s\n", SDL_GetError() );
        return -3;
    }

    // TODO: later I'll init SDL_img and all the other stuff too.
    return 0;
}

void cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}