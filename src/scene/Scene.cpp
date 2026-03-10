//
// Created by Iris Chow on 2026-02-25.
//
#include "Scene.h"
#include "../Game.h"
#include "../manager/AssetManager.h"

Scene::Scene(
    const SceneType sceneType,
    const char* sceneName,
    const char* mapPath,
    const int windowWidth,
    const int windowHeight
    ) : name (sceneName), type(sceneType) {

    if (sceneType == SceneType::MainMenu) {
        // Camera
        auto& cam(world.createEntity());
        cam.addComponent<Camera>();

        // Menu
        auto& menu(world.createEntity());
        const auto& menuTransform = menu.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);

        SDL_Texture* texture = TextureManager::load("../asset/menu.png");
        SDL_FRect menuSrc {0, 0, static_cast<float>(windowWidth), static_cast<float>(windowHeight)};
        SDL_FRect menuDest {menuTransform.position.x, menuTransform.position.y, menuSrc.w, menuSrc.h};
        menu.addComponent<Sprite>(texture, menuSrc, menuDest);
        return;
    }

    // Load map
    world.getMap().load(mapPath, TextureManager::load("../asset/tileset.png"));

    // Create wall colliders
    for (auto& collider : world.getMap().colliders) {
        auto& entity = world.createEntity();
        entity.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto&[tag, rect] = entity.addComponent<Collider>("wall");
        rect.x = collider.rect.x;
        rect.y = collider.rect.y;
        rect.w = collider.rect.w;
        rect.h = collider.rect.h;
    }

    // Add entities
    auto& cam(world.createEntity());
    SDL_FRect camView{};
    camView.w = static_cast<float>(windowWidth);
    camView.h = static_cast<float>(windowHeight);
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);

    // Create item spawn points
    for (const auto& spawnPoint : world.getMap().spawnPoints) {
        auto& item = world.createEntity();
        const auto& itemTransform = item.addComponent<Transform>(Vector2D(spawnPoint.position.x, spawnPoint.position.y), 0.0f, 1.0f);

        SDL_Texture* itemTexture = TextureManager::load("../asset/coin.png");
        SDL_FRect itemSrc {0, 0, 32, 32};
        SDL_FRect itemDest {itemTransform.position.x, itemTransform.position.y, 32, 32};

        // Import coin sprite
        item.addComponent<Sprite>(itemTexture, itemSrc, itemDest);
        auto&[tag, rect] = item.addComponent<Collider>("item");
        rect.w = itemDest.w;
        rect.h = itemDest.h;

    }

    // Create player
    auto& player(world.createEntity());
    const auto& playerTransform = player.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);

    player.addComponent<Velocity>(Vector2D(10.0f, 20.0f), 120.0f);

    auto animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture* playerTexture = TextureManager::load("../asset/animations/Slime2_Attack_without_shadow.png");
    SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0];
    SDL_FRect playerDst {playerTransform.position.x, playerTransform.position.y, 64, 64}; // Size of the sprite

    player.addComponent<Sprite>(playerTexture, playerSrc, playerDst);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    player.addComponent<Health>(Game::gameState.playerHealth);

    player.addComponent<PlayerTag>();

    // Create spawner
    auto& spawner(world.createEntity());
    const auto& spawnerTransform = spawner.addComponent<Transform>(Vector2D(static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f), 0.0f, 1.0f);
    spawner.addComponent<TimedSpawner>(2.0f, [this, spawnerTransform] {

        // Create projectile
        auto& enemy(world.createDeferredEntity());
        enemy.addComponent<Transform>(Vector2D(spawnerTransform.position.x, spawnerTransform.position.y), 0.0f, 1.0f);
        enemy.addComponent<Velocity>(Vector2D(0, -1), 100.0f);

        const auto& enemyAnimation = AssetManager::getAnimation("enemy");
        enemy.addComponent<Animation>(enemyAnimation);

        SDL_Texture* enemyTexture = TextureManager::load("../asset/animations/Slime1_Attack_body.png");
        SDL_FRect enemySrc {0, 0, 64, 64};
        SDL_FRect enemyDst {spawnerTransform.position.x, spawnerTransform.position.y, 64, 64};
        enemy.addComponent<Sprite>(enemyTexture, enemySrc, enemyDst);

        auto&[tag, rect] = enemy.addComponent<Collider>("projectile");
        rect.w = enemyDst.w;
        rect.h = enemyDst.h;

        enemy.addComponent<ProjectileTag>();
    });

    // Add scene state
    auto& state(world.createEntity());
    state.addComponent<SceneState>();
}
