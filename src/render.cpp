#include "include/render.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

TTF_Font* globalFont = NULL;

SDL_Texture* spriteSheet = NULL;
SDL_Rect blockTextures[7];

SDL_Texture* bg = NULL;
SDL_Texture* greyPng = NULL;


void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderTetrisGrid();

    // Text exampleText = Text(renderer, globalFont, SDL_COLOR_WHITE);
    // exampleText.changeText("Example text");
    // exampleText.render(100, 100);
    SDL_RenderPresent(renderer);
}

void renderTetrisGrid(){
    // Start rendering tetris grid, pieces, etc.
    SDL_RenderSetViewport(renderer, &gridViewport);

    // render grid
    //SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // bg grid color
    for(int i=0; i<GRID_WIDTH*GRID_HEIGHT; i++){
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // bg grid color
        SDL_Rect rect = {grid[i].x * TILE_SIZE, grid[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

        SDL_RenderCopyEx(renderer, greyPng, NULL, &rect, 0, NULL, SDL_FLIP_NONE);

        if(grid[i].block != NULL){//can't do this yet
            // renderBlock(grid[i].block, &rect);
        }
        else if(SDL_RenderDrawRect(renderer, &rect)<0){
            printf("SDL_Error:%s\n", SDL_GetError());
        }
        
    }
}