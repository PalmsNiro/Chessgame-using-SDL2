#include "Game.hpp"

Game::Game() : chessboard(8, 8)
{
    if (Init())
        std::cout << "Init() failed";
}

Game::~Game()
{
    std::cout << "Destructor called";
    Close();
}

SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren)
{
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr)
    {
        std::cout << "LoadTexture Error: " << SDL_GetError() << std::endl;
    }
    return texture;
}

// Piece *getPieceAtPosition(int x, int y, const std::vector<Piece *> &pieces)
// {
//     for (Piece *piece : pieces)
//     {
//         if (piece->getX() == x && piece->getY() == y)
//         {
//             return piece;
//         }
//     }
//     return nullptr;
// }

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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Enable blending mode for the renderer
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

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

int Game::Run()
{
    this->createPieces();

    Piece *selectedPiece = nullptr;
    Color turnColor = Color::WHITE;

    SDL_Event event;
    bool isRunning = true;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
                return EXIT_FAILURE; // Indicate that the game was interrupted
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                int boardX = (mouseX - OFFSET_X) / (CHESSBOARD_SIZE / COLS);
                int boardY = (mouseY - OFFSET_Y) / (CHESSBOARD_SIZE / ROWS);

                if (boardX >= 0 && boardX < COLS && boardY >= 0 && boardY < ROWS)
                {
                    if (selectedPiece == nullptr)
                    {
                        Piece *pieceClickedOn = chessboard.getPieceAt(boardX, boardY);
                        if (pieceClickedOn && pieceClickedOn->getColor() == turnColor && pieceClickedOn->validMoves(chessboard).size())
                        {
                            selectedPiece = pieceClickedOn;

                            // Show valid moves
                            this->showAvailAbleMoves(selectedPiece->validMoves(chessboard));
                        }
                    }
                    else if (selectedPiece != nullptr)
                    {
                        if (isValidMove(selectedPiece, boardX, boardY))
                        {
                            this->removePieceFromBoard(boardX, boardY); // Remove any piece at the target position
                            movePiece(selectedPiece, boardX, boardY);   // Move the selected piece

                            // Switch turn color
                            turnColor = (turnColor == Color::WHITE) ? Color::BLACK : Color::WHITE;
                        }
                        selectedPiece = nullptr;
                        availableMoves.clear(); // Clear available moves after a move is made
                    }
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render the chessboard background
        SDL_Rect chessboardRect = {OFFSET_X, OFFSET_Y, CHESSBOARD_SIZE, CHESSBOARD_SIZE};
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &chessboardRect);

        // Render available moves with transparency
        SDL_SetRenderDrawColor(renderer, 66, 245, 96, 128); // 128 is for 50% transparency
        for (const auto &move : availableMoves)
        {
            int col = move.first;
            int row = move.second;

            SDL_Rect square = {OFFSET_X + col * (CHESSBOARD_SIZE / COLS), OFFSET_Y + row * (CHESSBOARD_SIZE / ROWS), CHESSBOARD_SIZE / COLS, CHESSBOARD_SIZE / ROWS};
            SDL_RenderFillRect(renderer, &square);
        }

        // Render the pieces on top of the available move fields
        for (Piece *piece : piecesAlive)
        {
            if (piece != nullptr) // Ensure piece is not null
        {
            piece->render(renderer);
            }
        }

        // Present the rendered frame
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate to 60 FPS
        SDL_Delay(1000 / 60);
    }

    return EXIT_SUCCESS;
}

int Game::Close()
{
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
    // Pawns
    piecesAlive.push_back(new Pawn(PieceName::PAWN_WHITE, 0, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_WHITE, 1, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_WHITE, 2, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_WHITE, 3, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_WHITE, 4, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_WHITE, 5, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_WHITE, 6, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_WHITE, 7, 6, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Pawn.png"));

    piecesAlive.push_back(new Pawn(PieceName::PAWN_BLACK, 0, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_BLACK, 1, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_BLACK, 2, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_BLACK, 3, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_BLACK, 4, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_BLACK, 5, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_BLACK, 6, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));
    piecesAlive.push_back(new Pawn(PieceName::PAWN_BLACK, 7, 1, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Pawn.png"));

    // Towers
    piecesAlive.push_back(new Rook(PieceName::ROOK_WHITE, 0, 7, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Rook.png"));
    piecesAlive.push_back(new Rook(PieceName::ROOK_WHITE, 7, 7, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Rook.png"));
    piecesAlive.push_back(new Rook(PieceName::ROOK_BLACK, 0, 0, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Rook.png"));
    piecesAlive.push_back(new Rook(PieceName::ROOK_BLACK, 7, 0, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Rook.png"));

    // Bishops
    piecesAlive.push_back(new Bishop(PieceName::BISHOP_WHITE, 2, 7, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Bishop.png"));
    piecesAlive.push_back(new Bishop(PieceName::BISHOP_WHITE, 5, 7, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Bishop.png"));
    piecesAlive.push_back(new Bishop(PieceName::BISHOP_BLACK, 2, 0, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Bishop.png"));
    piecesAlive.push_back(new Bishop(PieceName::BISHOP_BLACK, 5, 0, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Bishop.png"));

    // Knights
    piecesAlive.push_back(new Knight(PieceName::KNIGHT_WHITE, 1, 7, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Knight.png"));
    piecesAlive.push_back(new Knight(PieceName::KNIGHT_WHITE, 6, 7, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Knight.png"));
    piecesAlive.push_back(new Knight(PieceName::KNIGHT_BLACK, 1, 0, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Knight.png"));
    piecesAlive.push_back(new Knight(PieceName::KNIGHT_BLACK, 6, 0, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Knight.png"));

    // Queen
    piecesAlive.push_back(new Queen(PieceName::QUEEN_WHITE, 3, 7, Color::WHITE, "images/staunton/piece/CubesAndPi/White-Queen.png"));
    piecesAlive.push_back(new Queen(PieceName::QUEEN_BLACK, 3, 0, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-Queen.png"));

    // Kings
    piecesAlive.push_back(new King(PieceName::KING_WHITE, 4, 7, Color::WHITE, "images/staunton/piece/CubesAndPi/White-King.png"));
    piecesAlive.push_back(new King(PieceName::KING_BLACK, 4, 0, Color::BLACK, "images/staunton/piece/CubesAndPi/Black-King.png"));

    for (auto piece : piecesAlive)
    {
        chessboard.setPieceAt(piece->getX(), piece->getY(), piece);
    }
}

Piece *Game::removePieceFromBoard(int boardX, int boardY)
{
    Piece *removedPiece = nullptr;

    //
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
    chessboard.setPieceAt(boardX, boardY, nullptr);
    return removedPiece;
}

bool Game::isValidMove(Piece *piece, int newX, int newY)
{
    std::vector<std::pair<int, int>> moves = piece->validMoves(chessboard);
    for (const auto &move : moves)
    {
        if (move.first == newX && move.second == newY)
        {
            return true;
        }
    }
    return false;
}

void Game::movePiece(Piece *piece, int newX, int newY)
{
    std::cout << "Moving piece from (" << piece->getX() << ", " << piece->getY() << ") to (" << newX << ", " << newY << ")" << std::endl;

    // Clear the piece's current position on the board
    chessboard.setPieceAt(piece->getX(), piece->getY(), nullptr);

    // Set the piece's new position
    piece->setPosition(newX, newY);

    // Place the piece in the new position on the board
    chessboard.setPieceAt(newX, newY, piece);

    std::cout << "Piece moved to (" << newX << ", " << newY << ")" << std::endl;
}

void Game::showAvailAbleMoves(const std::vector<std::pair<int, int>> &moves)
{
    availableMoves = moves; // Store the moves to be rendered later
}

void Game::printBoard()
{
    std::cout << "------------------------------------------------\n";
    for (int y = 0; y < chessboard.board.size(); ++y)
    {
        for (int x = 0; x < chessboard.board[y].size(); ++x)
        {
            Piece *piece = chessboard.getPieceAt(x, y);
            if (piece)
            {
                std::cout << piece->getSymbol() << " ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}