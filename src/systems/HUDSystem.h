//
// Created by Iris Chow on 2026-04-07.
//

#ifndef INC_8051PROJECT_HUDSYSTEM_H
#define INC_8051PROJECT_HUDSYSTEM_H

#include <vector>

class Entity;

class HUDSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities);
};

#endif //INC_8051PROJECT_HUDSYSTEM_H