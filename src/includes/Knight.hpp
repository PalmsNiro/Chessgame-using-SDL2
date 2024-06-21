#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"
#include "Chessboard.hpp"
#include <vector>
#include <utility>

class Knight : public Piece
{
public:
    Knight(PieceName name, int x, int y, Color color, const std::string &texturePath);

    bool isPathClear(const Chessboard &board, Color color) const override;
    std::vector<std::pair<int, int>> validMoves(const Chessboard &chessboard) const override;
};

#endif