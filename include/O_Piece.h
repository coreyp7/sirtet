#include "include/Piece.h"

class O_Piece : public Piece {
    public:

        O_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        ~O_Piece();

        void rotateCW();
        void rotateCCW();
        void setPosition(int x, int y);
};
