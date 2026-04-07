//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051PROJECT_RENDERSYSTEM_H
#define INC_8051PROJECT_RENDERSYSTEM_H

#include <SDL3/SDL_render.h>

class World;
struct Camera;

class RenderSystem {
public:
    static void render(World &world, SDL_Renderer *renderer, const Camera &camera);
};

#endif //INC_8051PROJECT_RENDERSYSTEM_H