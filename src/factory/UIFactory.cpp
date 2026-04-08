//
// Created by Iris Chow on 2026-03-30.
//

#include "UIFactory.h"
#include "../ecs/core/World.h"
#include "../ecs/component/UI.h"
#include "../utils/Constants.h"

Entity& UIFactory::createMainMenu(World &world, const int width, const int height) {
    auto& menu(world.createEntity());
    const auto& transform = menu.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);

    SDL_Texture* texture = TextureManager::load("../asset/ui/menu.png");
    SDL_FRect src { 0, 0, static_cast<float>(width), static_cast<float>(height) };
    menu.addComponent<Sprite>(texture, src, static_cast<float>(width), static_cast<float>(height), RenderLayer::UI);

    return menu;
}

Entity& UIFactory::createSettingsOverlay(World& world, const int width, const int height) {
    auto& overlay(world.createEntity());

    SDL_Texture *texture = TextureManager::load("../asset/ui/settings_menu.png");
    SDL_FRect src { 0, 0, static_cast<float>(width) * 0.85f, static_cast<float>(height) * 0.85f };

    overlay.addComponent<Transform>(Vector2D(src.x, src.y), 0.0f, 1.0f);
    overlay.addComponent<Sprite>(texture, src, static_cast<float>(width), static_cast<float>(height), RenderLayer::UI, false);

    createSettingsUIComponents(world, overlay);

    return overlay;

}

Entity& UIFactory::createCogButton(World& world, const int width, const int height, Entity& overlay) {
    auto& cog(world.createEntity());
    auto& transform = cog.addComponent<Transform>(Vector2D(static_cast<float>(width - 50), static_cast<float>(height - 50)), 0.0f, 1.0f);

    SDL_Texture *texture = TextureManager::load("../asset/ui/mouse/catpaw_holding_mouse_icon.png");
    SDL_FRect src { 0, 0, 32, 32 };

    cog.addComponent<Sprite>(texture, src);
    // cog.addComponent<Collider>("ui");

    auto& clickable = cog.addComponent<Clickable>();

    clickable.onPressed = [&transform] {
        transform.scale = 0.5f;
    };

    clickable.onReleased = [&transform, &overlay] {
        transform.scale = Constants::SCALE;
        toggleSettingsOverlayVisibility(overlay);
    };

    clickable.onCancel = [&transform] {
        transform.scale = Constants::SCALE;
    };

    return cog;
}

void UIFactory::createSettingsUIComponents(World& world, Entity& overlay) {
    if (!overlay.hasComponent<Children>()) {
        overlay.addComponent<Children>();
    }

    const auto& transform = overlay.getComponent<Transform>();
    const auto& sprite = overlay.getComponent<Sprite>();

    const float baseX = transform.position.x;
    const float baseY = transform.position.y;

    auto& closeButton(world.createEntity());
    auto& closeTransform = closeButton.addComponent<Transform>(Vector2D(baseX + sprite.width - 40, baseY + 10), 0.0f, 1.0f);

    SDL_Texture *texture = TextureManager::load("../asset/ui/mouse/catpaw_mouse_icon.png");
    SDL_FRect closeSrc { 0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE };
    SDL_FRect closeDest { closeTransform.position.x, closeTransform.position.y, closeSrc.w, closeSrc.h };

    closeButton.addComponent<Sprite>(texture, closeSrc, closeDest.w, closeDest.h, RenderLayer::UI, false);
    // closeButton.addComponent<Collider>("ui", closeDest);

    auto& clickable = closeButton.addComponent<Clickable>();

    clickable.onPressed = [&closeTransform] {
        closeTransform.scale = 0.5f;
    };

    clickable.onReleased = [&overlay, &closeTransform] {
        closeTransform.scale = Constants::SCALE;
        toggleSettingsOverlayVisibility(overlay);
    };

    clickable.onCancel = [&closeTransform] {
        closeTransform.scale = Constants::SCALE;
    };

    closeButton.addComponent<Parent>(&overlay);

    auto& parentChildren = overlay.addComponent<Children>();
    parentChildren.children.push_back(&closeButton);
}

void UIFactory::toggleSettingsOverlayVisibility(Entity& overlay) {
    auto& sprite = overlay.getComponent<Sprite>();
    const bool newVisibility = !sprite.visible;

    sprite.visible = newVisibility;

    if (overlay.hasComponent<Children>()) {
        for (auto&[children] = overlay.getComponent<Children>(); const auto& child : children) {
            if (child && child->hasComponent<Sprite>()) {
                child->getComponent<Sprite>().visible = newVisibility;
            }

            if (child && child->hasComponent<Collider>()) {
                child->getComponent<Collider>().enabled = newVisibility;
            }
        }
    }
}
