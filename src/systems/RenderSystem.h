//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051PROJECT_RENDERSYSTEM_H
#define INC_8051PROJECT_RENDERSYSTEM_H

class World;
struct Camera;

class RenderSystem {
public:
    static void render(World &world, const Camera &camera);
};

#endif //INC_8051PROJECT_RENDERSYSTEM_H