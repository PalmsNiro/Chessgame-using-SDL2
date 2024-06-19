#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"
#include "Chessboard.hpp"
#include <vector>
#include <utility>

class Pawn : public Piece {
public:
    Pawn(PieceName name, int x, int y, Color color, const std::string& texturePath);
    
    bool isPathClear(const Chessboard& board, Color color) const override;
    bool hasCrossRightOponent(const Chessboard& chessboard, Color color) const;
    bool hasCrossLeftOponent(const Chessboard& chessboard, Color color) const;
    std::vector<std::pair<int, int>> validMoves(const Chessboard& chessboard) const override;
};

#endif // PAWN_HPP
