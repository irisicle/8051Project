//
// Created by Iris Chow on 2026-04-06.
//

#include "EventBindings.h"
#include "CollisionResponseSystem.h"
#include "../ecs/event/BaseEvent.h"
#include "PlayerActionResponseSystem.h"
#include "MouseInteractionResponseSystem.h"
#include "../ecs/event/EventEnums.h"
#include "../ecs/core/World.h"

void EventBindings::update(World& world) {

    // Subscriptions
    world.getEventManager().subscribe([&world](const BaseEvent& event) {
        if (event.type != EventType::COLLISION) return;
        const auto& collision = dynamic_cast<const CollisionEvent&>(event); // Cast base type to collision type

        CollisionResponseSystem::handle(collision, "item", world);
        CollisionResponseSystem::handle(collision, "wall", world);
        CollisionResponseSystem::handle(collision, "projectile", world);
    });

    world.getEventManager().subscribe([&world](const BaseEvent& event) {
        if (event.type != EventType::PLAYER_ACTION) return;
        const auto& playerAction = dynamic_cast<const PlayerActionEvent&>(event);
        PlayerActionResponseSystem::handle(playerAction, world);
    });

    world.getEventManager().subscribe([&world](const BaseEvent& event) {
        if (event.type != EventType::MOUSE_INTERACTION) return;
        const auto& mouseInteractionEvent = dynamic_cast<const MouseInteractionEvent&>(event);
        MouseInteractionResponseSystem::handle(mouseInteractionEvent, world);
    });

}