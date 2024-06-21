#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED

#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 800; // Make the window square for the chessboard
const int ROWS = 8, COLS = 8;
const int SQUARE_SIZE = WIDTH / COLS;

const int CHESSBOARD_SIZE = 600;
const int OFFSET_X = (WIDTH - CHESSBOARD_SIZE) / 2; // Center the chessboard horizontally
const int OFFSET_Y = (HEIGHT - CHESSBOARD_SIZE) / 2; // Center the chessboard vertically

#endif