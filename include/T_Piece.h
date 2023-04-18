#include "include/Piece.h"

class T_Piece : public Piece {
    public:

        T_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        ~T_Piece();

        void rotateCW();
        void rotateCCW();
        void setPosition(int x, int y);
};
