#include "include/Piece.h"
#include "include/util.h"

Piece::Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks[0] = (new Block{x, y});
    blocks[1] = (new Block{x, y-1});
    blocks[2] = (new Block{x+1, y});
    blocks[3] = (new Block{x+1, y+1});
    this->grid = grid;

    facing = UP;
}

Piece::Piece(){
    // for when you create a Piece from a subclass and don't need anything done for you here.
}

Piece::~Piece(){
    // Destructor doesn't destroy everything because the blocks
    // are handled by the grid after the lifespan of this object.
    cleanupLanded();
}

bool Piece::move(Direction dir){
    int xMove = 0;
    int yMove = 0;

    switch(dir){
        case UP:
            yMove--;
            break;
        case DOWN:
            yMove++;
            break;
        case LEFT:
            xMove--;
            break;
        case RIGHT:
            xMove++;
            break;
    }

    // Check if there's a collision where we're going to.
    Block *block;// = blocks[0];
    for(int i=0; i<blocksSize; i++){
        block = blocks[i];
        if(!isEmptyAndInBounds(block->x + xMove, block->y + yMove)){
            return false;
        }

        if(getTile(block->x + xMove, block->y + yMove, grid)->block != NULL){
            return false;
        }
        //block++;
    }

    //block = blocks[0];
    for(int i=0; i<blocksSize; i++){
        block = blocks[i];
        block->x += xMove;
        block->y += yMove;
        //block++;
    }
    return true;
}

// Will return if the specified Tile position has a block in it.
bool Piece::isEmpty(int x, int y){
    return isEmptyAndInBounds(x, y);
}

bool Piece::isEmptyAndInBounds(int x, int y){
    if ( !((x >= 0 && x < GRID_WIDTH) && (y >= 0 && y < GRID_HEIGHT)) ) { // make sure its in bounds
        return false;
    }

    return(getTile(x, y, grid)->block == NULL);
}

void Piece::cleanupLanded(){
    // empty array of references to objects, they're in the grid now
    // and will be cleaned up later.
    for(int i=0; i<blocksSize; i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

// Will insert all the Blocks of this object into its current position.
// Should only be called when a Piece has landed and you're going to get rid of it.
int Piece::insertBlocksAtCurrPos(){
    for(int i=0; i<blocksSize; i++){
        getTile(blocks[i]->x, blocks[i]->y, grid)->block = blocks[i];
    }
}

// For row in grid
//  for block in blocks
//   if getTile(block.x, row y) != null
//    place this piece's blocks on the row above this row (row-1)
//      return
void Piece::landInstant(){
    printf("landInstant()\n");
    //Y NEEDS TO BE CHANGED TO BE THE BOTTOM OF THIS PIECE (Y BOTTOM)
    /*
    int pieceBottom = -1;
    for(int i=0; i<blocksSize; i++){
        if(blocks[i]->y > pieceBottom){
            pieceBottom = blocks[i]->y;
        }
    }
    */
    // Okay I think I have to go to work now:
    // This logic for the outer loop is valid, but the loops inside it are producing crazy shit.
    // Use the outer loop and check that its only iterating through rows that are below the Piece.
    //
    // Then, iterate through this Piece's blocks and see if there's a block in its spot in the current row.
    //
    // If there is, then move all of the pieces down the same amount.
    // NOTE: it may be useful to calculate the distance from the 'bottom' of the Piece a block is.
    // So, if it IS the bottom of the Piece, then the distance would be 0.
    // But if say, you're the top block of a L piece, then the distance would be 2.
    // This way we can offset the destination of the block, therefore keeping the shape of the Piece in tact
    // when it instantly lands. 
    //
    // Additional logic may have to be added to main.cpp to set 'landed' to true instantly.

    // OK new information:
    // I need to be checking the x & y of the blocks with the row that THEY'RE on. 
    // We need to cover situations where there is a collision on on block but not the other (L Piece).
    

    // So, for each block, we need an offset so that we know what row its in while it is moving down.
    Pair originalPositions[4] = { Pair{blocks[0]->x, blocks[0]->y}, Pair{blocks[1]->x, blocks[1]->y}, Pair{blocks[2]->x, blocks[2]->y}, Pair{blocks[3]->x, blocks[3]->y}, };
    // we have the original positions so we can figure out how much to offset their y
    int pieceBase = -1;
    for(int i=0; i<blocksSize; i++){
        if(blocks[i]->y > pieceBase){
            pieceBase = blocks[i]->y;
        } 
    }
    int baseOffsets[4];
    // now get offset for each block 
    for(int i=0; i<blocksSize; i++){
        baseOffsets[i] = pieceBase - blocks[i]->y;
    }

    // now we have the y offset for each block.
    
    for(int y=pieceBase; y<GRID_HEIGHT; y++){
        for(int blockIndex=0; blockIndex<blocksSize; blockIndex++){
            //TODO: handle if getTile returns NULL because that means we're on the ground.

            if(getTile(blocks[blockIndex]->x, y-baseOffsets[blockIndex], grid)->block != NULL){
                /*
                printf("This piece's base will be placed on row %i\n", y-1);
                return;
                */
               // The row above is where our Piece is going.
                int rowDest = y - 1;
                for(int i=0; i<blocksSize; i++){
                    // move the blocks to their new Tiles
                    blocks[i]->setPosition(blocks[i]->x, rowDest-baseOffsets[i]);
                    getTile(blocks[i]->x, rowDest-baseOffsets[i], grid)->block = blocks[i];
                    // note: somehow have to mark that we've 'landed'.
                }
                printf("Placed this Piece on the ground; returning out of landInstant");
                return;
            }
            /*
            if(getTile(blocks[blockIndex]->x, y, grid)->block != NULL){
                // There's a block here, so stop moving down and place the Piece above this row.
                printf("This piece's base will be placed on row %i\n", y-1);
                return;
            }
            */
        }
    }
    printf("Nothing was found?\n");
    /*
    for(int y=pieceBottom; y<GRID_HEIGHT; y++){
        for(int i=0; i<blocksSize; i++){
            if(getTile(blocks[i]->x, y, grid)->block != NULL){
                // Place piece above this row
                int rowDest = y-1; 
                for(int j=0; j<blocksSize; j++){
                    //int diffFromRowDest = y - blocks[j]->y;
                    //int blockY = blocks[j]->y;
                    //int diff = y - rowDest;
                    int diff = (rowDest-blocks[j]->y);
                    printf("diff:%i", diff);
                    printf("rowDest - (rowDest-blocks[j]->y):%i\n", rowDest - (rowDest-blocks[j]->y));
                    getTile(blocks[j]->x, diff, grid)->block = blocks[j];
                }
                return;
            }
        }
   } 
   */
}