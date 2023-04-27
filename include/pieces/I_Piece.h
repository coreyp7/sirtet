#include "include/Piece.h"

class I_Piece : public Piece {
    public:

        I_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        ~I_Piece();

        void rotateCW();
        void rotateCCW();
        void setPosition(int x, int y);
};
