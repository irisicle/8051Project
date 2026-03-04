//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051TUTORIAL_WORLD_H
#define INC_8051TUTORIAL_WORLD_H
#include <memory>
#include <vector>

#include "../Map.h"
#include "event/EventManager.h"
#include "system/AnimationSystem.h"
#include "system/CameraSystem.h"
#include "system/CollisionSystem.h"
#include "system/DestructionSystem.h"
#include "system/EventResponseSystem.h"
#include "system/KeyboardInputSystem.h"
#include "system/MovementSystem.h"
#include "system/RenderSystem.h"
#include "system/SpawnTimerSystem.h"

class World {
    Map map;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> deferredEntities;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem keyboardInputSystem;
    CollisionSystem collisionSystem;
    AnimationSystem animationSystem;
    CameraSystem cameraSystem;
    EventManager eventManager;
    SpawnTimerSystem spawnTimerSystem;
    DestructionSystem destructionSystem;
    EventResponseSystem eventResponseSystem{*this};

public:
    World() = default;
    void update(const float deltaTime, const SDL_Event& event) {
        KeyboardInputSystem::update(entities, event);
        MovementSystem::update(entities, deltaTime);
        CollisionSystem::update(*this);
        AnimationSystem::update(entities, deltaTime);
        CameraSystem::update(entities);
        SpawnTimerSystem::update(entities, deltaTime);
        DestructionSystem::update(entities);
        synchronizeEntities();
        cleanUp();
    }

    void render() const {
        for (const auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                map.draw(entity->getComponent<Camera>());
                break;
            }
        }
        RenderSystem::render(entities);
    }

    Entity& createEntity() {
        // We use emplace instead of push so we don't create a copy
        // Creates a smart pointer
        entities.emplace_back(std::make_unique<Entity>());
        return *entities.back();
    }

    Entity& createDeferredEntity() {
        deferredEntities.emplace_back(std::make_unique<Entity>());
        return *deferredEntities.back();
    }

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }

    void cleanUp() {
        // Use lambda predicate to remove all inactive entities
        std::erase_if(entities,
                      [](const std::unique_ptr<Entity>& entity) {
                          return !entity->isActive();
                      });
    }

    void synchronizeEntities() {
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

    EventManager& getEventManager() {
        return eventManager;
    }

    Map& getMap() {
        return map;
    }
};

#endif //INC_8051TUTORIAL_WORLD_H