//
// Created by Iris Chow on 2026-02-22.
//

#include "AssetManager.h"
#include "../vendor/tinyxml2.h"

std::unordered_map<std::string, TTF_Font*> AssetManager::fonts;
std::unordered_map<std::string, Animation> AssetManager::animations;

void AssetManager::loadFont(const char* path, const std::string& name, const float fontSize) {
    fonts.emplace(name, TTF_OpenFont(path, fontSize));
}

TTF_Font* AssetManager::getFont(const std::string& name) {
    return fonts[name];
}

void AssetManager::loadAnimation(const std::string& clipName, const char* path) {
    const Animation animation = loadAnimationFromXML(path);
    animations[clipName] = animation;
}

const Animation& AssetManager::getAnimation(const std::string& clipName) {
    return animations[clipName];
}

Animation AssetManager::loadAnimationFromXML(const std::string& path) {
    Animation animation;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());

    auto* root = doc.FirstChildElement("animations");
    for (auto* clipElement = root->FirstChildElement(); clipElement; clipElement = clipElement->NextSiblingElement()) {
        std::string clipName = clipElement->Name();
        AnimationClip clip;

        for (auto* frameElement = clipElement->FirstChildElement(); frameElement; frameElement = frameElement->NextSiblingElement()) {
            SDL_FRect rect;
            frameElement->QueryFloatAttribute("x", &rect.x);
            frameElement->QueryFloatAttribute("y", &rect.y);
            frameElement->QueryFloatAttribute("w", &rect.w);
            frameElement->QueryFloatAttribute("h", &rect.h);
            clip.frames.push_back(rect);
        }
        animation.clips[clipName] = clip;
    }

    if (!animation.clips.empty()) {
        animation.currentClip = animation.clips.begin()->first;
    }

    return animation;
}
