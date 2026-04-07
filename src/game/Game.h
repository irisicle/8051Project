//
// Created by Iris Chow on 2026-01-14.
//

// #ifndef INC_8051PROJECT_GAME_H
// #define INC_8051PROJECT_GAME_H
//
// #endif //INC_8051PROJECT_GAME_H

#pragma once
#include <SDL3/SDL.h>

#include "../ecs/core/World.h"
#include "../manager/SceneManager.h"
#include "../manager/AudioManager.h"

struct GameState{
    int playerHealth;
};

class Game {
public:
    Game();
    ~Game();

    // These are the types that SDL uses
    void init(const char *title, int width, int height, bool fullscreen);

    // Game loop functions (handleEvents, update, render)
    void handleEvents(); //Checks for input and system events
    void update(float deltaTime); //Handles the game logic and changes to game state
    void render(); //Handles the drawing of the current game state to the screen

    // Free up resources
    void destroy() const;

    [[nodiscard]] bool running() const {
        return isRunning;
    }

    SDL_Renderer* renderer = nullptr;

    AudioManager audioManager;
    SceneManager sceneManager;

    static std::function<void(std::string)> onSceneChangeRequest;
    static GameState gameState;

private:
    int frameCount = 0;
    bool isRunning = false;

    SDL_Window* window = nullptr;
    SDL_Event event{};

    Uint32 lastColorChangeMs = 0;

    // SDL stores color channels as 8-bit unsigned
    // range is 0-255
    Uint8 r{}, g{}, b{}, a{};
};
