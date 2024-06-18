#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(int x, int y, Color color, const std::string& texturePath);
    virtual std::vector<std::pair<int, int>> validMoves() const override;
};

#endif // PAWN_HPP
