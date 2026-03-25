//
// Created by Iris Chow on 2026-02-25.
//

#ifndef INC_8051PROJECT_SPAWNTIMERSYSTEM_H
#define INC_8051PROJECT_SPAWNTIMERSYSTEM_H
#include "../Component.h"
#include "../Entity.h"

class SpawnTimerSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities, const float deltaTime) {
        for (auto& entity : entities) {
            if (entity->hasComponent<TimedSpawner>()) {
                auto& spawner = entity->getComponent<TimedSpawner>();
                spawner.timer -= deltaTime;

                if (spawner.timer <= 0) {
                    spawner.timer = spawner.spawnInterval; // (eg. 2 secs)
                    spawner.spawnCallback(); // Create entity inside here
                }
            }
        }
    }
};

#endif //INC_8051PROJECT_SPAWNTIMERSYSTEM_H