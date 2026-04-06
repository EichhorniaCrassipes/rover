#include "chunk.h"

#include <iostream>

#include "../../generator/mapGenerator.h"
#include "SFML/Graphics/RenderTarget.hpp"

Chunk::Chunk(generator::MapGenerator gen, int x, int y): size{16, 16}, position{x, y}
{
    std::array<int, 256> tiles = {};
    for (int j = 0; j < size.y; j++)
        for (int i = 0; i < size.x; i++)
        {
            generator::Tile tile = gen.get_tile(i*10 + position.x, j*10 + position.y);
            if (tile.biome == "test0")
           tiles[i + j*size.x] = 0;
            else if (tile.biome == "test1")
                tiles[i + j*size.x] = 1;
        }
    if (!load("textures/tileset.png", {16, 16}, tiles.data(), size.x, size.y))
        std::cout << "Failed to load tileset.png" << std::endl;
}
Chunk::~Chunk()
{

}

void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
    states.texture = &m_tileset;
    target.draw(vertices, states);
}

bool Chunk::load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
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