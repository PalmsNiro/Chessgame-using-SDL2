#include "Game.hpp"

Game* game = new Game(); //Constructor calls Init() Method

int main(int argc, char *argv[]) {
    if(game->Run()){
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Error: " << SDL_GetError() << std::endl;

    delete game; //destructor calls Close() Method

    return EXIT_SUCCESS;
}
