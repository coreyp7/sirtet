#include "include/Piece.h"

class J_Piece : public Piece {
    public:

        J_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        ~J_Piece();

        void rotateCW();
        void rotateCCW();
        void setPosition(int x, int y);
};
