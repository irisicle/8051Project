//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051PROJECT_WORLD_H
#define INC_8051PROJECT_WORLD_H

#include <memory>
#include <vector>

#include "Camera.h"
#include "../../map/MapData.h"
#include "../../systems/MainMenuSystem.h"
#include "../../systems/MouseInputSystem.h"
#include "../../systems/AnimationSystem.h"
#include "../../systems/UIRenderSystem.h"
#include "../../systems/RenderSystem.h"
#include "../../systems/CollisionSystem.h"
#include "../../systems/CameraSystem.h"
#include "../../systems/KeyboardInputSystem.h"
#include "../../systems/MovementSystem.h"
#include "../../systems/CropGrowthSystem.h"
#include "../../systems/EventBindings.h"
#include "../event/EventManager.h"
#include "../../scene/SceneType.h"
#include "../../systems/PlayerControlSystem.h"
#include "../event/AudioEventQueue.h"
#include "../../systems/SelectionHighlightSystem.h"

class World {
    MapData map{};
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> deferredEntities;
    EventManager eventManager;
    SelectionHighlightSystem selectionHighlightSystem;
    AudioEventQueue audioEventQueue;

public:

    World() = default;

    void setMap(MapData newMap) {
        map = std::move(newMap);
    }

    void update(const float deltaTime, const SDL_Event& event, const SceneType sceneType) {
        if (sceneType == SceneType::MAIN_MENU) {
            MainMenuSystem::update(event);
        }

        else {
            EventBindings::update(*this);
            KeyboardInputSystem::update(entities, event);
            PlayerControlSystem::update(entities);
            MovementSystem::update(entities, deltaTime);
            CollisionSystem::update(*this);
            AnimationSystem::update(entities, deltaTime);
            CameraSystem::update(entities);
            CropGrowthSystem::update(entities, deltaTime);
        }

        MouseInputSystem::update(*this, event);
        audioEventQueue.process();

        synchronizeEntities();
        cleanUp();
    }

    void render(SDL_Renderer* renderer) {
        for (const auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                const auto& camera = entity->getComponent<Camera>();
                RenderSystem::render(*this, renderer, camera);
                selectionHighlightSystem.update(entities, camera);
                break;
            }
        }

        UIRenderSystem::render(entities);
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

    MapData& getMap() {
        return map;
    }

    [[nodiscard]] const MapData& getMap() const {
        return map;
    }

    SelectionHighlightSystem& getSelectionHighlightSystem() {
        return selectionHighlightSystem;
    }
};

#endif //INC_8051PROJECT_WORLD_H