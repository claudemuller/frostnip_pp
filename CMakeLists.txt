cmake_minimum_required(VERSION 3.17)
project(frostbyte)

set(CMAKE_CXX_STANDARD 14)

# Adds the files that are part of the project
add_executable(frostbyte src/main.cpp src/Constants.h
        src/Utils/Benchmark.cpp src/Utils/Benchmark.h
        src/Game.cpp src/Game.h
        src/Utils/Utils.cpp src/Utils/Utils.h
        src/Utils/Vec2.cpp src/Utils/Vec2.h
        src/Entity.cpp src/Entity.h
        src/EntityManager.cpp src/EntityManager.h
        src/TextureManager.cpp src/TextureManager.h
        src/AssetManager.cpp src/AssetManager.h
        src/Animation.cpp src/Animation.h
        src/Map.cpp src/Map.h
        src/FontManager.cpp src/FontManager.h
        src/CollisionEngine.h src/CollisionEngine.cpp
        src/Component.h
        src/Components/TransformComponent.cpp src/Components/TransformComponent.h
        src/Components/SpriteComponent.cpp src/Components/SpriteComponent.h
        src/Components/KeyboardControlComponent.cpp src/Components/KeyboardControlComponent.cpp
        src/Components/TileComponent.cpp src/Components/TileComponent.cpp
        src/Components/ColliderComponent.cpp src/Components/ColliderComponent.cpp
        src/Components/TextLabelComponent.cpp src/Components/TextLabelComponent.cpp
        src/Components/ProjectileEmitterComponent.cpp src/Components/ProjectileEmitterComponent.h
        )

# Tells CMake that the find scripts are inside inside subfolder /cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${frostbyte_SOURCE_DIR}/cmake")

# Asks CMake to find the SDL libraries in our system
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Lua REQUIRED)

# Asks CMake to include the library folders during build
include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${LUA_INCLUDE_DIR})

# Asks CMake to link against the libraries during build
target_link_libraries(frostbyte
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${LUA_LIBRARIES})
