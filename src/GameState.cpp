#include "include/GameState.h"

int amountOfLinesCleared = 0;
int level = 0;
int fallSpeed = 500; // TODO: change variable as player plays (based on lines cleared)

bool gameOver = false;
Piece* pieceQueue[4];
Piece* currentPiece;
Piece* heldPiece;
bool heldPieceLocked = false;

bool landed = false;

Uint32 pieceSpawnTime;
Uint32 allowedToDrop;

void initializeGameState(){
    for(int i=0; i<4; i++){
        pieceQueue[i] = getRandomPiece();
    }
    currentPiece = pieceQueue[0];

    pieceSpawnTime = getTime() + fallSpeed; // used for dropping piece
    allowedToDrop = 0;
}

void simulateGameState(std::vector<SDL_Keycode> keysPressed){
    // Get input and apply to currentPiece
    for(int i=0; i<keysPressed.size(); i++){
        switch(keysPressed.at(i)){
            case SDLK_w:
                if(allowedToDrop < SDL_GetTicks()){
                    currentPiece->landInstant();
                    landed = true;
                    pieceSpawnTime = SDL_GetTicks() - 1;                
                    allowedToDrop = SDL_GetTicks() + 250;
                } // otherwise ignore
                break;
            case SDLK_a:
                currentPiece->move(LEFT);
                break;
            case SDLK_s:
                currentPiece->move(DOWN);
                break;
            case SDLK_d:
                currentPiece->move(RIGHT);
                break;
            case SDLK_p:
                currentPiece->rotateCW();
                break;
            case SDLK_o:
                currentPiece->rotateCCW();
                break;
            case SDLK_h:
                holdPiece(currentPiece);
    }
    }
}

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