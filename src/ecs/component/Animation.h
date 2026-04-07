//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_ANIMATION_H
#define INC_8051PROJECT_ANIMATION_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../core/Component.h"
#include <SDL3/SDL.h>

namespace AnimationClips {

    inline constexpr auto IDLE_UP = "idle_up";
    inline constexpr auto IDLE_DOWN = "idle_down";
    inline constexpr auto IDLE_LEFT = "idle_left";
    inline constexpr auto IDLE_RIGHT = "idle_right";
    inline constexpr auto WALK_UP = "walk_up";
    inline constexpr auto WALK_DOWN = "walk_down";
    inline constexpr auto WALK_LEFT = "walk_left";
    inline constexpr auto WALK_RIGHT = "walk_right";

}

struct AnimationClip {
    std::vector<SDL_FRect> frames{};
};

struct Animation : Component {
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float frameTimer{0.0f}; // Time accumulated for the current frame
    size_t currentFrame{0}; // Index of the current frame in the clip
    float speed{0.1f}; // Time per frame
    bool looping{true};
};

#endif //INC_8051PROJECT_ANIMATION_H