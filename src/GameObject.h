//
// Created by Iris Chow on 2026-01-14.
//

#ifndef INC_8051TUTORIAL_GAMEOBJECT_H
#define INC_8051TUTORIAL_GAMEOBJECT_H

#include "Game.h"

class GameObject {
public:
    GameObject(const char* path, int x, int y);
    ~GameObject();

    void update(float deltaTime);
    void draw() const;
private:
    int xPos{}, yPos{};

    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect{}, dstRect{};
};

#endif //INC_8051TUTORIAL_GAMEOBJECT_H