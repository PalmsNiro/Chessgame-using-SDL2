#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"
#include "Chessboard.hpp"
#include <vector>
#include <utility>

class Bishop : public Piece
{
public:
    Bishop(PieceName name, int x, int y, Color color, const std::string &texturePath);

    bool isPathClear(const Chessboard &board, Color color) const override;
    std::vector<std::pair<int, int>> validMoves(const Chessboard &chessboard) const override;
};

#endif