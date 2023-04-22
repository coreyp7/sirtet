#pragma once

class Block {
    public:
        int x, y;
        char pieceType;

        Block();
        Block(int x, int y);
        void setPosition(int x, int y);
};