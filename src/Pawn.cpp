#include "Pawn.hpp"

Pawn::Pawn(int x, int y, Color color, const std::string& texturePath)
    : Piece(x, y, color, texturePath) {}

std::vector<std::pair<int, int>> Pawn::validMoves() const {
    std::vector<std::pair<int, int>> moves;
    if (color == Color::WHITE) {
        if (y > 0) moves.emplace_back(x, y - 1);
        if (y == 6) moves.emplace_back(x, y - 2); // Initial double move
    } else {
        if (y < 7) moves.emplace_back(x, y + 1);
        if (y == 1) moves.emplace_back(x, y + 2); // Initial double move
    }
    return moves;
}
