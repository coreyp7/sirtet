#include "include/Piece.h"

class Z_Piece : public Piece {
    public:

        Z_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        ~Z_Piece();

        void rotateCW();
        void rotateCCW();
        void setPosition(int x, int y);
};
