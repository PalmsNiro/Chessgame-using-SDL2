#include "Piece.hpp"
#include <SDL2/SDL_image.h>

Piece::Piece(int x, int y, Color color, const std::string& texturePath)
    : x(x), y(y), color(color), texturePath(texturePath), texture(nullptr) {}

Piece::~Piece() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Piece::render(SDL_Renderer* renderer) {
    if (!texture) {
        SDL_Surface* surface = IMG_Load(texturePath.c_str());
        if (surface) {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }
    if (texture) {
        SDL_Rect rect = { OFFSET_X + x * (CHESSBOARD_SIZE / COLS), OFFSET_Y + y * (CHESSBOARD_SIZE / ROWS), CHESSBOARD_SIZE / COLS, CHESSBOARD_SIZE / ROWS };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}

int Piece::getX() const { return x; }
int Piece::getY() const { return y; }
Color Piece::getColor() const { return color; }
void Piece::setPosition(int x, int y) { this->x = x; this->y = y; }



// //Pawns
//     pieces.push_back(new Pawn(0, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
//     pieces.push_back(new Pawn(1, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
//     pieces.push_back(new Pawn(2, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
//     pieces.push_back(new Pawn(3, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
//     pieces.push_back(new Pawn(4, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
//     pieces.push_back(new Pawn(5, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
//     pieces.push_back(new Pawn(6, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
//     pieces.push_back(new Pawn(7, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
//     pieces.push_back(new Pawn(0, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
//     pieces.push_back(new Pawn(1, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
//     pieces.push_back(new Pawn(2, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
//     pieces.push_back(new Pawn(3, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
//     pieces.push_back(new Pawn(4, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
//     pieces.push_back(new Pawn(5, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
//     pieces.push_back(new Pawn(6, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
//     pieces.push_back(new Pawn(7, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
    
//     //Rooks(Towers)

//     //Knights

//     //Bishops

//     //King

//     //Queen