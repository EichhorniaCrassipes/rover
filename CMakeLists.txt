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
        test.cpp
        objects/object.h
        objects/object.cpp
        objects/entity.h
        objects/entity.cpp
        objects/mapElement.h
        utils/generator/PerlinNoise.cpp
        utils/generator/mapGenerator.cpp
        objects/block.cpp
        objects/building.cpp
        objects/chest.cpp
        objects/decoration.cpp
        objects/deposit.cpp
        objects/enemy.cpp
        objects/entity.cpp
        objects/loot.cpp
        objects/mapElement.cpp
        objects/mob.cpp
        objects/npc.cpp
        objects/object.cpp
        objects/player.cpp
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