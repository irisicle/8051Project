//
// Created by Iris Chow on 2026-04-05.
//

#include "AnimationSystem.h"
#include "../ecs/core/Entity.h"
#include "../ecs/component/Animation.h"
#include "../ecs/component/Physics.h"
#include "../ecs/component/Interaction.h"

void AnimationSystem::update(const std::vector<std::unique_ptr<Entity>> &entities, const float deltaTime) {
    for (const auto &entity: entities) {
        if (!entity->hasComponent<Animation>() || !entity->hasComponent<Facing>() || !entity->hasComponent<Velocity>()) {
            continue;
        }

        auto &animation = entity->getComponent<Animation>();
        const auto &velocity = entity->getComponent<Velocity>();
        const auto &facing = entity->getComponent<Facing>();

        // State system
        std::string newClip;

        const bool isMoving = (velocity.direction.x != 0.0f || velocity.direction.y != 0.0f);

        switch (facing.direction) {
            case Direction::UP:
                newClip = isMoving ? AnimationClips::WALK_UP : AnimationClips::IDLE_UP;
                break;
            case Direction::DOWN:
                newClip = isMoving ? AnimationClips::WALK_DOWN : AnimationClips::IDLE_DOWN;
                break;
            case Direction::LEFT:
                newClip = isMoving ? AnimationClips::WALK_LEFT : AnimationClips::IDLE_LEFT;
                break;
            case Direction::RIGHT:
                newClip = isMoving ? AnimationClips::WALK_RIGHT : AnimationClips::IDLE_RIGHT;
                break;
            default:
                break;
        }

        // Check if the animation has switched
        // If the chosen clip is different from the current one, switch to new clip, reset time and frame index
        if (newClip != animation.currentClip) {
            animation.currentClip = newClip; // Switch to new clip
            animation.frameTimer = 0.0f; // Reset time to 0
            animation.currentFrame = 0; // Reset frame index to 0
        }

        // Playback
        // Avoids inserting empty clips
        const auto clipIt = animation.clips.find(animation.currentClip);
        if (clipIt == animation.clips.end()) {
            continue;
        }

        const auto &clip = clipIt->second; // Get reference of clip
        const std::size_t totalFrames = clip.frames.size();

        if (totalFrames == 0) {
            continue;
        }

        // Advance timer
        animation.frameTimer += deltaTime;

        // Handles lag better
        while (animation.frameTimer >= animation.speed) {
            animation.frameTimer -= animation.speed;

            if (animation.looping) {
                animation.currentFrame = (animation.currentFrame + 1) % totalFrames;
            } else if (animation.currentFrame + 1 < totalFrames) {
                ++animation.currentFrame;
            }
        }

        // Safety clamp in case currentFrame is out of bounds
        if (animation.currentFrame >= totalFrames) {
            animation.currentFrame = totalFrames - 1;
        }
    }
}