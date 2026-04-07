//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051PROJECT_MOVEMENTSYSTEM_H
#define INC_8051PROJECT_MOVEMENTSYSTEM_H

#include <memory>
#include <vector>

class Entity;

class MovementSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>> &entities, float deltaTime);
};

#endif //INC_8051PROJECT_MOVEMENTSYSTEM_H