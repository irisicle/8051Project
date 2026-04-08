//
// Created by Iris Chow on 2026-01-14
//

#include "Game.h"
#include <iostream>
#include <ostream>
#include <random>

#include "../manager/AssetManager.h"
#include "../manager/TextureManager.h"

GameState Game::gameState{};
std::function<void(std::string)> Game::onSceneChangeRequest;

Game::Game() = default;

Game::~Game()
{
    destroy();
}

void Game::init(
    const char* title,
    const int width,
    const int height,
    const bool fullscreen)
{
    int flags = 0;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    // Initialize SDL library
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        std::cout << "Subsystem initialized..." << std::endl;
        window = SDL_CreateWindow(title, width, height, flags);
        if (window) {
            std::cout << "Window created..." << std::endl;
        }

        // Windows will be Direct3D (DirectX)
        // MAC will likely be Metal, OpenGL
        renderer = SDL_CreateRenderer(window, nullptr);

        if (renderer) {
            std::cout << "Renderer created..." << std::endl;
        } else {
            std::cout << "Renderer could not be created..." << std::endl;
            return;
        }

        // Vsync asks SDL to wait for the monitor’s refresh before showing the next frame
        // This reduces visible tearing
        if (!SDL_SetRenderVSync(renderer, 1)) {
            std::cout << "Vsync could not be set..." << SDL_GetError() << std::endl;
        }

        isRunning = true;
    }

    else {
        isRunning = false;
    }

    // Load audio
    audioManager.loadAudio("theme", "../asset/audio/pixel_music.mp3");
    audioManager.loadAudio("till", "../asset/audio/blup_1.wav");

    // Load font
    AssetManager::loadFont("../asset/ui/fonts/pixel_font.ttf", "pixel", 16);


    // Load assets
    AssetManager::loadAnimation("player", "../asset/animations/character/player_animations.xml");
    AssetManager::loadAnimation("cow", "../asset/animations/animals/cow_animations.xml");

    // Load scenes
    sceneManager.loadScene(SceneType::MAIN_MENU, "mainmenu", nullptr, width, height);
    sceneManager.loadScene(SceneType::GAMEPLAY, "level1", "../asset/map.tmx", width, height);

    // Play music
    audioManager.playMusic("theme");

    // Init game data/state
    gameState.playerHealth = 5;

    // Start gameplay
    sceneManager.changeSceneDeferred("mainmenu");

    // Resolve scene callback
    onSceneChangeRequest = [this](const std::string& sceneName) {

        if (sceneManager.currentScene->getSceneName() == "level2" && sceneName == "level2") {
            std::cout << "You win!" << std::endl;
            isRunning = false;
            return;
        }

        if (sceneName == "gameover") {
            std::cout << "Game Over!" << std::endl;
            isRunning = false;
            return;
        }

        sceneManager.changeSceneDeferred(sceneName);
    };
}

void Game::handleEvents() {

    // SDL listens to the OS for input events internally, and it adds them to a queue
    // Checks for next event, if an event is available it will remove from the queue and store in event
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_EVENT_QUIT: //Usually triggered when the user closes the window
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update(const float deltaTime) {
    sceneManager.update(deltaTime, event);
}

void Game::render() {

    // Color change
    if (const Uint32 startTime = SDL_GetTicks(); startTime - lastColorChangeMs >= 1000) {
        lastColorChangeMs = startTime;
        r = 255;
        g = 255;
        b = 255;
        a = 255;
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    // Every frame the renderer is cleared with the draw color
    SDL_RenderClear(renderer);

    // Render scene
    sceneManager.render(renderer);

    // Swaps the back buffer to the screen
    SDL_RenderPresent(renderer);
}

void Game::destroy() const {
    TextureManager::clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game destroyed..." << std::endl;
}
