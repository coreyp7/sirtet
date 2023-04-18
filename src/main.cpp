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
#include "include/Tile.h"


int init();
void cleanup();

// enum Direction {
//     UP, DOWN, LEFT, RIGHT
// };

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

// const int GRID_WIDTH = 10;
// const int GRID_HEIGHT = 20;

const int TILE_SIZE = 25;

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font* globalFont;
const SDL_Color SDL_COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color SDL_COLOR_GREEN = {0, 255, 0, 255};


std::array<Tile, GRID_WIDTH * GRID_HEIGHT> grid; // 0 - 199

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

void handleInput(SDL_Keycode key, Piece *piece){
    switch(key){
        case SDLK_w:
            piece->move(UP);
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
    }
}

void handleInput(std::vector<SDL_Keycode> keysPressed, Piece *piece){
    for(int i=0; i<keysPressed.size(); i++){
        switch(keysPressed.at(i)){
            // case SDLK_w:
            //     piece->move(UP);
            //     break;
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
    int random = rand() % 2; // 0 or 1
        switch(random){
            case 0:
                return new S_Piece(1, 1, &grid);
            case 1:
                return new T_Piece(1, 1, &grid);
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

    Text info = Text(renderer, globalFont, SDL_COLOR_WHITE);

    Uint32 startOfFrame;
    Uint32 endOfFrame;

    int fallSpeed = 500; // TODO: change variable as player plays (based on lines cleared)
    
    std::queue<Piece*> pieceQueue;
    for(int i=0; i<4; i++){
        pieceQueue.push(getRandomPiece());
    }
    Piece* currentPiece = pieceQueue.front();

    Uint32 pieceSpawnTime = SDL_GetTicks() + fallSpeed; // used for dropping piece
    std::vector<SDL_Keycode> keysPressed;

    // Block *blockTest = new Block(5, 15);
    // getTile(5, 15, &grid)->block = blockTest; // manually insert static block
    // Block *blockTest2 = new Block(5, 5);
    // getTile(5, 5, &grid)->block = blockTest2; // manually insert static block
    Block *blockTest = new Block(5, 5);
    // getTile(5, 5, &grid)->block = blockTest;
    // blockTest = new Block(5, 4);
    // getTile(5, 4, &grid)->block = blockTest;

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
                    //handleInput(event.key.keysym.sym, &testPiece);
                    keysPressed.push_back(event.key.keysym.sym);
                    break;
            }
        }

        // GAME STATE //
        if(!keysPressed.empty()){
            handleInput(keysPressed, currentPiece);
            keysPressed.clear();
        }
        
        if((pieceSpawnTime < SDL_GetTicks())){
            bool landed = !currentPiece->move(DOWN);
            if(landed){
                // Insert blocks into position of Piece when landed,
                // then get rid of that Piece in the queue.
                currentPiece->insertBlocksAtCurrPos();
                pieceQueue.pop();
                
                pieceQueue.push(getRandomPiece());
                currentPiece = pieceQueue.front();

                clearCompleteLines();
            }
            pieceSpawnTime = SDL_GetTicks() + fallSpeed;
        }

        // RENDERING //
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // NOTE: Will probably render stuff outside grid here.
        // SDL_RenderSetViewport(renderer, &windowViewport);
        // std::ostringstream oss;
        // oss << currPiece[0]->facing;
        // info.changeText("Facing: "+oss.str());
        // info.render(0, 0);

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