#ifndef PIECE_HPP_INCLUDED
#define PIECE_HPP_INCLUDED

enum class PieceName
{
    Empty,
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

class Piece
{
protected:
    PieceName name = PieceName::Empty;
    bool isWhite = false;
    int position_X = -1;
    int position_Y = -1;
    bool isAlive = false;

public:
    Piece();
    ~Piece();
    

};

#endif