//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_TAG_H
#define INC_8051PROJECT_TAG_H

#include "../core/Component.h"

struct PlayerTag : Component {};
struct SelectionHighlightTag : Component {};
struct CropTag {};
struct SlotTag { int index{}; };
struct ItemDropTag {};
struct InteractableTag{};
struct ProjectileTag{};

// Game state, might have multiple scenes
struct SceneState {};

#endif //INC_8051PROJECT_TAG_H