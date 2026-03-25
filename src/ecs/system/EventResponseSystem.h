//
// Created by Iris Chow on 2026-03-04.
//

#ifndef INC_8051PROJECT_EVENTRESPONSESYSTEM_H
#define INC_8051PROJECT_EVENTRESPONSESYSTEM_H
#include <functional>

#include "../event/BaseEvent.h"

class Entity;
class World;

class EventResponseSystem {
public:
  explicit EventResponseSystem(World& world);

private:
  // Collisions
  static void onCollision(const CollisionEvent& event, const char* otherTag, World& world);
  static bool getCollisionEntities(const CollisionEvent& event, const char* otherTag, Entity*& player, Entity*& other);

  // Player action
  static void onPlayerAction(const PlayerActionEvent& event, const std::function<void(Entity* player, PlayerAction action)>& callback);

  static void onMouseInteraction(const MouseInteractionEvent& event);
};

#endif //INC_8051PROJECT_EVENTRESPONSESYSTEM_H