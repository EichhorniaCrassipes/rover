#include "chunk.h"
#include "tiletexturelist.h"
#include "../engine/textures.h"

#include "mapGenerator.h"

#include <iostream>
using std::cout;

#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
using sf::Clock;

#include "SFML/Graphics/RenderTarget.hpp"


generator::Chunk::Chunk(MapGenerator* generator_link, const long long x, const long long y, Texture* texture) : position{x, y} {
    generator = generator_link;
    m_tileset = texture;
    //cout << "[generator/chunk] x = " << x << ", y = " << y << '\n';
    array<int, 256> tiles = {};
    array<unsigned char, 256> var = {};

    Clock timer;

    timer.start();
    for (int j = 0; j < size.y; j++)
        for (int i = 0; i < size.x; i++) {
            const long long x_local = i + position.x,
                            y_local = j + position.y;
            Tile tile0 = generator->get_tile(x_local,     y_local);
            Tile tile1 = generator->get_tile(x_local + 1, y_local);
            Tile tile2 = generator->get_tile(x_local,     y_local + 1);
            Tile tile3 = generator->get_tile(x_local + 1, y_local + 1);

            tiles[i + j * size.x] = {texture_list::maptiles[get4tiles(tile0, tile1, tile2, tile3)]};
            var[i + j * size.x] = tile0.variation;
        }
    //cout << "\tgenerating: " << timer.restart().asMilliseconds() << " ms\n";

    load({64, 64}, tiles.data(), var.data(), size.x, size.y);
    //cout << "\tloading: " << timer.getElapsedTime().asMilliseconds() << " ms\n";

    setPosition({static_cast<float>(position.x * size.x * 4), static_cast<float>(position.y * size.y * 4)});
}


string generator::Chunk::get4tiles(const Tile &tile0, const Tile &tile1, const Tile &tile2, const Tile &tile3) {
    string t0 = "0", t1 = "0", t2 = "0", t3 = "0";
    if (tile0.biome == "test1")
        t0 = '1';
    if (tile1.biome == "test1")
        t1 = '1';
    if (tile2.biome == "test1")
        t2 = '1';
    if (tile3.biome == "test1")
        t3 = '1';
    if (tile0.biome == "test0")
        t0 = '0';
    if (tile1.biome == "test0")
        t1 = '0';
    if (tile2.biome == "test0")
        t2 = '0';
    if (tile3.biome == "test0")
        t3 = '0';
    if (tile0.biome == "test2")
        t0 = '2';
    if (tile1.biome == "test2")
        t1 = '2';
    if (tile2.biome == "test2")
        t2 = '2';
    if (tile3.biome == "test2")
        t3 = '2';

    return t0+t1+t2+t3;
}

void generator::Chunk::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    states.transform.translate(Vector2f(32, 32));
    states.texture = m_tileset;
    target.draw(vertices, states);
}

void generator::Chunk::load(const Vector2u tileSize, const int* tiles, const unsigned char* var, const unsigned int width, const unsigned int height) {
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(width * height * 6);

    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            const int tileNumber = tiles[i + j * width];
            const unsigned char variationOffset = var[i + j * width];

            const int tu = tileNumber % (m_tileset->getSize().x / tileSize.x);
            const int tv = variationOffset % (128 / tileSize.y);

            sf::Vertex* triangles = &vertices[(i + j * width) * 6];

            triangles[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            triangles[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
}

Vector2<long long> generator::Chunk::getAbsolutePosition() const { return position; }
