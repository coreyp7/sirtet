#pragma once

#include <SDL.h>
#include <array>
#include "include/constants.h"
#include "include/Tile.h"

// The grid of Tiles, which is handeld by GameState and render
extern std::array<Tile, GRID_WIDTH * GRID_HEIGHT> grid; // 0 - 199