#include "Piece.hpp"
#include <SDL2/SDL_image.h>

Piece::Piece(PieceName name, int x, int y, Color color, const std::string &texturePath)
    : name(name), x(x), y(y), color(color), texturePath(texturePath), texture(nullptr) {}

Piece::~Piece()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void Piece::render(SDL_Renderer *renderer)
{
    if (!texture)
    {
        SDL_Surface *surface = IMG_Load(texturePath.c_str());
        if (surface)
        {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }
    if (texture)
    {
        SDL_Rect rect = {OFFSET_X + x * (CHESSBOARD_SIZE / COLS), OFFSET_Y + y * (CHESSBOARD_SIZE / ROWS), CHESSBOARD_SIZE / COLS, CHESSBOARD_SIZE / ROWS};
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}

int Piece::getX() const { return x; }
int Piece::getY() const { return y; }
Color Piece::getColor() const { return color; }
PieceName Piece::getPieceName() const { return name; }
void Piece::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

char Piece::getSymbol()
{
    return (char)this->getPieceName();
}