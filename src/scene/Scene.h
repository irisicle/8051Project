//
// Created by Iris Chow on 2026-02-25.
//

#ifndef INC_8051PROJECT_SCENE_H
#define INC_8051PROJECT_SCENE_H

#include <string>
#include <SDL3/SDL_events.h>
#include "../ecs/core/Camera.h"
#include "../ecs/core/World.h"
#include "SceneType.h"
#include "../map/MapLoader.h"
#include "../systems/SelectionHighlightSystem.h"

class Scene {
public:
    Scene(SceneType sceneType, const char* sceneName, const char* mapPath, int windowWidth, int windowHeight);

    void initialize();
    void update(float deltaTime, const SDL_Event &event);
    void render(SDL_Renderer *renderer);

    [[nodiscard]] const std::string& getSceneName() const {
        return name;
    }

    Camera& getCamera() {
        return camera;
    }

    // const overload
    // Read only access
    [[nodiscard]] const Camera& getCamera() const {
        return camera;
    }

private:
    World world{};
    Camera camera{};
    MapLoader loader{};
    SelectionHighlightSystem selectionHighlightSystem{};

    std::string name{};
    SceneType type{};

    void initMainMenu(int windowWidth, int windowHeight);
    void initGameplay(const char* mapPath, int windowWidth, int windowHeight);
};

#endif //INC_8051PROJECT_SCENE_H