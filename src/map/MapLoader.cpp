//
// Created by Iris Chow on 2026-04-04.
//

#include "MapLoader.h"
#include <iostream>
#include <ostream>
#include <sstream>

#include "TileData.h"
#include "../ecs/core/World.h"
#include "../manager/TextureManager.h"
#include "../utils/Constants.h"
#include "../vendor/tinyxml2.h"

MapData MapLoader::load(const char* path, World &world) {
    MapData mapData{};

    tinyxml2::XMLDocument doc;

    if (doc.LoadFile(path) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Could not load map \"" << path << "\"" << std::endl;
        return mapData;
    }

    std::cout << "Loaded map \"" << path << "\"" << std::endl;

    auto *mapNode = doc.FirstChildElement("map");
    mapData.width = mapNode->IntAttribute("width");
    mapData.height = mapNode->IntAttribute("height");

    for (auto &layer: mapData.grid) {
        layer.clear();
        layer.resize(mapData.width * mapData.height, nullptr);
    }

    mapData.farmTiles.resize(mapData.width * mapData.height);

    // Load tilesets
    for (auto *ts = mapNode->FirstChildElement("tileset"); ts != nullptr; ts = ts->NextSiblingElement("tileset")) {
        Tileset tileset{};
        tileset.firstGid = ts->IntAttribute("firstgid");

        const char *source = ts->Attribute("source");
        if (!source) {
            continue;
        }

        tinyxml2::XMLDocument tsx;
        std::string fullPath = std::string("../asset/") + source;

        if (tsx.LoadFile(fullPath.c_str()) != tinyxml2::XML_SUCCESS) {
            std::cerr << "Could not load tsx \"" << fullPath << "\"" << std::endl;
            continue;
        }

        auto *tsxNode = tsx.FirstChildElement("tileset");
        if (!tsxNode) {
            std::cerr << "Could not find tileset \"" << fullPath << "\"" << std::endl;
            continue;
        }

        tileset.tileWidth = tsxNode->IntAttribute("tilewidth");
        tileset.tileHeight = tsxNode->IntAttribute("tileheight");
        tileset.columns = tsxNode->IntAttribute("columns");
        tileset.tileCount = tsxNode->IntAttribute("tilecount");

        const auto *imgNode = tsxNode->FirstChildElement("image");
        if (!imgNode) {
            continue;
        }

        const char *imgSrc = imgNode->Attribute("source");
        if (!imgSrc) {
            continue;
        }

        std::string imgPath = std::string("../asset/tilesets/") + imgSrc;
        tileset.texture = TextureManager::load(imgPath.c_str());

        mapData.tilesets.push_back(tileset);
    }

    // Parse terrain layers and create tile entities
    for (auto *layer = mapNode->FirstChildElement("layer"); layer != nullptr; layer = layer->NextSiblingElement("layer")) {
        const char *layerName = layer->Attribute("name");
        std::string name(layerName);

        TileLayer currentLayer{};

        if (name == "Water Layer") currentLayer = TileLayer::Water;
        else if (name == "Terrain Layer") currentLayer = TileLayer::Terrain;
        else if (name == "Environment Layer") currentLayer = TileLayer::Environment;
        else if (name == "Soil Layer") currentLayer = TileLayer::Soil;
        else if (name == "Farming Layer") currentLayer = TileLayer::Farming;
        else if (name == "Path Layer") currentLayer = TileLayer::Path;
        else if (name == "Fence Layer") currentLayer = TileLayer::Fence;
        else if (name == "Building Layer") currentLayer = TileLayer::Building;

        auto *data = layer->FirstChildElement("data");
        if (!data || !data->GetText()) {
            continue;
        }

        std::string csv = data->GetText();
        std::stringstream ss(csv);

        for (int row = 0; row < mapData.height; row++) {
            for (int col = 0; col < mapData.width; col++) {
                std::string val;

                // Read characters from a ss into val until it hits a comma, or is at the end of the stream
                if (!std::getline(ss, val, ',')) break;

                const int gid = std::stoi(val);

                // Don't create a tile entity if gid is empty
                if (gid == 0) {
                    mapData.setEntityAt(col, row, nullptr, currentLayer);
                    continue;
                }

                // Create farming tiles for farming layer
                if (currentLayer == TileLayer::Farming) {
                    if (FarmTile* farmTile = mapData.getFarmTileAt(col, row)) {
                        farmTile->isFarmable = true;
                    }

                    // Don't create a tile entity for farming layer
                    mapData.setEntityAt(col, row, nullptr, currentLayer);
                    continue;
                }

                auto &tile = world.createEntity();

                if (const auto *ts = mapData.getTilesetFromGid(gid)) {
                    tile.addComponent<Sprite>(ts->texture);
                    tile.addComponent<TileData>(gid, TileState::UNTILLED);
                    tile.addComponent<Transform>(Vector2D(
                        static_cast<float>(col) * Constants::TILE_SIZE,
                        static_cast<float>(row) * Constants::TILE_SIZE), 0.0f, 1.0f
                    );

                    mapData.setEntityAt(col, row, &tile, currentLayer);
                }
            }
        }
    }

    // Load object layers
    for (auto* objectGroup = mapNode->FirstChildElement("objectgroup"); objectGroup != nullptr; objectGroup = objectGroup->NextSiblingElement("objectgroup")) {
        const char* objectGroupName = objectGroup->Attribute("name");
        if (!objectGroupName) {
            continue;
        }

        std::string name(objectGroupName);

        for (auto* object = objectGroup->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object")) {

            // Load walls
            if (name == "Collision Layer") {
                MapCollider collider{};
                collider.bounds.x = object->FloatAttribute("x");
                collider.bounds.y = object->FloatAttribute("y");
                collider.bounds.w = object->FloatAttribute("width");
                collider.bounds.h = object->FloatAttribute("height");

                mapData.colliders.push_back(collider);
            }

            else if (name == "Animal Layer") {
                SpawnMarker marker{};
                marker.position.x = object->FloatAttribute("x");
                marker.position.y = object->FloatAttribute("y");
                marker.type = "Animal";

                mapData.spawnMarkers.push_back(marker);
            }
        }
    }

    return mapData;
}
