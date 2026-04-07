#include "game/Game.h"
#include "utils/Constants.h"

// Global variable
Game *game = nullptr;

int main() {
    constexpr int FPS = 60; //60 is the closest refresh rate of most our monitors, 30fps is half the work
    constexpr int desiredFrameRate = 1000 / FPS; //16ms per frame

    Uint64 ticks = SDL_GetTicks();
    float deltaTime = 0.0f;

    game = new Game();
    game->init("8051 PROJECT Engine", Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, false);

    // Game loop
    while (game->running()) {
        const Uint64 currentTicks = SDL_GetTicks();
        deltaTime = static_cast<float>(currentTicks - ticks) / 1000.0f;
        ticks = currentTicks;

        game->handleEvents();
        game->update(deltaTime);
        game->render();

        // Frame limiter
        // Keeps the game running at the desired frame rate
        // If the actual frame took less time than the desired frame, then delay the difference
        if (const auto actualFrameRate = static_cast<float>(SDL_GetTicks() - ticks);
        desiredFrameRate > actualFrameRate) {
            SDL_Delay(static_cast<unsigned>(desiredFrameRate - actualFrameRate));
        }
    }

    // Clean up pointer
    delete game;

    return 0;
}

