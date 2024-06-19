#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "common.hpp"
#include "Chessboard.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Queen.hpp"
#include "Piece.hpp"

class Game
{
public:

    Game();
    ~Game();

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *backgroundTexture;

    Chessboard chessboard;

    std::vector<Piece *> piecesAlive;
    std::vector<Piece *> piecesDead;

    int Init();
    int Run();
    int Close();

    void createPieces();
    Piece *removePieceFromBoard(int boardX, int boardY);
    bool isValidMove(Piece *piece, int newX, int newY);
    void movePiece(Piece *piece, int newX, int newY);
};
#endif
