//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051PROJECT_COMPONENT_H
#define INC_8051PROJECT_COMPONENT_H

#include <functional>
#include <SDL3/SDL_render.h>
#include <string>
#include <unordered_map>

#include "../utils/Vector2D.h"
#include "Entity.h"
#include "system/AnimationClip.h"

enum class RenderLayer {
    World,
    UI,
};

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
    Vector2D oldPosition{};
};

// Direction and speed
struct Velocity {
    Vector2D direction{};
    float speed{};
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dst{};
    RenderLayer renderLayer = RenderLayer::World;
    bool visible = true;
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
    bool enabled = true;
};

struct SpawnPoint {
    Vector2D position{};
};

struct Animation {
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float time{}; // Time accumulated for the current frame
    int currentFrame{}; // Index of the current frame in the clip
    float speed = 0.1f; // Time per frame
};

struct Camera {
    SDL_FRect view{};
    float worldWidth{};
    float worldHeight{};
};

struct TimedSpawner {
    float spawnInterval{};
    std::function<void()> spawnCallback{};
    float timer{};
};

// Game state, might have multiple scenes
struct SceneState {
    int coinsCollected = 0;
};

struct Health {
    int currentHealth{};
};

struct Clickable {
    std::function<void()> onPressed{};
    std::function<void()> onReleased{};
    std::function<void()> onCancel{};
    bool pressed = false;
};

struct Parent {
    Entity* parent = nullptr;
};

struct Children {
    std::vector<Entity*> children{};
};

struct PlayerTag{};
struct ProjectileTag{};

#endif //INC_8051PROJECT_COMPONENT_H