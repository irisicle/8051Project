//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_UIFACTORY_H
#define INC_8051PROJECT_UIFACTORY_H

#include "../ecs/core/Entity.h"

class World;

class UIFactory {
public:
    static Entity& createMainMenu(World &world, int width, int height);
    static Entity& createSettingsOverlay(World& world, int width, int height);
    static Entity& createCogButton(World& world, int width, int height, Entity& overlay);

    static Entity& createInventory(World& world, int width, int height);
    static Entity& createSelectionHighlight(World& world);

    static void createSettingsUIComponents(World& world, Entity& overlay);
    static void toggleSettingsOverlayVisibility(Entity& overlay);
};

#endif //INC_8051PROJECT_UIFACTORY_H