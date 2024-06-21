#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"
#include "Chessboard.hpp"
#include <vector>
#include <utility>

class King : public Piece
{
public:
    King(PieceName name, int x, int y, Color color, const std::string &texturePath);

    bool isPathClear(const Chessboard &board, Color color) const override;
    std::vector<std::pair<int, int>> validMoves(const Chessboard &chessboard) const override;
};

#endif