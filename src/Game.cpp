#include "Game.hpp"

// When calling constructor in main with new, Init gets called
Game::Game()
{
    Init();
};

Game::~Game()
{
    std::cout << "Desctructor called";
    Close();
};

/*

    * class functions

*/
SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren)
{
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr)
    {
        std::cout << "LoadTexture Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

Piece *getPieceAtPosition(int x, int y, const std::vector<Piece *> &pieces)
{
    for (Piece *piece : pieces)
    {
        if (piece->getX() == x && piece->getY() == y)
        {
            return piece;
        }
    }
    return nullptr;
}

bool isValidMove(Piece *piece, int newX, int newY)
{
    std::vector<std::pair<int, int>> moves = piece->validMoves();
    for (const auto &move : moves)
    {
        if (move.first == newX && move.second == newY)
        {
            return true;
        }
    }
    return false;
}

/*

    class Methods

*/

/*
    Game::Init
*/
int Game::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    backgroundTexture = loadTexture("images/board/blue-marble.jpg", renderer);
    if (backgroundTexture == nullptr)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
    Game::Run
*/
int Game::Run()
{
    this->createPieces();

    Piece *selectedPiece = nullptr;

    SDL_Event event;
    bool isRunning = true;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                int boardX = (mouseX - OFFSET_X) / (CHESSBOARD_SIZE / COLS);
                int boardY = (mouseY - OFFSET_Y) / (CHESSBOARD_SIZE / ROWS);

                if (boardX >= 0 && boardX < COLS && boardY >= 0 && boardY < ROWS) // If click is on ChessBoard
                {
                    if (selectedPiece == nullptr) // If no piece has been selected(clicked on) yet
                    {
                        // Select piece clicked on
                        selectedPiece = getPieceAtPosition(boardX, boardY, piecesAlive);
                    }
                    else // a piece has been selected and the next click is where we put it down if possible
                    {
                        // Check if move is valid
                        if (isValidMove(selectedPiece, boardX, boardY))
                        {
                            this->removePieceFromBoard(boardX, boardY);
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
        SDL_Rect chessboardRect = {OFFSET_X, OFFSET_Y, CHESSBOARD_SIZE, CHESSBOARD_SIZE};
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &chessboardRect);

        // Render chess pieces
        for (Piece *piece : piecesAlive)
        {
            piece->render(renderer);
        }

        SDL_RenderPresent(renderer); // Present the current rendering

        SDL_Delay(1000 / 60); // Delay to limit the frame rate to 60 FPS
    }

    return EXIT_SUCCESS;
}

/*
    Game::Close
*/
int Game::Close()
{
    // Clean up
    for (Piece *piece : piecesAlive)
    {
        delete piece;
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

void Game::createPieces()
{
    // Create the pieces
    piecesAlive.push_back(new Pawn(0, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    piecesAlive.push_back(new Pawn(0, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
}

Piece *Game::removePieceFromBoard(int boardX, int boardY)
{
    Piece *removedPiece = nullptr;

    for (auto it = piecesAlive.begin(); it != piecesAlive.end(); ++it)
    {
        Piece *piece = *it;
        if (piece->getX() == boardX && piece->getY() == boardY)
        {
            removedPiece = piece;
            piecesDead.push_back(piece);
            piecesAlive.erase(it);
            break;
        }
    }

    return removedPiece;
}