#include "Rook.hpp"
#include "Utils.hpp"

Rook::Rook(PieceName name, int x, int y, Color color, const std::string &texturePath) : Piece(name, x, y, color, texturePath) {}

bool Rook::isPathClear(const Chessboard &board, Color color) const
{

    return false;
}

std::vector<std::pair<int, int>> Rook::validMoves(const Chessboard &chessboard) const {
    std::vector<std::pair<int, int>> moves;
    int x = this->getX();
    int y = this->getY();
    Color color = this->getColor();

    // Directions for Rook (north, east, south, west)
    std::vector<std::pair<int, int>> directions = {
        {0, -1}, // North
        {1, 0},  // East
        {0, 1},  // South
        {-1, 0}  // West
    };

    for (const auto &direction : directions) {
        checkDirection(x, y, direction.first, direction.second, 7, chessboard, color, moves);
    }

    return moves;
}