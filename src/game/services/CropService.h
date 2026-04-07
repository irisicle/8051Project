//
// Created by Iris Chow on 2026-04-04.
//

#ifndef INC_8051PROJECT_CROPSERVICE_H
#define INC_8051PROJECT_CROPSERVICE_H

class Entity;
class World;

class CropService {
public:
    static bool water(World& world, int x, int y);
    static bool plant(World& world, Entity& player, int x, int y);
    static bool harvest(World& world, Entity& player, int x, int y);
};

#endif //INC_8051PROJECT_CROPSERVICE_H