//
// Created by Iris Chow on 2026-02-25.
//

#ifndef INC_8051TUTORIAL_SCENE_H
#define INC_8051TUTORIAL_SCENE_H
#include <string>

#include <SDL3/SDL_events.h>
#include "../ecs/World.h"
#include "SceneType.h"

class Scene {
public:
    Scene(SceneType sceneType, const char* sceneName, const char* mapPath, int windowWidth, int windowHeight);

    void update(const float deltaTime, const SDL_Event& event) {
        world.update(deltaTime, event, type);
    }

    void render() const {
        world.render();
    }

    World world;

    [[nodiscard]] const std::string& getSceneName() const { return name; }

private:
    std::string name;
    SceneType type;
    void createProjectile(Vector2D pos, Vector2D dir, int speed);
};

#endif //INC_8051TUTORIAL_SCENE_H