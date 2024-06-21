#include "Game.hpp"
#include "GameStates.hpp"

int main(int argc, char *argv[]) {
    Game* game = new Game(); // Constructor calls Init() Method

    GameState currentState = GameState::MAIN_MENU;

    bool isRunning = true;
    while (isRunning) {
        switch (currentState) {
            case GameState::MAIN_MENU:
                // Handle main menu logic here
                // For simplicity, transition directly to playing state
                currentState = GameState::PLAYING;
                break;

            case GameState::PLAYING:
                if (game->Run()) {
                    std::cout << "Error: " << SDL_GetError() << std::endl;
                    isRunning = false;
                }
                // Temporary: simulate transition to GAME_OVER state after running the game
                currentState = GameState::GAME_OVER;
                break;

            case GameState::PAUSED:
                // Handle paused state logic here
                break;

            case GameState::GAME_OVER:
                // Handle game over logic here
                isRunning = false; // End the loop for now
                break;

            default:
                std::cout << "Unknown game state!" << std::endl;
                isRunning = false;
                break;
        }
    }

    delete game; // Destructor calls Close() Method

    return EXIT_SUCCESS;
}
