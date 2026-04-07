//
// Created by Iris Chow on 2026-02-25.
//

#ifndef INC_8051PROJECT_SCENE_H
#define INC_8051PROJECT_SCENE_H

#include <string>
#include <SDL3/SDL_events.h>
#include "../ecs/core/World.h"
#include "SceneType.h"
#include "../map/MapLoader.h"

class Scene {
public:
    Scene(SceneType sceneType, const char* sceneName, const char* mapPath, int windowWidth, int windowHeight);

    void update(const float deltaTime, const SDL_Event& event) {
        world.update(deltaTime, event, type);
    }

    void render(SDL_Renderer* renderer) {
        world.render(renderer);
    }

    [[nodiscard]] const std::string& getSceneName() const { return name; }

private:
    World world;
    MapLoader loader;

    std::string name;
    SceneType type;

    void initMainMenu(int windowWidth, int windowHeight);
    void initGameplay(const char* mapPath, int windowWidth, int windowHeight);
};

#endif //INC_8051PROJECT_SCENE_H