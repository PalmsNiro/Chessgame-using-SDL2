#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "common.hpp"

enum class Color { WHITE, BLACK };

class Piece {
protected:
    int x, y;
    Color color;
    std::string texturePath;
    SDL_Texture* texture;
public:
    Piece(int x, int y, Color color, const std::string& texturePath);
    virtual ~Piece();

    virtual std::vector<std::pair<int, int>> validMoves() const = 0;
    void render(SDL_Renderer* renderer);

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

    
