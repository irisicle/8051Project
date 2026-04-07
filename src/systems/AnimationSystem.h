//
// Created by Iris Chow on 2026-02-22.
//

#ifndef INC_8051PROJECT_ANIMATIONSYSTEM_H
#define INC_8051PROJECT_ANIMATIONSYSTEM_H
#include <vector>

class Entity;

// State system: Deciding which clip to use
// Check if the animation has been switched
// Playback system: Advances the animation
class AnimationSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>> &entities, float deltaTime);
};


#endif //INC_8051PROJECT_ANIMATIONSYSTEM_H
