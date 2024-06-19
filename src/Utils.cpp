#include "Utils.hpp"

void checkDirection(int startX, int startY, int dx, int dy, int maxDistance, const Chessboard &chessboard, Color color, std::vector<std::pair<int, int>> &moves) {
    for (int i = 1; i <= maxDistance; ++i) {
        int newX = startX + dx * i;
        int newY = startY + dy * i;

        // Check bounds
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
            break;
        }

        Piece *piece = chessboard.getPieceAt(newX, newY);
        if (piece == nullptr) {
            moves.emplace_back(newX, newY);
        } else {
            if (piece->getColor() != color) {
                moves.emplace_back(newX, newY);
            }
            break;
        }
    }
}
