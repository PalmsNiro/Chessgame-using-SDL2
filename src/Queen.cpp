#include "Queen.hpp"
#include "Utils.hpp"

Queen::Queen(PieceName name, int x, int y, Color color, const std::string &texturePath) : Piece(name, x, y, color, texturePath) {}

bool Queen::isPathClear(const Chessboard &board, Color color) const
{
    return true;
}

std::vector<std::pair<int, int>> Queen::validMoves(const Chessboard &chessboard) const {
    std::vector<std::pair<int, int>> moves;
    int x = this->getX();
    int y = this->getY();
    Color color = this->getColor();

    // Directions for Queen (north, east, south, west)
    std::vector<std::pair<int, int>> directions = {
        {0, -1}, // North
        {1, 0},  // East
        {0, 1},  // South
        {-1, 0},  // West
        {1, 1}, // North/East
        {1, -1},  // Sout/East
        {-1, 1},  // South/West
        {-1, -1}  // North/West
    };

    for (const auto &direction : directions) {
        checkDirection(x, y, direction.first, direction.second, 7, chessboard, color, moves);
    }

    return moves;
}