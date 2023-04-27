#pragma once
#include "include/Piece.h"
#include "include/util.h"
#include "include/S_Piece.h"
#include "include/T_Piece.h"
#include "include/Z_Piece.h"
#include "include/L_Piece.h"
#include "include/J_Piece.h"
#include "include/O_Piece.h"
#include "include/I_Piece.h"

void initializeGameState();
void simulateGameState(std::vector<SDL_Keycode> keysPressed);

void holdPiece(Piece* piece);
Piece* getRandomPiece();
