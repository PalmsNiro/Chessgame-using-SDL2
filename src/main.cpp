#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "common.hpp"
#include "Pawn.hpp"


SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) {
        std::cout << "LoadTexture Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

Piece* getPieceAtPosition(int x, int y, const std::vector<Piece*>& pieces) {
    for (Piece* piece : pieces) {
        if (piece->getX() == x && piece->getY() == y) {
            return piece;
        }
    }
    return nullptr;
}

bool isValidMove(Piece* piece, int newX, int newY) {
    std::vector<std::pair<int, int>> moves = piece->validMoves();
    for (const auto& move : moves) {
        if (move.first == newX && move.second == newY) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Texture *backgroundTexture = loadTexture("images/board/blue-marble.jpg", renderer);
    if (backgroundTexture == nullptr) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Create the pieces
    std::vector<Piece*> pieces;
    pieces.push_back(new Pawn(0, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    pieces.push_back(new Pawn(0, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));

    Piece* selectedPiece = nullptr;

    SDL_Event event;
    bool isRunning = true;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                int boardX = (mouseX - OFFSET_X) / (CHESSBOARD_SIZE / COLS);
                int boardY = (mouseY - OFFSET_Y) / (CHESSBOARD_SIZE / ROWS);

                if (boardX >= 0 && boardX < COLS && boardY >= 0 && boardY < ROWS) {
                    if (selectedPiece == nullptr) {
                        // Select piece
                        selectedPiece = getPieceAtPosition(boardX, boardY, pieces);
                    } else {
                        // Check if move is valid
                        if (isValidMove(selectedPiece, boardX, boardY)) {
                            selectedPiece->setPosition(boardX, boardY);
                        }
                        selectedPiece = nullptr;
                    }
                }
            }
        }

        // Render the black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render the chessboard image in the center
        SDL_Rect chessboardRect = { OFFSET_X, OFFSET_Y, CHESSBOARD_SIZE, CHESSBOARD_SIZE };
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &chessboardRect);

        // Render chess pieces
        for (Piece* piece : pieces) {
            piece->render(renderer);
        }

        SDL_RenderPresent(renderer); // Present the current rendering

        SDL_Delay(1000 / 60); // Delay to limit the frame rate to 60 FPS
    }

    // Clean up
    for (Piece* piece : pieces) {
        delete piece;
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
