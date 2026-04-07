//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_COLLISIONRESPONSESYSTEM_H
#define INC_8051PROJECT_COLLISIONRESPONSESYSTEM_H

#include "../ecs/event/BaseEvent.h"

class World;

class CollisionResponseSystem {
public:
    static void handle(const CollisionEvent& event, const char* otherTag, World& world);

private:
    static bool getCollisionEntities(const CollisionEvent& event, const char* otherTag, Entity*& player, Entity*& other);
};

#endif //INC_8051PROJECT_COLLISIONRESPONSESYSTEM_H