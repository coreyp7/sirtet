#include "include/Piece.h"

class L_Piece : public Piece {
    public:

        L_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        ~L_Piece();

        void rotateCW();
        void rotateCCW();
        void setPosition(int x, int y);
};
