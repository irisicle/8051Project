//
// Created by Iris Chow on 2026-04-08.
//

#include "InventoryUISystem.h"

#include "../ecs/component/Inventory.h"
#include "../ecs/component/Tag.h"
#include "../ecs/core/Entity.h"
#include "../manager/TextureManager.h"
#include "../game/data/ItemDatabase.h"

void InventoryUISystem::render(const std::vector<std::unique_ptr<Entity>>& entities, SDL_Renderer* renderer) {
    if (!renderer) {
        return;
    }

    Entity* player = nullptr;

    for (const auto& entity : entities) {
        if (entity->hasComponent<PlayerTag>() && entity->hasComponent<Inventory>()) {
            player = entity.get();
            break;
        }
    }

    if (!player) {
        return;
    }

    const auto& inventory = player->getComponent<Inventory>();
    const int slotCount = static_cast<int>(inventory.items.size());

    if (slotCount <= 0) {
        return;
    }

    int screenWidth = 0;
    int screenHeight = 0;
    SDL_GetRenderOutputSize(renderer, &screenWidth, &screenHeight);

    constexpr float slotSize = 56.0f;
    constexpr float spacing = 8.0f;

    const float totalWidth = static_cast<float>(slotCount) * slotSize + static_cast<float>(slotCount - 1) * spacing;
    const float startX = (static_cast<float>(screenWidth) - totalWidth) * 0.5f;
    const float startY = static_cast<float>(screenHeight) - slotSize - 20.0f;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (int i = 0; i < slotCount; ++i) {
        const float x = startX + static_cast<float>(i) * (slotSize + spacing);
        const float y = startY;

        const SDL_FRect slotRect{
            x,
            y,
            slotSize,
            slotSize
        };

        // slot fill
        SDL_SetRenderDrawColor(renderer, 35, 35, 35, 100);
        SDL_RenderFillRect(renderer, &slotRect);

        // base border
        SDL_SetRenderDrawColor(renderer, 180, 180, 180, 180);
        SDL_RenderRect(renderer, &slotRect);

        // selected slot highlight
        if (i == inventory.selectedIndex) {
            constexpr float padding = 4.0f;

            const SDL_FRect selectedRect{
                x - 3.0f,
                y - 3.0f,
                slotSize + padding * 2.0f,
                slotSize + padding * 2.0f
            };

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
            SDL_RenderRect(renderer, &selectedRect);
        }

        const auto& slot = inventory.items[i];

        if (const auto& itemData = ItemDatabase::get(slot.id); slot.id != ItemId::NONE && itemData.texture) {
            constexpr float iconPadding = 8.0f;
            const SDL_FRect iconDest{
                x + iconPadding,
                y + iconPadding,
                slotSize - iconPadding * 2.0f,
                slotSize - iconPadding * 2.0f
            };

            TextureManager::draw(itemData.texture, itemData.src, iconDest);
        }

        // Count badge placeholder (visual box)
        // Replace with real text rendering if you have SDL_ttf or your own text system
        if (slot.count > 1) {
            const SDL_FRect countRect{
                x + slotSize - 18.0f,
                y + slotSize - 18.0f,
                14.0f,
                14.0f
            };

            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 80);
            SDL_RenderFillRect(renderer, &countRect);

            SDL_SetRenderDrawColor(renderer, 220, 220, 220, 80);
            SDL_RenderRect(renderer, &countRect);
        }
    }
}