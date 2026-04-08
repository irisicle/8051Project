//
// Created by Iris Chow on 2026-02-22.
//

#ifndef INC_8051PROJECT_ASSETMANAGER_H
#define INC_8051PROJECT_ASSETMANAGER_H
#include <string>
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>
#include "../ecs/component/Animation.h"

class AssetManager {
    static std::unordered_map<std::string, TTF_Font*> fonts;
    static std::unordered_map<std::string, Animation> animations;

    static Animation loadAnimationFromXML(const std::string& path);

public:
    static void loadFont(const char* path, const std::string& name, float fontSize);
    static TTF_Font* getFont(const std::string& name);
    static void loadAnimation(const std::string& clipName, const char* path);
    static const Animation& getAnimation(const std::string& clipName);

};

#endif //INC_8051PROJECT_ASSETMANAGER_H