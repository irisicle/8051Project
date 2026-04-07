cmake_minimum_required(VERSION 3.20)
project(8051Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tell CMake where Homebrew libraries are
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sdl3")

# Try to find SDL3
find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_Image REQUIRED CONFIG)
find_package(SDL3_mixer REQUIRED CONFIG)

add_executable(8051Project src/main.cpp
        src/game/Game.cpp
        src/manager/TextureManager.cpp
        src/utils/Vector2D.cpp
        src/utils/Collision.cpp
        src/systems/CollisionSystem.cpp
        src/vendor/tinyxml2.cpp
        src/manager/AssetManager.cpp
        src/scene/Scene.cpp
        src/systems/MainMenuSystem.cpp
        src/systems/MouseInputSystem.cpp
        src/systems/KeyboardInputSystem.cpp
        src/factory/EntityFactory.cpp
        src/factory/UIFactory.cpp
        src/map/MapLoader.cpp
        src/systems/AnimationSystem.cpp
        src/systems/MovementSystem.cpp
        src/game/data/ItemDatabase.cpp
        src/map/MapRenderer.cpp
        src/game/services/CropService.cpp
        src/game/data/CropVisualDatabase.cpp
        src/systems/CollisionResponseSystem.cpp
        src/systems/SpriteSystem.cpp
        src/systems/RenderSystem.cpp
        src/factory/MapEntityFactory.cpp
        src/systems/EventBindings.cpp
        src/game/services/ToolService.cpp
        src/systems/SelectionHighlightSystem.cpp
        src/manager/AudioManager.cpp)

target_link_libraries(8051Project SDL3::SDL3
SDL3_image::SDL3_image
SDL3_mixer::SDL3_mixer)