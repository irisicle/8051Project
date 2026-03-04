//
// Created by Iris Chow on 2026-01-14.
//
#include "TextureManager.h"

#include <iostream>
#include <ostream>
#include <ranges>

#include "../Game.h"

// Doesn't create any extra memory, just grabs the reference of this object
extern Game* game;
std::unordered_map<std::string, SDL_Texture*> TextureManager::textures;

// Load texture with a path
SDL_Texture* TextureManager::load(const char* path) {

    // Caching: storing the result of some work so you don't have to repeat the work next time
    // Check if the texture already exists in the map
    if (const auto it = textures.find(path); it != textures.end()) { // If the iterator is not at the end
        return it->second;
    }

    // What is a surface? A surface represents an image in RAM (CPU memory)
    // Do we want to do anything with the image before we store it in GPU?
    SDL_Surface* tempSurface = IMG_Load(path);
    if (!tempSurface) {
        std::cout << "Failed to load image: " << path << std::endl;
    }

    // Texture represents an image in VRAM (GPU memory)
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, tempSurface);

    // Clean up surface
    SDL_DestroySurface (tempSurface);

    // Check if the texture creation was successful
    if (!texture) {
        std::cout << "Failed to create texture: " << path << std::endl;
        return nullptr;
    }

    // Store the new texture in the cache
    textures[path] = texture;
    return texture;
}

void TextureManager::draw(SDL_Texture* texture, const SDL_FRect src, const SDL_FRect dst) {
    // Draw the texture to the screen from the VRAM
    SDL_RenderTexture(game->renderer, texture, &src, &dst);
}

void TextureManager::clean() {
    for (auto &val: textures | std::views::values) {
        SDL_DestroyTexture(val);
        val = nullptr;
    }
    textures.clear();
}