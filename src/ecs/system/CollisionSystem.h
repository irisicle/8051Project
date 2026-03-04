//
// Created by Iris Chow on 2026-02-04.
//

#ifndef INC_8051TUTORIAL_COLLISIONSYSTEM_H
#define INC_8051TUTORIAL_COLLISIONSYSTEM_H
#include <set>

#include "../Entity.h"
#include <vector>

using CollisionKey = std::pair<Entity*, Entity*>;

// Forward declaration
class World;

class CollisionSystem {
public:
    static void update(World& world);
    std::set<CollisionKey> activeCollisions;
private:
    static std::vector<Entity*> queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities);
    static CollisionKey makeKey(Entity* entityA, Entity* entityB) {
        return std::minmax(entityA, entityB); // Automatically orders the pair so smaller number (memory address) is ordered first
    }
};

#endif //INC_8051TUTORIAL_COLLISIONSYSTEM_H