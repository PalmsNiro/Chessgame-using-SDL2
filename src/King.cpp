#include "King.hpp"
#include "Utils.hpp"

King::King(PieceName name, int x, int y, Color color, const std::string &texturePath) : Piece(name, x, y, color, texturePath) {}

bool King::isPathClear(const Chessboard &board, Color color) const
{
    return true;
}

std::vector<std::pair<int, int>> King::validMoves(const Chessboard &chessboard) const
{
    std::vector<std::pair<int, int>> moves;
    int x = this->getX();
    int y = this->getY();
    Color color = this->getColor();

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (!i && !j) // Wenn beide loop variablen 0 sind(position des Königs)
            {
                continue;
            }

            int newX = x + i;
            int newY = y + j;

            if (newX >= 0 && newX < chessboard.board.size() && newY >= 0 && newY < chessboard.board[0].size()) // check if new point is in bounds
            {
                Piece *piece = chessboard.getPieceAt(newX, newY);

                // If the square is empty or contains an opponent's piece, it's a valid move
                if (piece == nullptr || piece->getColor() != color)
                {
                    moves.emplace_back(newX, newY);
                }
            }
        }
    }

    return moves;
}