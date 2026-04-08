//
// Created by Iris Chow on 2026-04-08.
//

#ifndef INC_8051PROJECT_INVENTORYUISYSTEM_H
#define INC_8051PROJECT_INVENTORYUISYSTEM_H

#include <memory>
#include <vector>
#include <SDL3/SDL_render.h>

class Entity;

class InventoryUISystem {
public:
    static void render(const std::vector<std::unique_ptr<Entity>>& entities, SDL_Renderer* renderer);
};

#endif //INC_8051PROJECT_INVENTORYUISYSTEM_H