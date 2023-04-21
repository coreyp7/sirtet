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


int init();
void cleanup();
Piece* getRandomPiece();

// enum Direction {
//     UP, DOWN, LEFT, RIGHT
// };

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;
const int TILE_SIZE = 25;
const int PIECE_START_POS_X = (GRID_WIDTH/2)-1;
const int PIECE_START_POS_Y = 1;

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font* globalFont;
const SDL_Color SDL_COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color SDL_COLOR_GREEN = {0, 255, 0, 255};
bool gameOver = false;

std::array<Tile, GRID_WIDTH * GRID_HEIGHT> grid; // 0 - 199
std::queue<Piece*> pieceQueue;
Piece* currentPiece;
Piece* heldPiece;
bool heldPieceLocked = false;

bool landed = false;

Uint32 pieceSpawnTime; //SDL_GetTicks() + fallSpeed; // used for dropping piece
//bool allowedToDrop = true;
Uint32 allowedToDrop;

// Populates the grid array with every Tile in our grid.
void fillGrid(){
    for(int row=0; row<GRID_HEIGHT; row++){
        for(int column=0; column<GRID_WIDTH; column++){
            int rowStart = row * GRID_WIDTH; // first tile pos in this row
            grid[rowStart + column] = Tile{column, row, NULL};
        }
    }
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
        heldPiece->setPosition(PIECE_START_POS_X, PIECE_START_POS_Y);
    } else {  // first time holding Piece
        heldPiece = currentPiece;
        pieceQueue.pop();
        pieceQueue.push(getRandomPiece());
        currentPiece = pieceQueue.front();
        heldPiece->setPosition(PIECE_START_POS_X, PIECE_START_POS_Y);
    }
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

    Text info = Text(renderer, globalFont, SDL_COLOR_WHITE);

    Uint32 startOfFrame;
    Uint32 endOfFrame;

    int fallSpeed = 500; // TODO: change variable as player plays (based on lines cleared)
    
    for(int i=0; i<4; i++){
        pieceQueue.push(getRandomPiece());
    }
    currentPiece = pieceQueue.front();

    pieceSpawnTime = SDL_GetTicks() + fallSpeed; // used for dropping piece
    allowedToDrop = 0;
    std::vector<SDL_Keycode> keysPressed;

    Block *blockTest = new Block(5, 5);
    

    for(int i=0; i<GRID_WIDTH-1; i++){
        getTile(i, 19, &grid)->block = blockTest;
    }
    
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
                    pieceQueue.pop();

                    // delete current piece from memory
                    currentPiece->cleanupLanded();
                    delete currentPiece;

                    pieceQueue.push(getRandomPiece());
                    currentPiece = pieceQueue.front();
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

        // NOTE: Will probably render stuff outside grid here.
        SDL_RenderSetViewport(renderer, &windowViewport);
        if(gameOver){
            std::ostringstream oss;
            info.changeText("GAME OVER");
            info.render((WINDOW_WIDTH-info.getWidth())/2, 0);
        }

        // Start rendering tetris grid, pieces, etc.
        SDL_RenderSetViewport(renderer, &gridViewport);

        // render grid
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for(int i=0; i<GRID_WIDTH*GRID_HEIGHT; i++){
            SDL_Rect rect = {grid[i].x * TILE_SIZE, grid[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

            if(grid[i].block != NULL){
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            }

            if(SDL_RenderDrawRect(renderer, &rect)<0){
                printf("SDL_Error:%s\n", SDL_GetError());
            }

            if(grid[i].block != NULL){
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

                Text *text = new Text(renderer, globalFont, SDL_COLOR_GREEN);
                // std::ostringstream oss;
                // oss << "full";
                text->changeText("full");
                text->render(rect.x, rect.y);
                text->~Text();
            }

            // Text text = Text(renderer, globalFont, SDL_COLOR_WHITE);
            // std::ostringstream oss;
            // oss << i;
            // text.changeText(oss.str());
            // text.render(rect.x, rect.y);
        }

        // render piece
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        Block *block;// = currPiece->blocks[0];
        for(int i=0; i<4; i++){
            block = currentPiece->blocks[i];
            SDL_Rect rect = {block->x * TILE_SIZE, block->y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if(SDL_RenderDrawRect(renderer, &rect)<0){
                printf("SDL_Error:%s\n", SDL_GetError());
            }
            Text *text = new Text(renderer, globalFont, SDL_COLOR_WHITE);
            std::ostringstream oss;
            oss << i;
            text->changeText(oss.str());
            text->render(rect.x, rect.y);
            text->~Text();

            // block = currPiece->blocks[i];
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
    
    if( TTF_Init() == -1){
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return -5;
    }

    // load font into global font
    globalFont = TTF_OpenFont("assets/fonts/Lato-Black.ttf", 16);
    if(globalFont == NULL){
		printf( "Failed to load lato black: %s\n", TTF_GetError() );
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