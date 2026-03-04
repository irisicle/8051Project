//
// Created by Iris Chow on 2026-02-22.
//

#ifndef INC_8051TUTORIAL_ASSETMANAGER_H
#define INC_8051TUTORIAL_ASSETMANAGER_H
#include <string>
#include <unordered_map>

#include "../ecs/Component.h"

class AssetManager {

    static std::unordered_map<std::string, Animation> animations;
    static Animation loadAnimationFromXML(const std::string& path);
public:
    static void loadAnimation(const std::string& clipName, const char* path);
    static const Animation& getAnimation(const std::string& clipName);

};

#endif //INC_8051TUTORIAL_ASSETMANAGER_H