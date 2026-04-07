//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_SELECTIONHIGHLIGHTSYSTEM_H
#define INC_8051PROJECT_SELECTIONHIGHLIGHTSYSTEM_H

#include <vector>
#include <SDL3/SDL_render.h>
#include "../ecs/core/Entity.h"

class World;
struct Camera;

class SelectionHighlightSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, const Camera& camera);
    void draw(SDL_Renderer* renderer) const;

private:
    bool visible{false};
    SDL_FRect rect{};
};

#endif //INC_8051PROJECT_SELECTIONHIGHLIGHTSYSTEM_H