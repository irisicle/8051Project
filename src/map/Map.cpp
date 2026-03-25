//
// Created by Iris Chow on 2026-01-14.
//
#include "Map.h"
#include "../manager/TextureManager.h"
#include "../vendor/tinyxml2.h"

#include <iostream>
#include <sstream>

const Tileset* Map::getTilesetFromGid(const int gid) const {
    for (int i = static_cast<int>(tilesets.size()) - 1; i >= 0; i--) {
        if (gid >= tilesets[i].firstGid) {
            return &tilesets[i];
        }
    }
    return nullptr;
}

void Map::load(const char* path) {
    tilesets.clear();

    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    // Parse width and height of map
    auto* mapNode = doc.FirstChildElement("map");
    width = mapNode->IntAttribute("width");
    height = mapNode->IntAttribute("height");

    std::cout << "Loaded map: " << width << "x" << height << std::endl;

    for (auto* ts = mapNode->FirstChildElement("tileset"); ts != nullptr; ts = ts->NextSiblingElement("tileset")) {
        Tileset tileset{};
        tileset.firstGid = ts->IntAttribute("firstgid");
        const char* source = ts->Attribute("source");

        // Load TSX
        tinyxml2::XMLDocument tsx;
        if (tsx.LoadFile(source) != tinyxml2::XML_SUCCESS) {
            std::cerr << "Failed to load tsx from: " << tsx.ErrorStr() << std::endl;
            continue;
        }

        auto* tsxNode = tsx.FirstChildElement("tileset");

        if (!tsxNode) {
            std::cerr << "Failed to load tileset from: " << source << std::endl;
            continue;
        }

        tileset.tileWidth = tsxNode->IntAttribute("tilewidth");
        tileset.tileHeight = tsxNode->IntAttribute("tileheight");
        tileset.columns = tsxNode->IntAttribute("columns");
        tileset.tileCount = tsxNode->IntAttribute("tilecount");

        const char* imgPath = tsxNode->FirstChildElement("image")->Attribute("source");
        tileset.texture = TextureManager::load(imgPath);

        tilesets.push_back(tileset);
    }

    // Parse terrain data
    for (auto* layer = mapNode->FirstChildElement("layer"); layer != nullptr; layer = layer->NextSiblingElement("layer")) {
        auto* data = layer->FirstChildElement("data");

        std::string csv = data->GetText();
        std::stringstream ss(csv);
        std::vector tileData(height, std::vector<int>(width));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::string val;
                // Read characters from a ss into val until it hits a comma, or is at the end of the stream
                if (!std::getline(ss, val, ',')) break;
                tileData[i][j] = std::stoi(val); // stoi is a string-to-integer converter
            }
        }

        layers.push_back(tileData);
    }
}

void Map::draw(const Camera& cam) const {

    SDL_FRect src{}, dest{};

    dest.w = dest.h = 32;

    for (auto& layer : layers) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {

                const int gid = layer[row][col];
                if (gid == 0) continue;

                const auto* ts = getTilesetFromGid(gid);
                if (!ts) continue;

                const int localId = gid - ts->firstGid;
                const int srcX = (localId % ts->columns) * ts->tileWidth;
                const int srcY = (localId / ts->columns) * ts->tileHeight;

                src.x = static_cast<float>(srcX);
                src.y = static_cast<float>(srcY);
                src.w = static_cast<float>(ts->tileWidth);
                src.h = static_cast<float>(ts->tileHeight);

                const float worldX = static_cast<float>(col) * dest.w;
                const float worldY = static_cast<float>(row) * dest.h;

                dest.x = std::round(worldX - cam.view.x);
                dest.y = std::round(worldY - cam.view.y);

                TextureManager::draw(ts->texture, src, dest);
            }
        }
    }
}
