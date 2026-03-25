//
// Created by Iris Chow on 2026-02-25.
//

#ifndef INC_8051PROJECT_SCENEMANAGER_H
#define INC_8051PROJECT_SCENEMANAGER_H
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>

#include "../scene/Scene.h"

struct SceneParams {
    SceneType sceneType;
    const char* name;
    const char* mapPath;
    int windowWidth;
    int windowHeight;
};

class SceneManager {
    std::unordered_map<std::string, SceneParams> sceneParams;
    std::string pendingScene;

    void changeScene(const std::string& name) {
        if (const auto it = sceneParams.find(name); it != sceneParams.end()) {
            const auto& params = it->second;
            // Create scene object
            // Build scene
            currentScene = std::make_unique<Scene>(
                params.sceneType,
                params.name,
                params.mapPath,
                params.windowWidth,
                params.windowHeight
                );
        } else {
            std::cerr << "Scene not found: " << name << std::endl;
        }
    }

public:
    std::unique_ptr<Scene> currentScene;

    void loadScene(const SceneType sceneType, const char* sceneName, const char* mapPath, const int windowWidth, const int windowHeight) {
        sceneParams[sceneName] = {sceneType, sceneName, mapPath, windowWidth, windowHeight};
    }

    void changeSceneDeferred(const std::string& name) {
        pendingScene = name;
    }

    void update(const float deltaTime, const SDL_Event& event) {
        if (currentScene) {
            currentScene->update(deltaTime, event); // All world updates
        }

        if (!pendingScene.empty()) {
            changeScene(pendingScene);
            pendingScene.clear();
        }
    }

    void render() const {
        if (currentScene) currentScene->render();
    }
};

#endif //INC_8051PROJECT_SCENEMANAGER_H