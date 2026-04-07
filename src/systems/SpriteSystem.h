//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_SPRITESYSTEM_H
#define INC_8051PROJECT_SPRITESYSTEM_H

#include <memory>
#include <vector>

class World;
class Entity;
struct Camera;

class SpriteSystem {
public:
    static void draw(const std::vector<std::unique_ptr<Entity>>& entities, const Camera& camera);
};

#endif //INC_8051PROJECT_SPRITESYSTEM_H