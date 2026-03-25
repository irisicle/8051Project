cmake_minimum_required(VERSION 3.20)
project(8051Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tell CMake where Homebrew libraries are
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sdl3")

# Try to find SDL3
find_package(SDL3 REQUIRED)
find_package(SDL3_Image REQUIRED)

add_executable(8051Project src/main.cpp
        src/Game.cpp
        src/manager/TextureManager.cpp
        src/map/Map.cpp
        src/utils/Vector2D.cpp
        src/utils/Collision.cpp
        src/ecs/system/CollisionSystem.cpp
        src/vendor/tinyxml2.cpp
        src/manager/AssetManager.cpp
        src/scene/Scene.cpp
        src/ecs/system/EventResponseSystem.cpp
        src/ecs/system/MainMenuSystem.cpp
        src/ecs/system/MouseInputSystem.cpp)

target_link_libraries(8051Project SDL3::SDL3
SDL3_image::SDL3_image)