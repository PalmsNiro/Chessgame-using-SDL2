#include "Pawn.hpp"
#include <iostream>

Pawn::Pawn(PieceName name, int x, int y, Color color, const std::string &texturePath)
    : Piece(name, x, y, color, texturePath) {}

bool Pawn::isPathClear(const Chessboard &chessboard, Color color) const
{
    int forwardDirection = (color == Color::WHITE) ? -1 : 1;
    int nextY = this->getY() + forwardDirection;
    if (nextY < 0 || nextY >= chessboard.board[0].size())
    {
        return false;
    }
    if (chessboard.getPieceAt(this->getX(), nextY) == nullptr)
    {
        return true;
    }
    return false;
}

bool Pawn::hasCrossRightOponent(const Chessboard &chessboard, Color color) const
{
    int forwardDirection = (color == Color::WHITE) ? -1 : 1;
    int nextY = this->getY() + forwardDirection;
    int nextX = this->getX() + 1;
    if (nextX < 0 || nextX >= chessboard.board.size() || nextY < 0 || nextY >= chessboard.board[0].size())
    {
        return false;
    }
    Piece *piece = chessboard.getPieceAt(nextX, nextY);
    if (piece != nullptr && piece->getColor() != color)
    {
        return true;
    }
    return false;
}

bool Pawn::hasCrossLeftOponent(const Chessboard &chessboard, Color color) const
{
    int forwardDirection = (color == Color::WHITE) ? -1 : 1;
    int nextY = this->getY() + forwardDirection;
    int nextX = this->getX() - 1;
    if (nextX < 0 || nextX >= chessboard.board.size() || nextY < 0 || nextY >= chessboard.board[0].size())
    {
        return false;
    }
    Piece *piece = chessboard.getPieceAt(nextX, nextY);
    if (piece != nullptr && piece->getColor() != color)
    {
        return true;
    }
    return false;
}

std::vector<std::pair<int, int>> Pawn::validMoves(const Chessboard &chessboard) const
{
    std::vector<std::pair<int, int>> moves;
    int x = this->getX();
    int y = this->getY();
    Color color = this->getColor();

    int forwardDirection = (color == Color::WHITE) ? -1 : 1;
    int nextY = y + forwardDirection;

    if (this->isPathClear(chessboard, color))
    {
        moves.emplace_back(x, nextY);
        if (color == Color::WHITE && y == 6 && chessboard.getPieceAt(x, y - 1) == nullptr && chessboard.getPieceAt(x, y - 2) == nullptr)
        {
            moves.emplace_back(x, y - 2);
        }
        else if (color == Color::BLACK && y == 1 && chessboard.getPieceAt(x, y + 1) == nullptr && chessboard.getPieceAt(x, y + 2) == nullptr)
        {
            moves.emplace_back(x, y + 2);
        }
    }

    if (this->hasCrossRightOponent(chessboard, color))
    {
        moves.emplace_back(x + 1, nextY);
    }
    if (this->hasCrossLeftOponent(chessboard, color))
    {
        moves.emplace_back(x - 1, nextY);
    }

    return moves;
}
