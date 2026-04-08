//
// Created by Iris Chow on 2026-04-07.
//

#include "World.h"

#include "../../map/MapData.h"
#include "../../systems/MainMenuSystem.h"
#include "../../systems/MouseInputSystem.h"
#include "../../systems/AnimationSystem.h"
#include "../../systems/UIRenderSystem.h"
#include "../../systems/CollisionSystem.h"
#include "../../systems/KeyboardInputSystem.h"
#include "../../systems/MovementSystem.h"
#include "../../systems/CropGrowthSystem.h"
#include "../../systems/EventBindings.h"
#include "../../scene/SceneType.h"
#include "../../systems/PlayerControlSystem.h"
#include "../event/AudioEventQueue.h"

void World::initialize() {
    EventBindings::bind(*this);
}

void World::setMap(MapData newMap) {
    map = std::move(newMap);
}

void World::update(const float deltaTime, const SDL_Event& event, const SceneType sceneType) {
    if (sceneType == SceneType::MAIN_MENU) {
        MainMenuSystem::update(event);
    }

    else {
        EventBindings::bind(*this);
        KeyboardInputSystem::update(entities, event);
        PlayerControlSystem::update(entities);
        MovementSystem::update(entities, deltaTime);
        CollisionSystem::update(*this);
        AnimationSystem::update(entities, deltaTime);
        CropGrowthSystem::update(entities, deltaTime);
    }

    MouseInputSystem::update(*this, event);
    audioEventQueue.process();

    synchronizeEntities();
    cleanUp();
}

void World::render(const Camera& camera) {
    RenderSystem::render(*this, camera);
    UIRenderSystem::render(entities);
}

Entity& World::createEntity() {

    // We use emplace instead of push so we don't create a copy
    // Creates a smart pointer
    entities.emplace_back(std::make_unique<Entity>());
    return *entities.back();
}

Entity& World::createDeferredEntity() {
    deferredEntities.emplace_back(std::make_unique<Entity>());
    return *deferredEntities.back();
}

void World::cleanUp() {

    // Use lambda predicate to remove all inactive entities
    std::erase_if(entities,
                  [](const std::unique_ptr<Entity>& entity) {
                      return !entity->isActive();
                  });
}

void World::synchronizeEntities() {
    if (!deferredEntities.empty()) {

        // Push back all deferred entities to the entities vector
        std::ranges::move(deferredEntities
                          ,
                          std::back_inserter(entities)
        );

        // Clearing the creation buffer
        deferredEntities.clear();
    }
}
