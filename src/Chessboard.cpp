// void drawChessboard(SDL_Renderer* renderer) {
//     bool isDarkbrown = false;
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Black background
//     SDL_RenderClear(renderer); // Clear the renderer with black color

//     for (int row = 0; row < ROWS; ++row) {
//         for (int col = 0; col < COLS; ++col) {
//             if (isDarkbrown) {
//                 SDL_SetRenderDrawColor(renderer, 207, 137, 72, SDL_ALPHA_OPAQUE); // Darkbrown color
//             } else {
//                 SDL_SetRenderDrawColor(renderer, 255, 204, 156, SDL_ALPHA_OPAQUE); // Lightbrown color
//             }
//             SDL_Rect square = { OFFSET_X + col * (CHESSBOARD_SIZE / COLS), OFFSET_Y + row * (CHESSBOARD_SIZE / ROWS), CHESSBOARD_SIZE / COLS, CHESSBOARD_SIZE / ROWS };
//             SDL_RenderFillRect(renderer, &square);
//             isDarkbrown = !isDarkbrown; // Alternate color
//         }
//         isDarkbrown = !isDarkbrown; // Alternate starting color for next row
//     }
// }