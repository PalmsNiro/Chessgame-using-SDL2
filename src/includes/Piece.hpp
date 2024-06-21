#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "common.hpp"
#include "Chessboard.hpp"

enum class Color
{
    WHITE = 0,
    BLACK = 1
};

enum class PieceName
{
    BISHOP_WHITE='B',
    KING_WHITE='K',
    KNIGHT_WHITE='K',
    PAWN_WHITE='P',
    QUEEN_WHITE='Q',
    ROOK_WHITE='R',
    BISHOP_BLACK='B',
    KING_BLACK='K',
    KNIGHT_BLACK='K',
    PAWN_BLACK='P',
    QUEEN_BLACK='Q',
    ROOK_BLACK='R'
};

class Piece
{
protected:
    PieceName name;
    int x, y;
    Color color;
    std::string texturePath;
    SDL_Texture *texture;

public:
    Piece(PieceName name, int x, int y, Color color, const std::string &texturePath);
    virtual ~Piece();

    virtual bool isPathClear(const Chessboard& board, Color color) const = 0;
    virtual std::vector<std::pair<int, int>> validMoves(const Chessboard& chessboard) const = 0;
    void render(SDL_Renderer *renderer);

    int getX() const;
    int getY() const;
    Color getColor() const;
    PieceName getPieceName() const;
    void setPosition(int x, int y);
    char getSymbol();
    // virtual void draw(SDL_Renderer *renderer)
    // {
    //     SDL_Rect destRect = {x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};
    //     SDL_RenderCopy(renderer, texture, NULL, &destRect);
    // }
    // virtual bool isValidMove(int newX, int newY) = 0;
};

#endif // PIECE_HPP
