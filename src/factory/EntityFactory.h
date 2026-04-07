//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_ENTITYFACTORY_H
#define INC_8051PROJECT_ENTITYFACTORY_H

#include "../ecs/core/Entity.h"
#include "../utils/Vector2D.h"

class World;

class EntityFactory {
public:
    static Entity& createCamera(World& world, int width, int height);
    static Entity& createPlayer(World& world);
    static Entity& createCow(World& world, const Vector2D& position);
    static Entity& createCrop(World& world, const Vector2D& position);
};

#endif //INC_8051PROJECT_ENTITYFACTORY_H