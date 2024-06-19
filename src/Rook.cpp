#include "Rook.hpp"

Tower::Tower(PieceName name, int x, int y, Color color, const std::string &texturePath) : Piece(name, x, y, color, texturePath) {}

bool Tower::isPathClear(const Chessboard &board, Color color) const {

    return false;
}
std::vector<std::pair<int, int>> Tower::validMoves(const Chessboard &chessboard) const {
    std::vector<std::pair<int, int>> moves;
    int x = this->getX();
    int y = this->getY();
    Color color = this->getColor();

    return moves;
}