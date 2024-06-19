// Chessboard.hpp
#ifndef CHESSBOARD_HPP_INCLUDED
#define CHESSBOARD_HPP_INCLUDED

#include <vector>
// #include "Piece.hpp"

class Piece;  // Forward declaration

class Chessboard {
public:
    std::vector<std::vector<Piece*>> board;
    
    // Chessboard();
    Chessboard(int width, int height);

    Piece* getPieceAt(int x, int y) const;
    void setPieceAt(int x, int y, Piece* piece);
};

#endif // CHESSBOARD_HPP_INCLUDED
