#include "Bishop.hpp"
#include "Utils.hpp"

Bishop::Bishop(PieceName name, int x, int y, Color color, const std::string &texturePath) : Piece(name, x, y, color, texturePath) {}

bool Bishop::isPathClear(const Chessboard &board, Color color) const
{
    return true;
}

std::vector<std::pair<int, int>> Bishop::validMoves(const Chessboard &chessboard) const
{
    std::vector<std::pair<int, int>> moves;
    int x = this->getX();
    int y = this->getY();
    Color color = this->getColor();

    // Directions for Bishop (north, east, south, west)
    std::vector<std::pair<int, int>> directions = {
        {1, 1}, // North/East
        {1, -1},  // Sout/East
        {-1, 1},  // South/West
        {-1, -1}  // North/West
    };

    for (const auto &direction : directions)
    {
        checkDirection(x, y, direction.first, direction.second, 7, chessboard, color, moves);
    }

    return moves;
}