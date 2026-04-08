//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051PROJECT_WORLD_H
#define INC_8051PROJECT_WORLD_H

#include <memory>
#include <vector>

#include "../../map/MapData.h"
#include "../../systems/MainMenuSystem.h"
#include "../../systems/UIRenderSystem.h"
#include "../../systems/RenderSystem.h"
#include "../event/EventManager.h"
#include "../../scene/SceneType.h"
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

    void initialize();
    void setMap(MapData newMap);
    void update(float deltaTime, const SDL_Event &event, SceneType sceneType);
    void render(SDL_Renderer* renderer, const Camera& camera);

    Entity &createEntity();
    Entity &createDeferredEntity();

    void cleanUp();
    void synchronizeEntities();

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }

    EventManager& getEventManager() {
        return eventManager;
    }

    AudioEventQueue& getAudioEventQueue() {
        return audioEventQueue;
    }

    MapData& getMap() {
        return map;
    }

    // const overload
    [[nodiscard]] const MapData& getMap() const {
        return map;
    }

    SelectionHighlightSystem& getSelectionHighlightSystem() {
        return selectionHighlightSystem;
    }
};

#endif //INC_8051PROJECT_WORLD_H