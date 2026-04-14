#include "chunk.h"
#include "tiletexturelist.h"

#include <iostream>
using std::cout;
using std::cerr;

#include "../../generator/mapGenerator.h"
#include "SFML/Graphics/RenderTarget.hpp"

string get4tiles(const generator::MapGenerator& gen, int x, int y) {
    generator::Tile tile0 = gen.get_tile(x, y);
    generator::Tile tile1 = gen.get_tile(x + 1, y);
    generator::Tile tile2 = gen.get_tile(x, y + 1);
    generator::Tile tile3 = gen.get_tile(x + 1, y + 1);
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
    return t0+t1+t2+t3;
}

Chunk::Chunk(const generator::MapGenerator &gen, int x, int y): size{16, 16}, position{x, y} {
    cout << "[generator/chunk] at x = " << x << ", y = " << y << '\n';
    std::array<int, 256> tiles = {};

    for (int j = 0; j < size.y; j++)
        for (int i = 0; i < size.x; i++)
            tiles.at(i + j * size.x) = texturelist::maptiles[get4tiles(gen, i+position.x, j+position.y)];
    if (!load( {64, 64}, tiles.data(), size.x, size.y))
        cerr << "Failed to load tileset.png\n";
    setPosition({static_cast<float>(position.x * size.x * 4), static_cast<float>(position.y * size.y * 4)});
}

void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();// getTransform() is defined by sf::Transformable
    states.transform.translate(sf::Vector2f(32, 32));
    states.texture = &m_tileset;
    target.draw(vertices, states);
}

bool Chunk::load( sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) {
    cout << "[generator/chunk/load] tileset: test01.png\n\n";
    // load the tileset texture
    if (!m_tileset.loadFromFile("textures/test01.png"))
        return false;

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            const int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}