//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_ENTITYFACTORY_H
#define INC_8051PROJECT_ENTITYFACTORY_H

#include "../ecs/core/Entity.h"
#include "../utils/CropEnums.h"
#include "../utils/Vector2D.h"

class World;

class EntityFactory {
public:
    static Entity& createPlayer(World& world);
    static Entity& createCow(World& world, const Vector2D& position);
    static Entity& createCrop(World &world, CropType type, int x, int y);
};

#endif //INC_8051PROJECT_ENTITYFACTORY_H