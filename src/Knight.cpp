#include "Knight.hpp"
#include "Utils.hpp"

Knight::Knight(PieceName name, int x, int y, Color color, const std::string &texturePath) : Piece(name, x, y, color, texturePath) {}

bool Knight::isPathClear(const Chessboard &board, Color color) const
{
    return true;
}

std::vector<std::pair<int, int>> Knight::validMoves(const Chessboard &chessboard) const
{
    std::vector<std::pair<int, int>> moves;
    int x = this->getX();
    int y = this->getY();
    Color color = this->getColor();

    // Directions for Knight
    std::vector<std::pair<int, int>> directions = {
        {-1, -2}, // Up-Left
        {1, -2},  // Up-Right
        {2, -1},  // Right-Up
        {2, 1},   // Right-Down
        {1, 2},   // Down-Right
        {-1, 2},  // Down-Left
        {-2, 1},  // Left-Down
        {-2, -1}  // Left-Up
    };

    int newX;
    int newY;

    for (const auto &direction : directions)
    {
        newX = x + direction.first;
        newY = y + direction.second;
        if (newX >= 0 && newX < chessboard.board.size() && newY >= 0 && newY < chessboard.board[0].size()) // check if new point is in bounds
        {
            Piece *piece = chessboard.getPieceAt(newX, newY);

            // If the square is empty or contains an opponent's piece, it's a valid move
            if (piece == nullptr || piece->getColor() != color) {
                moves.emplace_back(newX, newY);
            }
        }
    }

    return moves;
}