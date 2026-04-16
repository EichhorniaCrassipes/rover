cmake_minimum_required(VERSION 3.28)
project(ROVER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/.release")

set(RENDER_ICON FALSE)  # для добавления иконки на итоговый бинарник
if (RENDER_ICON)
    enable_language(RC)
    set(CMAKE_RC_COMPILER "windres.exe")
endif()

set(SOURCES
        main.cpp
        engine/engine.cpp
        engine/camera.cpp

        objects/object.cpp
        objects/entity.cpp
        objects/mapElement.cpp

        objects/entity/enemy.cpp
        objects/entity/mob.cpp
        objects/entity/npc.cpp
        objects/entity/player.cpp

        objects/map/block.cpp
        objects/map/building.cpp
        objects/map/chest.cpp
        objects/map/decoration.cpp
        objects/map/deposit.cpp
        objects/map/loot.cpp

        generator/PerlinNoise.cpp
        generator/mapGenerator.cpp
        generator/chunk.cpp
        generator/chunkDecorations.cpp
        generator/biomes.cpp
        generator/deposits.cpp
        generator/decorations.cpp

        scenes/game/gameScene.cpp

        scenes/UI/UIScene.cpp
        scenes/UI/testScene.cpp
        objects/map/stone.h
        objects/map/stone.cpp
)

if (RENDER_ICON)
    list(APPEND SOURCES icon.rc)
endif()

find_package(
        SFML 3 REQUIRED
        COMPONENTS System Window Graphics Audio Network
        PATHS "${CMAKE_SOURCE_DIR}/SFML-3.0.2/lib/cmake/SFML"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
        SFML::Network
)