#include <SDL2/SDL.h>
#include <iostream>

#include "../include/board.h"

#define ASSERT(X)                                                                           \
    if (!X)                                                                                 \
    {                                                                                       \
        std::cout << #X << " at line " << __LINE__ << " in file " << __FILE__ << std::endl; \
        return 1;                                                                           \
    }

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    Board board{};
    std::cout << board.generate_fenstring() << std::endl;
    ASSERT((board.generate_fenstring() == initial_board_fen_v));
    while (board.is_running())
    {
        board.handle_events();
        board.draw();
        board.parse_fenstring();
        board.render();
    }

    return 0;
}