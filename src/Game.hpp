#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "common.hpp"
#include "Pawn.hpp"

class Game
{
public:
    Game();
    ~Game();

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *backgroundTexture;

    std::vector<Piece *> piecesAlive;
    std::vector<Piece *> piecesDead;

    int Init();
    int Run();
    int Close();

    void createPieces();
    Piece *removePieceFromBoard(int boardX, int boardY);
};
#endif
