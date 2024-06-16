#include <iostream>
#include <common.hpp>

void drawChessboard(SDL_Renderer* renderer) {
    bool isDarkbrown = false;
    SDL_SetRenderDrawColor(renderer, 207, 137, 72, SDL_ALPHA_OPAQUE); // Darkbrown color
    SDL_RenderClear(renderer); // Clear the renderer with white color

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (isDarkbrown) {
                SDL_SetRenderDrawColor(renderer, 207, 137, 72, SDL_ALPHA_OPAQUE); // Darkbrown color
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 204, 156, SDL_ALPHA_OPAQUE); // Lightbrown color
            }
            SDL_Rect square = { col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            SDL_RenderFillRect(renderer, &square);
            isDarkbrown = !isDarkbrown; // Alternate color
        }
        isDarkbrown = !isDarkbrown; // Alternate starting color for next row
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error: " << SDL_GetError() << std::endl;
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

    SDL_Event event;
    bool isRunning = true;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        drawChessboard(renderer);

        SDL_RenderPresent(renderer); // Present the current rendering

        // SDL_Delay(1000 / 60); // Delay to limit the frame rate to 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
