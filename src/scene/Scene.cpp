//
// Created by Iris Chow on 2026-02-25.
//

#include "Scene.h"
#include "../factory/EntityFactory.h"
#include "../factory/UIFactory.h"
#include "../ecs/component/Tag.h"
#include "../game/Game.h"

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

void Scene::initMainMenu(const int windowWidth, const int windowHeight) {

    // Create camera
    auto& camera(world.createEntity());
    camera.addComponent<Camera>();

    // Spawn main menu
    UIFactory::createMainMenu(world, windowWidth, windowHeight);
    auto& overlay = UIFactory::createSettingsOverlay(world, windowWidth, windowHeight);

    // Spawn UI components
    UIFactory::createCogButton(world, windowWidth, windowHeight, overlay);
}

void Scene::initGameplay(const char* mapPath, const int windowWidth, const int windowHeight) {

    // Load world map
    world.setMap(MapLoader::load(mapPath, world));

    // Create world camera
    EntityFactory::createCamera(world, windowWidth, windowHeight);

    // Spawn world entities
    EntityFactory::createPlayer(world);

    for (const auto& marker : world.getMap().spawnMarkers) {
        EntityFactory::createCow(world, Vector2D(marker.position.x, marker.position.y));
    }

    // Add scene state
    auto& state(world.createEntity());
    state.addComponent<SceneState>();
}
