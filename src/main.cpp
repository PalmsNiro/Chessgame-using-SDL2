#include "Game.hpp"

Game* game = new Game(); //Constructor calls Init() Method

int main(int argc, char *argv[]) {
    game->Run();

    delete game; //destructor calls Close() Method

    return EXIT_SUCCESS;
}
