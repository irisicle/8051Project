//
// Created by Iris Chow on 2026-02-25.
//

#include "Scene.h"
#include "../factory/EntityFactory.h"
#include "../factory/UIFactory.h"
#include "../ecs/component/Tag.h"
#include "../game/Game.h"
#include "../systems/CameraSystem.h"
#include "../utils/Constants.h"

Scene::Scene(
    const SceneType sceneType,
    const char* sceneName,
    const char* mapPath,
    const int windowWidth,
    const int windowHeight
    ) : name (sceneName), type(sceneType) {

    if (sceneType == SceneType::MAIN_MENU) {
        initMainMenu(windowWidth, windowHeight);
        return;
    }

    initGameplay(mapPath, windowWidth, windowHeight);
}

void Scene::initialize() {
    world.initialize();
}

void Scene::update(const float deltaTime, const SDL_Event& event) {
    world.update(deltaTime, event, type);
    CameraSystem::update(world.getEntities(), camera);
    selectionHighlightSystem.update(world.getEntities(), camera);
}

void Scene::render(SDL_Renderer* renderer) {
    world.render(renderer, camera);
    selectionHighlightSystem.draw(renderer);
}

void Scene::initMainMenu(const int windowWidth, const int windowHeight) {

    // Spawn main menu
    UIFactory::createMainMenu(world, windowWidth, windowHeight);
    auto& overlay = UIFactory::createSettingsOverlay(world, windowWidth, windowHeight);

    // Spawn UI components
    UIFactory::createCogButton(world, windowWidth, windowHeight, overlay);

    // Set camera
    camera = Camera{
        SDL_FRect{
            0.0f,
            0.0f,
            static_cast<float>(windowWidth),
            static_cast<float>(windowHeight)
        },
        static_cast<float>(windowWidth),
        static_cast<float>(windowHeight)
    };

}

void Scene::initGameplay(const char* mapPath, const int windowWidth, const int windowHeight) {

    // Load world map
    world.setMap(loader.load(mapPath, world));

    // Set world camera
    camera = Camera{
        SDL_FRect{
            0.0f,
            0.0f,
            static_cast<float>(windowWidth),
            static_cast<float>(windowHeight)
        },
        // World constraints
        static_cast<float>(world.getMap().width * Constants::TILE_SIZE),
        static_cast<float>(world.getMap().height * Constants::TILE_SIZE)
    };

    // Spawn world entities
    EntityFactory::createPlayer(world);

    for (const auto& marker : world.getMap().spawnMarkers) {
        EntityFactory::createCow(world, Vector2D(marker.position.x, marker.position.y));
    }

    // Add scene state
    auto& state(world.createEntity());
    state.addComponent<SceneState>();

}
