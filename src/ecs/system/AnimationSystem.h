//
// Created by Iris Chow on 2026-02-22.
//

#ifndef INC_8051TUTORIAL_ANIMATIONSYSTEM_H
#define INC_8051TUTORIAL_ANIMATIONSYSTEM_H
#include "AnimationClip.h"
#include "../Component.h"
#include "../Entity.h"

// State system: Deciding which clip to use
// Check if the animation has been switched
// Playback system: Advances the animation
class AnimationSystem {

public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities, const float deltaTime) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Animation>() && entity->hasComponent<Velocity>()) {
                auto& animation = entity->getComponent<Animation>();
                auto& velocity = entity->getComponent<Velocity>();

                // State system
                std::string newClip;

                if (velocity.direction.x > 0.0f) {
                    newClip = "walk_right";
                }
                else if (velocity.direction.x < 0.0f) {
                    newClip = "walk_left";
                }
                else if (velocity.direction.y > 0.0f) {
                    newClip = "walk_up";
                }
                else if (velocity.direction.y < 0.0f) {
                    newClip = "walk_down";
                }
                else {
                    newClip = "idle";
                }

                // Check if the animation has switched
                // If the chosen clip is different from the current one, switch to new clip, reset time and frame index
                if (newClip != animation.currentClip) {
                    animation.currentClip = newClip; // Switch to new clip
                    animation.time = 0.0f; // Reset time to 0
                    animation.currentFrame = 0; // Reset frame index to 0
                }

                // Playback system: Advance the animation
                const float animationFrameSpeed = animation.speed;
                auto clip = animation.clips[animation.currentClip]; // Retrieve the frame data from the current clip

                // Advance time
                animation.time += deltaTime; // Every 'game loop frame' we are going to add the accumulated time

                // Once enough time has passed
                if (animation.time >= animationFrameSpeed) {
                    animation.time -= animationFrameSpeed; // Subtract animationFrameSpeed (e.g. 0.1f) so the extra time isn't lost
                    const std::size_t totalAnimationFrames = clip.frameIndices.size();

                    // Advance to the next animation frame (currentAnimationFrame + 1)
                    // Wrap around % so it loops when reaching the end of the clip
                    animation.currentFrame = (animation.currentFrame + 1) % totalAnimationFrames;
                }
            }
        }
    }
};

#endif //INC_8051TUTORIAL_ANIMATIONSYSTEM_H