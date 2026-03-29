//
// Created by Iris Chow on 2026-02-25.
//
#include "Scene.h"
#include "../game/Game.h"
#include "../manager/AssetManager.h"

Scene::Scene(
    const SceneType sceneType,
    const char* sceneName,
    const char* mapPath,
    const int windowWidth,
    const int windowHeight
    ) : name (sceneName), type(sceneType) {

    if (sceneType == SceneType::MainMenu) {
        initMainMenu(windowWidth, windowHeight);
        return;
    }

    initGameplay(mapPath, windowWidth, windowHeight);
}

void Scene::initMainMenu(const int windowWidth, const int windowHeight) {

    // Camera
    auto& cam(world.createEntity());
    cam.addComponent<Camera>();

    // Menu
    auto& menu(world.createEntity());
    const auto& menuTransform = menu.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);

    SDL_Texture* texture = TextureManager::load("../asset/ui/menu.png");
    SDL_FRect menuSrc { 0, 0, static_cast<float>(windowWidth), static_cast<float>(windowHeight) };
    SDL_FRect menuDest { menuTransform.position.x, menuTransform.position.y, menuSrc.w, menuSrc.h };
    menu.addComponent<Sprite>(texture, menuSrc, menuDest);

    auto& settingsOverlay = createSettingsOverlay(windowWidth, windowHeight);
    createCogButton(windowWidth, windowHeight, settingsOverlay);
}

void Scene::initGameplay(const char* mapPath, const int windowWidth, const int windowHeight) {

    // Load map
    world.getMap().load(mapPath);

    // Create colliders
    for (const auto& collider : world.getMap().colliders) {
        auto& water(world.createEntity());
        water.addComponent<Transform>(Vector2D(collider.rect.x * 2.0f, collider.rect.y * 2.0f), 0.0f, 1.0f);
        auto& c = water.addComponent<Collider>("water");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;
    }

    // Add entities
    auto& cam(world.createEntity());
    SDL_FRect camView{};
    camView.w = static_cast<float>(windowWidth);
    camView.h = static_cast<float>(windowHeight);
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);

    // Create save point (bed)
    for (const auto& p : world.getMap().savePoints) {
        auto& bed = world.createEntity();
        const auto& bedTransform = bed.addComponent<Transform>(Vector2D(p.position.x, p.position.y), 0.0f, 1.0f);

        SDL_Texture* bedTexture = TextureManager::load("../asset/objects/furniture.png");
        SDL_FRect bedSrc { 24, 24, 24, 24 };
        SDL_FRect bedDest { bedTransform.position.x, bedTransform.position.y, 48, 48 };
        bed.addComponent<Sprite>(bedTexture, bedSrc, bedDest);
    }

    // Create cows
    for (const auto& sp : world.getMap().spawnPoints) {
        auto& cow(world.createEntity());
        const auto& cowTransform = cow.addComponent<Transform>(Vector2D(sp.position.x, sp.position.y), 0.0f, 1.0f);

        auto& cowAnimation = AssetManager::getAnimation("cow");
        cow.addComponent<Animation>(cowAnimation);

        SDL_Texture* cowTexture = TextureManager::load("../asset/animations/animals/cow.png");
        SDL_FRect cowSrc { 32, 32, 32, 32 };
        SDL_FRect cowDest { cowTransform.position.x, cowTransform.position.y, 64, 64 };
        cow.addComponent<Sprite>(cowTexture, cowSrc, cowDest);

        auto& c = cow.addComponent<Collider>("cow");
        c.rect.w = cowDest.w;
        c.rect.h = cowDest.h;
    }

    // Create player
    auto& player(world.createEntity());
    const auto& playerTransform = player.addComponent<Transform>(Vector2D(140, 80), 0.0f, 1.0f);

    player.addComponent<Velocity>(Vector2D(0.0f, 0.0f), 120.0f);

    auto animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture* playerTexture = TextureManager::load("../asset/animations/character/player_spritesheet.png");
    SDL_FRect playerSrc = animation.clips[animation.currentClip].frameIndices[0];
    SDL_FRect playerDest { playerTransform.position.x, playerTransform.position.y, 64, 64 }; // Size of the sprite

    player.addComponent<Sprite>(playerTexture, playerSrc, playerDest);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDest.w;
    playerCollider.rect.h = playerDest.h;

    player.addComponent<Health>(Game::gameState.playerHealth);

    player.addComponent<PlayerTag>();

    // // Create table
    // for (const auto& c : world.getMap().colliders) {
    //     auto& table = world.createEntity();
    //     const auto& tableTransform = table.addComponent<Transform>(Vector2D(c.rect.x, c.rect.y), 0.0f, 1.0f);
    //     auto& collider = table.addComponent<Collider>("table");
    //     collider.rect.x = c.rect.x;
    //     collider.rect.y = c.rect.y;
    //
    //     SDL_Texture* tableTexture = TextureManager::load("../asset/objects/furniture.png");
    //     SDL_FRect tableSrc { 48, 48, 32, 32 };
    //     SDL_FRect tableDest { tableTransform.position.x, tableTransform.position.y, 48, 48 };
    //
    //     table.addComponent<Sprite>(tableTexture, tableSrc, tableDest);
    // }

    // // Create spawner
    // auto& spawner(world.createEntity());
    // const auto& spawnerTransform = spawner.addComponent<Transform>(Vector2D(static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f), 0.0f, 1.0f);
    // spawner.addComponent<TimedSpawner>(2.0f, [this, spawnerTransform] {
    //
    //     // Create projectile
    //     auto& enemy(world.createDeferredEntity());
    //     enemy.addComponent<Transform>(Vector2D(spawnerTransform.position.x, spawnerTransform.position.y), 0.0f, 1.0f);
    //     enemy.addComponent<Velocity>(Vector2D(0, -1), 100.0f);
    //
    //     const auto& enemyAnimation = AssetManager::getAnimation("enemy");
    //     enemy.addComponent<Animation>(enemyAnimation);
    //
    //     SDL_Texture* enemyTexture = TextureManager::load("../asset/animations/character/player_actions.png");
    //     SDL_FRect enemySrc { 0, 0, 32, 32 };
    //     SDL_FRect enemyDest { spawnerTransform.position.x, spawnerTransform.position.y, 32, 32 };
    //     enemy.addComponent<Sprite>(enemyTexture, enemySrc, enemyDest);
    //
    //     auto& c = enemy.addComponent<Collider>("projectile");
    //     c.rect.w = enemyDest.w;
    //     c.rect.h = enemyDest.h;
    //
    //     enemy.addComponent<ProjectileTag>();
    // });

    // Add scene state
    auto& state(world.createEntity());
    state.addComponent<SceneState>();
}

Entity& Scene::createSettingsOverlay(const int windowWidth, const int windowHeight) {
    auto& overlay(world.createEntity());

    SDL_Texture *overlayTexture = TextureManager::load("../asset/ui/settings_menu.png");
    SDL_FRect overlaySrc { 0, 0, static_cast<float>(windowWidth) * 0.85f, static_cast<float>(windowHeight) * 0.85f };
    SDL_FRect overlayDest{ static_cast<float>(windowWidth) / 2.0f - overlaySrc.w / 2.0f, static_cast<float>(windowHeight) / 2.0f - overlaySrc.h / 2.0f, overlaySrc.w, overlaySrc.h };

    overlay.addComponent<Transform>(Vector2D(overlayDest.x, overlayDest.y), 0.0f, 1.0f);
    overlay.addComponent<Sprite>(overlayTexture, overlaySrc, overlayDest, RenderLayer::UI, false);

    createSettingsUIComponents(overlay);

    return overlay;
}

Entity& Scene::createCogButton(const int windowWidth, const int windowHeight, Entity& overlay) {
    auto& cog(world.createEntity());
    auto& cogTransform = cog.addComponent<Transform>(Vector2D(static_cast<float>(windowWidth - 50), static_cast<float>(windowHeight - 50)), 0.0f, 1.0f);

    SDL_Texture *texture = TextureManager::load("../asset/ui/Catpaw_holding_Mouse_icon.png");
    SDL_FRect cogSrc { 0, 0, 32, 32 };
    SDL_FRect cogDest { cogTransform.position.x, cogTransform.position.y, cogSrc.w, cogSrc.h };

    cog.addComponent<Sprite>(texture, cogSrc, cogDest);
    cog.addComponent<Collider>("ui", cogDest);

    auto& clickable = cog.addComponent<Clickable>();

    clickable.onPressed = [&cogTransform] {
        cogTransform.scale = 0.5f;
    };

    clickable.onReleased = [&cogTransform, &overlay] {
        cogTransform.scale = 1.0f;
        toggleSettingsOverlayVisibility(overlay);
    };

    clickable.onCancel = [&cogTransform] {
        cogTransform.scale = 1.0f;
    };

    return cog;
}

void Scene::createSettingsUIComponents(Entity& overlay) {
    if (!overlay.hasComponent<Children>()) {
        overlay.addComponent<Children>();
    }

    const auto& overlayTransform = overlay.getComponent<Transform>();
    const auto& overlaySprite = overlay.getComponent<Sprite>();

    const float baseX = overlayTransform.position.x;
    const float baseY = overlayTransform.position.y;

    auto& closeButton(world.createEntity());
    auto& closeTransform = closeButton.addComponent<Transform>(Vector2D(baseX + overlaySprite.dst.w - 40, baseY + 10), 0.0f, 1.0f);

    SDL_Texture *texture = TextureManager::load("../asset/ui/Catpaw_Mouse_icon.png");
    SDL_FRect closeSrc { 0, 0, 32, 32 };
    SDL_FRect closeDest { closeTransform.position.x, closeTransform.position.y, closeSrc.w, closeSrc.h };

    closeButton.addComponent<Sprite>(texture, closeSrc, closeDest, RenderLayer::UI, false);
    closeButton.addComponent<Collider>("ui", closeDest);

    auto& clickable = closeButton.addComponent<Clickable>();

    clickable.onPressed = [&closeTransform] {
        closeTransform.scale = 0.5f;
    };

    clickable.onReleased = [&overlay, &closeTransform] {
        closeTransform.scale = 1.0f;
        toggleSettingsOverlayVisibility(overlay);
    };

    clickable.onCancel = [&closeTransform] {
        closeTransform.scale = 1.0f;
    };

    closeButton.addComponent<Parent>(&overlay);

    auto& parentChildren = overlay.addComponent<Children>();
    parentChildren.children.push_back(&closeButton);
}

void Scene::toggleSettingsOverlayVisibility(Entity& overlay) {
    auto& sprite = overlay.getComponent<Sprite>();
    const bool newVisibility = !sprite.visible;
    sprite.visible = newVisibility;

    if (overlay.hasComponent<Children>()) {
        auto& c = overlay.getComponent<Children>();

        for (const auto& child : c.children) {
            if (child && child->hasComponent<Sprite>()) {
                child->getComponent<Sprite>().visible = newVisibility;
            }

            if (child && child->hasComponent<Collider>()) {
                child->getComponent<Collider>().enabled = newVisibility;
            }
        }
    }
}
