cmake_minimum_required(VERSION 3.28)
project(ROVER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/.release")

set(RELEASE_FLAG FALSE)  # флаг для сборки публичной релизной версии
if (RELEASE_FLAG)
    enable_language(RC)
    set(CMAKE_RC_COMPILER "windres.exe")
    set(WINDOWED_MODE "WIN32")
else()
    set(WINDOWED_MODE "")
endif()

set(SOURCES
        main.cpp
        engine/engine.cpp
        engine/camera.cpp

        objects/object.cpp

        objects/entity.cpp
        objects/entity/mob.cpp
        objects/entity/npc.cpp
        objects/entity/enemy.cpp
        objects/entity/player.cpp

        objects/block.cpp
        objects/block/building.cpp
        objects/block/building/furnace.cpp
        objects/block/building/furnace/mk1.cpp
        objects/block/building/drill.cpp
        objects/block/building/drill/mk1.cpp
        objects/block/building/spawn.cpp
        objects/block/deposit.cpp
        objects/block/deposit/coal.cpp
        objects/block/deposit/copper.cpp
        objects/block/deposit/iron.cpp
        objects/block/deposit/stone.cpp
        objects/block/loot.cpp

        generator/PerlinNoise.cpp
        generator/mapGenerator.cpp
        generator/chunks/chunk.cpp
        generator/chunks/chunkDecorations.cpp
        generator/config/biomes.cpp
        generator/config/deposits.cpp
        generator/config/decorations.cpp

        scenes/scene.cpp
        scenes/game/gameScene.cpp
        scenes/UI/UIScene.cpp
        scenes/UI/menuScene.cpp
        scenes/UI/cutscene/cutScene.cpp
        scenes/UI/gameUIScene.cpp
        scenes/UI/settingsScene.cpp
        scenes/UI/aboutScene.cpp

        objects/ui/gameMenu.cpp
        objects/ui/gameInventory.cpp

)

if (RENDER_ICON)
    list(APPEND SOURCES icon.rc)
endif()

find_package(
        SFML 3 REQUIRED
        COMPONENTS System Window Graphics Audio Network
        PATHS "${CMAKE_SOURCE_DIR}/SFML-3.0.2/lib/cmake/SFML"
)

add_executable(${PROJECT_NAME} ${WINDOWED_MODE} ${SOURCES})
target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
        SFML::Network
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders"
        COMMENT "Copying shaders to runtime directory"
)