//
// Created by Iris Chow on 2026-03-30.
//

#include "EntityFactory.h"
#include "../ecs/component/Interaction.h"
#include "../ecs/core/World.h"
#include "../manager/AssetManager.h"
#include "../ecs/component/Render.h"
#include "../ecs/component/Inventory.h"
#include "../ecs/component/Physics.h"
#include "../ecs/component/Tag.h"
#include "../game/data/CropData.h"
#include "../game/data/CropVisualDatabase.h"
#include "../utils/Constants.h"
#include "../utils/CropEnums.h"

struct Inventory;

Entity& EntityFactory::createPlayer(World& world) {
    auto& player(world.createEntity());
    player.addComponent<PlayerTag>();
    player.addComponent<PlayerIntent>();
    player.addComponent<Transform>(Vector2D(140, 80), 0.0f, 1.0f);
    player.addComponent<Velocity>(Vector2D(0.0f, 0.0f), 120.0f);
    player.addComponent<Facing>(Direction::DOWN);
    player.addComponent<Inventory>();

    auto animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture* texture = TextureManager::load("../asset/animations/character/player_spritesheet.png");
    SDL_FRect src = animation.clips.at(animation.currentClip).frames[0];
    player.addComponent<Sprite>(texture, src, 64.0f, 64.0f, RenderLayer::WORLD, true);

    return player;
}

Entity& EntityFactory::createCow(World &world, const Vector2D& position) {
    auto& cow(world.createEntity());
    const auto& transform = cow.addComponent<Transform>(position, 0.0f, 1.0f);

    SDL_Texture* texture = TextureManager::load("../asset/animations/animals/cow.png");

    auto animation = AssetManager::getAnimation("cow");
    animation.currentClip = "idle";
    animation.currentFrame = 0;
    animation.frameTimer = 0.0f;
    cow.addComponent<Animation>(animation);

    SDL_FRect src{32, 32, 32, 32};
    cow.addComponent<Sprite>(texture, src, 64.0f, 64.0f, RenderLayer::WORLD, true);

    return cow;
}

Entity& EntityFactory::createCrop(World &world, CropType type, const int x, const int y) {
    auto& crop = world.createEntity();

    crop.addComponent<Crop>(type, 0, 10.0f);
    crop.addComponent<Transform>(Vector2D(
        static_cast<float>(x) * Constants::TILE_SIZE,
        static_cast<float>(y) * Constants::TILE_SIZE),
        0.0f,
        1.0f);

    return crop;
}
