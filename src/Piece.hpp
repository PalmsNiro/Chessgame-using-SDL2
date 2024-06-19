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
    WHITE,
    BLACK
};

enum class PieceName
{
    BISHOP_WHITE,
    KING_WHITE,
    KNIGHT_WHITE,
    PAWN_WHITE,
    QUEEN_WHITE,
    ROOK_WHITE,
    BISHOP_BLACK,
    KING_BLACK,
    KNIGHT_BLACK,
    PAWN_BLACK,
    QUEEN_BLACK,
    ROOK_BLACK
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
    void setPosition(int x, int y);

    // virtual void draw(SDL_Renderer *renderer)
    // {
    //     SDL_Rect destRect = {x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};
    //     SDL_RenderCopy(renderer, texture, NULL, &destRect);
    // }
    // virtual bool isValidMove(int newX, int newY) = 0;
};

#endif // PIECE_HPP
