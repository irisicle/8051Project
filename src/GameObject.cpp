//
// Created by Iris Chow on 2026-01-14.
//
#include "GameObject.h"

#include "manager/TextureManager.h"

GameObject::GameObject(const char *path, const int x, const int y) :
xPos(x), yPos(y), texture(TextureManager::load(path)) {}

GameObject::~GameObject() {
    if (texture) SDL_DestroyTexture(texture);
}

void GameObject::update(const float deltaTime) {
    constexpr int speed = 250; // Pixels per frame
    // Move GameObject one pixel on the x and y each frame
    xPos += speed * deltaTime;
    yPos += speed * deltaTime;

    // Where do we want to crop the texture from?
    srcRect.x = srcRect.y = 0;

    // How much to crop?
    srcRect.w = srcRect.h = 32;

    // Where to draw it?
    dstRect.x = static_cast<float>(xPos);
    dstRect.y = static_cast<float>(yPos);

    // What sizes to render?
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
}

void GameObject::draw() const {
    TextureManager::draw(texture, srcRect, dstRect);
}
