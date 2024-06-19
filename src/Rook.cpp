#include "Rook.hpp"

Rook::Rook(PieceName name, int x, int y, Color color, const std::string &texturePath) : Piece(name, x, y, color, texturePath) {}

bool Rook::isPathClear(const Chessboard &board, Color color) const
{

    return false;
}

std::vector<std::pair<int, int>> Rook::validMoves(const Chessboard &chessboard) const {
    std::vector<std::pair<int, int>> moves;
    int x = this->getX();
    int y = this->getY();
    Color color = this->getColor();

    std::cout << "Rook at (" << x << ", " << y << ")\n";

    bool northDone = false;
    bool eastDone = false;
    bool southDone = false;
    bool westDone = false;
    Piece *piece = nullptr;

    for (int i = 1; i < 8; i++) {
        // Check North
        if (!northDone) {
            int newY = y - i;
            if (newY >= 0) {
                piece = chessboard.getPieceAt(x, newY);
                // std::cout << "Piece at (" << x << ", " << newY << ")\n";
                if (piece == nullptr) {
                    moves.emplace_back(x, newY);
                } else if (color != piece->getColor()) {
                    moves.emplace_back(x, newY);
                    northDone = true;
                } else {
                    northDone = true;
                }
            } else {
                northDone = true;
            }
        }

        // Check East
        if (!eastDone) {
            int newX = x + i;
            if (newX < 8) {
                piece = chessboard.getPieceAt(newX, y);
                if (piece == nullptr) {
                    moves.emplace_back(newX, y);
                } else if (color != piece->getColor()) {
                    moves.emplace_back(newX, y);
                    eastDone = true;
                } else {
                    eastDone = true;
                }
            } else {
                eastDone = true;
            }
        }

        // Check South
        if (!southDone) {
            int newY = y + i;
            if (newY < 8) {
                piece = chessboard.getPieceAt(x, newY);
                if (piece == nullptr) {
                    moves.emplace_back(x, newY);
                } else if (color != piece->getColor()) {
                    moves.emplace_back(x, newY);
                    southDone = true;
                } else {
                    southDone = true;
                }
            } else {
                southDone = true;
            }
        }

        // Check West
        if (!westDone) {
            int newX = x - i;
            if (newX >= 0) {
                piece = chessboard.getPieceAt(newX, y);
                if (piece == nullptr) {
                    moves.emplace_back(newX, y);
                } else if (color != piece->getColor()) {
                    moves.emplace_back(newX, y);
                    westDone = true;
                } else {
                    westDone = true;
                }
            } else {
                westDone = true;
            }
        }
    }
    return moves;
}