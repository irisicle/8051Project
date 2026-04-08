//
// Created by Iris Chow on 2026-04-07.
//

#include "HUDSystem.h"
#include "../ecs/component/Tag.h"
#include "../ecs/component/Physics.h"
#include "../ecs/component/Render.h"

void HUDSystem::update(const std::vector<std::unique_ptr<Entity>> &entities) {
    // Entity *player = nullptr;
    //
    // // Find player
    // for (auto &entity: entities) {
    //     if (entity->hasComponent<PlayerTag>()) {
    //         player = entity.get();
    //         break;
    //     }
    // }
    //
    // if (!player) return;
    //
    // auto &playerTransform = player->getComponent<Transform>();
    //
    // for (auto &entity: entities) {
    //     if (entity->hasComponent<Label>()) {
    //         auto &label = entity->getComponent<Label>();
    //
    //         // Update player position label
    //         if (label.type == LabelType::PlayerPosition) {
    //             std::stringstream ss;
    //             ss << "Player position: " << playerTransform.position;
    //             label.text = ss.str();
    //             label.dirty = true;
    //         }
    //     }
    // }
}
