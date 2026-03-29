//
// Created by Iris Chow on 2026-03-04.
//

#include "EventResponseSystem.h"
#include "../World.h"
#include "../../game/Game.h"

EventResponseSystem::EventResponseSystem(World& world) {

    // Subscriptions
    world.getEventManager().subscribe([&world](const BaseEvent& event) {
        if (event.type != EventType::Collision) return;
        const auto& collision = dynamic_cast<const CollisionEvent&>(event); // Cast base type to collision type

        onCollision(collision, "item", world);
        onCollision(collision, "water", world);
        onCollision(collision, "projectile", world);
    });

    world.getEventManager().subscribe([this, &world](const BaseEvent& event) {
        if (event.type != EventType::PlayerAction) return;
        const auto& playerAction = dynamic_cast<const PlayerActionEvent&>(event);
    });

    world.getEventManager().subscribe([this, &world](const BaseEvent& event) {
        if (event.type != EventType::MouseInteraction) return;
        const auto& mouseInteractionEvent = dynamic_cast<const MouseInteractionEvent&>(event);
        onMouseInteraction(mouseInteractionEvent);
    });
}

void EventResponseSystem::onPlayerAction(const PlayerActionEvent &event, const std::function<void(Entity* player, PlayerAction action)>& callback) {


}

void EventResponseSystem::onMouseInteraction(const MouseInteractionEvent& event) {
    if (!event.entity->hasComponent<Clickable>()) return;

    const auto& clickable = event.entity->getComponent<Clickable>();

    switch (event.state) {
        case MouseInteractionState::Pressed:
            clickable.onPressed();
            break;
        case MouseInteractionState::Released:
            clickable.onReleased();
            break;
        case MouseInteractionState::Cancel:
            clickable.onCancel();
            break;
        default:
            break;
    }
}

void EventResponseSystem::onCollision(const CollisionEvent& event, const char* otherTag, World& world) {
    Entity* player = nullptr;
    Entity* other = nullptr;

    if (!getCollisionEntities(event, otherTag, player, other)) return;

    if (std::string(otherTag) == "item") {
        if (event.state != CollisionState::Enter) return;

        other->destroy();

        for (const auto& entity : world.getEntities()) {
            if (!entity->hasComponent<SceneState>()) continue;

            // Scene state
            auto& sceneState = entity->getComponent<SceneState>();

            sceneState.coinsCollected++;
            if (sceneState.coinsCollected > 1) {
                Game::onSceneChangeRequest("level2");
            }
        }
    }

    else if (std::string(otherTag) == "water") {
        if (event.state != CollisionState::Stay) return;

        // Stop the player
        auto& transform = player->getComponent<Transform>();
        transform.position = transform.oldPosition;
    }

    else if (std::string(otherTag) == "projectile") {
        if (event.state != CollisionState::Enter) return;

        // This logic is simple and direct
        // Ideally we would only operate on data in an update function (hinting at transient entities)
        auto& health = player->getComponent<Health>();
        health.currentHealth--;

        Game::gameState.playerHealth = health.currentHealth;

        std::cout << health.currentHealth << std::endl;

        if (health.currentHealth <= 0) {
            player->destroy();

            // Change scenes defer
            Game::onSceneChangeRequest("gameover");
        }
    }
}

bool EventResponseSystem::getCollisionEntities(const CollisionEvent& event, const char* otherTag, Entity*& player, Entity*& other) {
    if (event.entityA == nullptr || event.entityB == nullptr) return false;

    if (!(event.entityA->hasComponent<Collider>() && event.entityB->hasComponent<Collider>())) return false;

    const auto& colliderA = event.entityA->getComponent<Collider>();
    const auto& colliderB = event.entityB->getComponent<Collider>();

    if (colliderA.tag == "player" && colliderB.tag == otherTag) {
        player = event.entityA;
        other = event.entityB;
    }

    else if (colliderA.tag == otherTag && colliderB.tag == "player") {
        player = event.entityB;
        other = event.entityA;
    }

    return player && other;
}
