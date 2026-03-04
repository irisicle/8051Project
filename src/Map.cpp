//
// Created by Iris Chow on 2026-01-14.
//
#include "Map.h"
#include "manager/TextureManager.h"
#include "vendor/tinyxml2.h"

#include <iostream>
#include <sstream>

void Map::load(const char* path, SDL_Texture* ts) {

    tileset = ts;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    // Parse width and height of map
    auto* mapNode = doc.FirstChildElement("map");
    width = mapNode->IntAttribute("width");
    height = mapNode->IntAttribute("height");

    // Parse terrain data
    auto* layer = mapNode->FirstChildElement("layer");
    auto* data = layer->FirstChildElement("data");
    std::string csv = data->GetText();
    std::stringstream ss(csv);
    tileData = std::vector(height, std::vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::string val;
            // Read characters from a ss into val until it hits a comma, or is at the end of the stream
            if (!std::getline(ss, val, ',')) break;
            tileData[i][j] = std::stoi(val); // stoi is a string-to-integer converter
        }
    }

    // Parse collider data
    auto* objectGroup = layer->NextSiblingElement("objectgroup");
    while (objectGroup != nullptr) {
        const char* name = objectGroup->Attribute("name");

        // Create a for-loop with initialization, condition and an increment
        auto* object = objectGroup->FirstChildElement("object");
        while (object != nullptr) {
            if (name != nullptr) {
                if (std::string(name) == "Item Layer") {
                    SpawnPoint spawnPoint;
                    spawnPoint.position.x = static_cast<float>(object->IntAttribute("x"));
                    spawnPoint.position.y = static_cast<float>(object->IntAttribute("y"));

                    spawnPoints.push_back(spawnPoint);
                }
                else if (std::string(name) == "Collision Layer") {
                    Collider collider;
                    collider.rect.x = static_cast<float>(object->IntAttribute("x"));
                    collider.rect.y = static_cast<float>(object->IntAttribute("y"));
                    collider.rect.w = static_cast<float>(object->IntAttribute("width"));
                    collider.rect.h = static_cast<float>(object->IntAttribute("height"));

                    colliders.push_back(collider);
                }
            }
            object = object->NextSiblingElement("object");
        }
        objectGroup = objectGroup->NextSiblingElement("objectgroup");
    }
}

void Map::draw(const Camera& cam) const {

    SDL_FRect src{}, dest{};

    dest.w = dest.h = 32;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            const int type = tileData[row][col];

            const float worldX = static_cast<float>(col) * dest.w;
            const float worldY = static_cast<float>(row) * dest.h;

            // Move tiles or map relative to the camera
            // Convert from world space to screen space
            dest.x = std::round(worldX - cam.view.x);
            dest.y = std::round(worldY - cam.view.y);

            switch (type) {
                case 1:
                    // dirt
                    src.x = 0;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 2:
                    // grass
                    src.x = 32;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 4:
                    // water
                    src.x = 32;
                    src.y = 32;
                    src.w = 32;
                    src.h = 32;
                    break;
                default:
                    break;
            }

            TextureManager::draw(tileset, src, dest);
        }
    }
}
