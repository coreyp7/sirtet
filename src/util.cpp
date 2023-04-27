#include "include/util.h"

int init(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL couldn't be initialized, SDL error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Not tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    if(window == NULL){
        printf("Window couldn't be created, SDL error: %s\n", SDL_GetError());
        return -2;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
		printf( "Renderer couldn't be created, SDL Error: %s\n", SDL_GetError() );
        return -3;
    }

    int imgFlags = IMG_INIT_PNG;
    if( IMG_Init(imgFlags) == -1){
        printf("SDL_IMG couldn't be initialized: %s\n", IMG_GetError());
        return -6;
    }
    
    if( TTF_Init() == -1){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return -5;
    }

    int loadedAssets = loadAssets();
    if(loadedAssets != 0){
        printf("loadAssets() failed: error code %i", loadedAssets);
        return -7;
    }


    // TODO: later I'll init SDL_img and all the other stuff too.
    return 0;
}

int loadAssets(){
    // load font into global font
    globalFont = TTF_OpenFont("assets/fonts/Lato-Black.ttf", 16);
    if(globalFont == NULL){
		printf( "Failed to load lato black: %s\n", TTF_GetError() );
        return -1;
    } 

    spriteSheet = IMG_LoadTexture(renderer, "assets/blocks/default_sheet.png");
    if(spriteSheet == NULL){
        printf("Couldn't load spritesheet.\n%s\n", IMG_GetError());
        return -2;
    }

    for(int i=0; i<7; i++){
        blockTextures[i] = {i*44, 0, 44, 44};
    }

    bg = IMG_LoadTexture(renderer, "assets/bg32.png");
    if(bg == NULL){
        printf("Couldn't load bg.\n%s\n", IMG_GetError());
        return -3;
    }

    greyPng = IMG_LoadTexture(renderer, "assets/faded.png");
    if(greyPng == NULL){
        printf("Couldn't load faded.\n%s\n", IMG_GetError());
        return -4;
    }
    if(SDL_SetTextureAlphaMod(greyPng, 220) != 0){
        printf("Couldn't set texture alpha to grey.\n");

    }

    return 0;
}

// Populates the grid array with every Tile in our grid.
void fillGrid(){
    for(int row=0; row<GRID_HEIGHT; row++){
        for(int column=0; column<GRID_WIDTH; column++){
            int rowStart = row * GRID_WIDTH; // first tile pos in this row
            grid[rowStart + column] = Tile{column, row, NULL};
        }
    }

/*
    for(int row=0; row<4; row++){
        for(int column=0; column<5; column++){
            int rowStart = row * 5; // first tile pos in this row
            heldGrid[rowStart + column] = Tile{column, row, NULL};
        }
    }
    */
}
// Get pointer to rect at position specified.
// (Top left going down)
// Returns NULL if the requested grid position is invalid.
// Tile* getTile(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid){
//     if((x >= GRID_WIDTH) || (y >= GRID_HEIGHT)){
//         return NULL;
//     }

//     int rowStart = y * GRID_WIDTH;
//     return &grid->at(rowStart + x);
// }
