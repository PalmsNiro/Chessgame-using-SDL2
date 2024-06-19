#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <vector>
#include "Piece.hpp"
#include "Chessboard.hpp"

void checkDirection(int startX, int startY, int dx, int dy, int maxDistance, const Chessboard &chessboard, Color color, std::vector<std::pair<int, int>> &moves);

#endif // UTILS_HPP_INCLUDED
