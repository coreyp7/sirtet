#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <sstream>
#include <array>
#include <vector>
#include <queue>

/* */
#include "include/Text.h"
#include "include/util.h"

/* Project includes */
#include "include/Piece.h"
#include "include/S_Piece.h"
#include "include/T_Piece.h"
#include "include/Z_Piece.h"
#include "include/L_Piece.h"
#include "include/J_Piece.h"
#include "include/O_Piece.h"
#include "include/I_Piece.h"
#include "include/Tile.h"

// Function signatures in main.cpp (in order)
void fillGrid();
void holdPiece(Piece* piece);
void handleInput(std::vector<SDL_Keycode> keysPressed, Piece *piece);
bool isRowEmpty(int y);
bool isRowFull(int y);
void clearCompleteLines();
Piece* getRandomPiece();
bool checkForGameOver();
void renderBlock(Block* block, SDL_Rect* dest);
void gameLoop();
// main
void renderTetrisGrid();
void renderHeldPiece();
void renderPieceQueue();
void renderGhostPiece();
int loadAssets();
int init();
void cleanup();

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;
const int TILE_SIZE = 25;
const int PIECE_START_POS_X = (GRID_WIDTH/2)-1;
const int PIECE_START_POS_Y = 1;
// Viewport for entire window
SDL_Rect windowViewport = {
    0, 0, WINDOW_WIDTH, WINDOW_HEIGHT
};

// Viewport specifically for the tetris grid.
SDL_Rect gridViewport = {
        ( WINDOW_WIDTH - (GRID_WIDTH*TILE_SIZE) )/2,
        WINDOW_HEIGHT - (GRID_HEIGHT*TILE_SIZE) - 50,
        GRID_WIDTH*TILE_SIZE, GRID_HEIGHT*TILE_SIZE
};

SDL_Rect queueViewport = {
    gridViewport.x + gridViewport.w,
    gridViewport.y,
    100, //(4*10)*5
    300
};

// For held piece
SDL_Rect heldViewport = {
    gridViewport.x - 100,
    gridViewport.y,
    5*10, 4*10
};

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font* globalFont;
const SDL_Color SDL_COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color SDL_COLOR_GREEN = {0, 255, 0, 255};
bool gameOver = false;

std::array<Tile, GRID_WIDTH * GRID_HEIGHT> grid; // 0 - 199
//std::queue<Piece*> pieceQueue;
Piece* pieceQueue[4];
Piece* currentPiece;
bool heldPieceLocked = false;

bool landed = false;

Uint32 pieceSpawnTime; //SDL_GetTicks() + fallSpeed; // used for dropping piece
Uint32 allowedToDrop;

SDL_Texture* blockTexture;
SDL_Texture* spriteSheet;
SDL_Rect blockTextures[7];

// visual stuff
std::array<Tile, 6*25> queueGrid;
//std::array<Tile, 5*4> heldGrid;
Piece* heldPiece;

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

// Provided a reference to the Piece, this will store this Piece in the
// player's Piece holder.
// If the player already had a Piece in there (anytime after first), then
// the piece that was in the slot will be spawned, ignoring pieceQueue.
void holdPiece(Piece* piece){
    // if locked, then return and ignore.
    if(heldPieceLocked) return;

    printf("Before: (heldPiece=%p), (currentPiece=%p)\n", heldPiece, currentPiece);
    if(heldPiece != NULL){
        std::swap(currentPiece, heldPiece);
        currentPiece->setPosition(PIECE_START_POS_X, PIECE_START_POS_Y);
        //heldPiece->setPosition(PIECE_START_POS_X, PIECE_START_POS_Y);
    } else {  // first time holding Piece
        heldPiece = currentPiece;
        //pieceQueue.pop();
        //pieceQueue.push(getRandomPiece());
        //currentPiece = pieceQueue.front();
        pieceQueue[0] = pieceQueue[1];
        pieceQueue[1] = pieceQueue[2];
        pieceQueue[2] = pieceQueue[3];
        pieceQueue[3] = getRandomPiece();

        currentPiece = pieceQueue[0];


        //heldPiece->setPosition(PIECE_START_POS_X, PIECE_START_POS_Y);

    }
    heldPiece->setPosition(1, 2);
    heldPieceLocked = true;
    printf("After: (heldPiece=%p), (currentPiece=%p)\n", heldPiece, currentPiece);
}



void handleInput(std::vector<SDL_Keycode> keysPressed, Piece *piece){
    for(int i=0; i<keysPressed.size(); i++){
        switch(keysPressed.at(i)){
            case SDLK_w:
                if(allowedToDrop < SDL_GetTicks()){
                    piece->landInstant();
                    landed = true;
                    pieceSpawnTime = SDL_GetTicks() - 1;                
                    allowedToDrop = SDL_GetTicks() + 250;
                } // otherwise ignore
                break;
            case SDLK_a:
                piece->move(LEFT);
                break;
            case SDLK_s:
                piece->move(DOWN);
                break;
            case SDLK_d:
                piece->move(RIGHT);
                break;
            case SDLK_p:
                piece->rotateCW();
                break;
            case SDLK_o:
                piece->rotateCCW();
                break;
            case SDLK_h:
                holdPiece(piece);
    }
    }
}

// Given a row number (starting from top), will return if a
// row is completely empty of Blocks.
bool isRowEmpty(int y){
    for(int x=0; x<GRID_WIDTH; x++){
        if(getTile(x, y, &grid)->block != NULL){
            return false;
        }
    }
    return true;
}

// Given a row number, will return if a row is completely
// full of Blocks.
bool isRowFull(int y){
    for(int x=0; x<GRID_WIDTH; x++){
        if(getTile(x, y, &grid)->block == NULL){
            return false;
        }
    }
    return true;
}

// Will check the grid for any complete lines and shift the block
// positions appropriately.
void clearCompleteLines(){
    int rowIndex; // start of this row
    bool full = true; // true until proven false

    std::vector<int> clearedRows;
    // Loop through array one row at a time
    for(int row=0; row<GRID_HEIGHT; row++){
        if(isRowFull(row)){
            clearedRows.push_back(row);
            // now clear this row
            for(int tile=0; tile<GRID_WIDTH; tile++){
                delete getTile(tile, row, &grid)->block;
                getTile(tile, row, &grid)->block = NULL;
            }
        }
    }

    if(clearedRows.empty()){
        return;
    }

    // Move shit down
    int newRow = clearedRows.back();

    for(int y=newRow; y>-1; y--){
        //printf("Going through row %i\n", y);
        if(isRowEmpty(y)){
            // keep going up
        } else {
            // set the current row (y) to (newRow).            
            for(int x=0; x<GRID_WIDTH; x++){
                getTile(x, newRow, &grid)->block = getTile(x, y, &grid)->block;
                getTile(x, y, &grid)->block = NULL;
            }
            printf("Row %i moved to row %i\n", y, newRow);
            newRow--;
        }
    }
}

Piece* getRandomPiece(){
    int random = rand() % 7;
        switch(random){
            case 0:
                return new S_Piece(PIECE_START_POS_X, PIECE_START_POS_Y, &grid);
            case 1:
                return new T_Piece(PIECE_START_POS_X, PIECE_START_POS_Y, &grid);
            case 2:
                return new Z_Piece(PIECE_START_POS_X, PIECE_START_POS_Y, &grid);
            case 3:
                return new J_Piece(PIECE_START_POS_X, PIECE_START_POS_Y, &grid);
            case 4:
                return new L_Piece(PIECE_START_POS_X, PIECE_START_POS_Y, &grid);
            case 5:
                return new O_Piece(PIECE_START_POS_X, PIECE_START_POS_Y, &grid);
            case 6:
                return new I_Piece(PIECE_START_POS_X, PIECE_START_POS_Y, &grid);
        }
    // FOR TESTING PIECES
    //return new I_Piece(PIECE_START_POS_X, PIECE_START_POS_Y, &grid);
}

// Returns true if game over, false otherwise.
bool checkForGameOver(){
    for(int i=0; i<4; i++){
        int x = currentPiece->blocks[i]->x;
        int y = currentPiece->blocks[i]->y;
        if(getTile(x, y, &grid)->block != NULL){
            // there's a block present in the spawn position, the game is over.
            return true;
        }
    }
    return false;
}

// Renders block in the SDL_Rect dest.
// NOTE: renders in whatever current viewport is; make sure to be in the grid viewport before calling this.
void renderBlock(Block* block, SDL_Rect* dest){
    int sheetPos = -1;
    switch(block->pieceType){
        case ('I'):
            sheetPos = 0;
            break;
        case ('S'):
            sheetPos = 1;
            break;
        case ('O'):
            sheetPos = 2;
            break;
        case ('L'):
            sheetPos = 3;
            break;
        case ('T'):
            sheetPos = 4;
            break;
        case ('Z'):
            sheetPos = 5;
            break;
        case ('J'):
            sheetPos = 6;
            break;
    }
    SDL_RenderCopyEx(renderer, spriteSheet, &blockTextures[sheetPos], dest, 0, NULL, SDL_FLIP_NONE);
}

void gameLoop(){
    bool quit = false;

    SDL_Event event;


    Text info = Text(renderer, globalFont, SDL_COLOR_WHITE);

    Uint32 startOfFrame;
    Uint32 endOfFrame;

    int fallSpeed = 500; // TODO: change variable as player plays (based on lines cleared)
    
    for(int i=0; i<4; i++){
        pieceQueue[i] = getRandomPiece();
    }
    currentPiece = pieceQueue[0];

    pieceSpawnTime = SDL_GetTicks() + fallSpeed; // used for dropping piece
    allowedToDrop = 0;
    std::vector<SDL_Keycode> keysPressed;
    
    while(!quit){
        // event loop
        while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    keysPressed.push_back(event.key.keysym.sym);
                    break;
            }
        }

        if(!gameOver){
            // GAME STATE //
            if(!keysPressed.empty()){
                handleInput(keysPressed, currentPiece);
                keysPressed.clear();
            }
            
            
            if((pieceSpawnTime < SDL_GetTicks())){
                landed = !currentPiece->move(DOWN);
                if(landed){
                    // Insert blocks into position of Piece when landed,
                    // then get rid of that Piece in the queue.
                    currentPiece->insertBlocksAtCurrPos();
                    //pieceQueue.pop();

                    pieceQueue[0] = pieceQueue[1];
                    pieceQueue[1] = pieceQueue[2];
                    pieceQueue[2] = pieceQueue[3];
                    pieceQueue[3] = getRandomPiece();

                    // delete current piece from memory
                    currentPiece->cleanupLanded();
                    delete currentPiece;

                    //currentPiece = pieceQueue.front();
                    currentPiece = pieceQueue[0];
                    heldPieceLocked = false;

                    clearCompleteLines();

                    if(checkForGameOver()){
                        // do game over shit
                        gameOver = true;
                    }
                }
                pieceSpawnTime = SDL_GetTicks() + fallSpeed;
            }

        }

        // RENDERING //
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderSetViewport(renderer, &windowViewport); 
        if(gameOver){
            std::ostringstream oss;
            info.changeText("GAME OVER");
            info.render((WINDOW_WIDTH-info.getWidth())/2, 0);
        }

        renderTetrisGrid();

        // Render current piece
        Block *block;
        for(int i=0; i<4; i++){
            block = currentPiece->blocks[i];
            SDL_Rect rect = {block->x * TILE_SIZE, block->y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            renderBlock(block, &rect);
        }

        renderHeldPiece();

        //TODO: render queue
        renderPieceQueue();

        renderGhostPiece();

        SDL_RenderPresent(renderer);
    }
    
}

// Renders in 'gridViewport'. 
// Draws grid lines and draws all Tiles in grid that have a block in them.
void renderTetrisGrid(){
    // Start rendering tetris grid, pieces, etc.
    SDL_RenderSetViewport(renderer, &gridViewport);

    // render grid
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // bg grid color
    for(int i=0; i<GRID_WIDTH*GRID_HEIGHT; i++){
        SDL_Rect rect = {grid[i].x * TILE_SIZE, grid[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

        if(grid[i].block != NULL){
            renderBlock(grid[i].block, &rect);
        }
        else if(SDL_RenderDrawRect(renderer, &rect)<0){
            printf("SDL_Error:%s\n", SDL_GetError());
        }
    }
}

void renderHeldPiece(){
        // now draw stuff around grid
        SDL_RenderSetViewport(renderer, &heldViewport);
        // render held piece
        if(heldPiece != NULL){
            Block* block;
            for(int i=0; i<4; i++){
                block = heldPiece->blocks[i];
                SDL_Rect newrect = {block->x * 10, block->y * 10, 10, 10};
                renderBlock(block, &newrect);
            }
        }
}

void renderPieceQueue(){
    SDL_RenderSetViewport(renderer, &queueViewport);

    Piece* piece;
    Block* block;
    for(int i=1; i<4; i++){
        piece = pieceQueue[i];
        
        for(int j=0; j<4; j++){
            block = piece->blocks[j];
            SDL_Rect rect = {block->x * 10, 
                (block->y * 10) + (i * 60),
                10, 10};
            renderBlock(block, &rect);
        }
    }
}

// return row to place Piece on
void renderGhostPiece(){
    SDL_RenderSetViewport(renderer, &gridViewport);
    int pieceBase = -1;
    Block** blocks = currentPiece->blocks;
    for(int i=0; i<currentPiece->blocksSize; i++){
        if(blocks[i]->y > pieceBase){
            pieceBase = blocks[i]->y;
        } 
    }
    // Contains offset of block from the Piece's 'base'.
    int baseOffsets[4];
    for(int i=0; i<currentPiece->blocksSize; i++){
        baseOffsets[i] = pieceBase - blocks[i]->y;
    }

    // Go through each row (top to bottom) until we find a tile with block in it
    for(int y=pieceBase; y<GRID_HEIGHT; y++){
        for(int blockIndex=0; blockIndex<4; blockIndex++){
            if(getTile(blocks[blockIndex]->x, y-baseOffsets[blockIndex], &grid)->block != NULL){
               // rowDes is the row where our Piece base is going.
                int rowDest = y - 1;

                Block *block;
                for(int i=0; i<4; i++){
                    block = currentPiece->blocks[i];
                    SDL_Rect rect = {block->x * TILE_SIZE, (rowDest-baseOffsets[i]) * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    renderBlock(block, &rect);
                }
                
                return;
            }
        }
    }

    // Made it through all of them, so that means put it on the ground.
    //printf("Nothing was found: so placing on ground level.\n");
    for(int i=0; i<4; i++){
        int rowDest = GRID_HEIGHT-1; 
        for(int i=0; i<4; i++){
            Block *block;
            for(int i=0; i<4; i++){
                block = currentPiece->blocks[i];
                SDL_Rect rect = {block->x * TILE_SIZE, ((19-baseOffsets[i]) * TILE_SIZE), TILE_SIZE, TILE_SIZE};
                renderBlock(block, &rect);
            }
        } 
    }

    return;


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

void cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}