#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"
#include "Chessboard.hpp"
#include <vector>
#include <utility>

class Queen : public Piece
{
public:
    Queen(PieceName name, int x, int y, Color color, const std::string &texturePath);

    bool isPathClear(const Chessboard &board, Color color) const override;
    std::vector<std::pair<int, int>> validMoves(const Chessboard &chessboard) const override;
};

#endif