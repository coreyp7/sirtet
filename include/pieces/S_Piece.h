#include "include/Piece.h"

class S_Piece : public Piece {
    public:

        S_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        ~S_Piece();

        void rotateCW();
        void rotateCCW();
        void setPosition(int x, int y);
};
