#include "chunk.h"
#include "../objects/map/tiletexturelist.h"

#include <iostream>
using std::cout;
using std::cerr;

#include "mapGenerator.h"

#include "../objects/map/stone.h"


generator::Chunk::Chunk(MapGenerator* generator_link, const int x, const int y) : position{x, y}, size{16, 16} {
    generator = generator_link;
    cout << "[generator/chunk] at x = " << x << ", y = " << y << '\n';
    std::array<int, 256> tiles = {};

    for (int j = 0; j < size.y; j++)
        for (int i = 0; i < size.x; i++) {
            tiles[i + j * size.x] = texturelist::maptiles[get4tiles(i+position.x, j+position.y)];
            auto tile_result = generator->get_tile(x + i, y + j);
            for (auto &decoration : tile_result.decorations)
                decorations_raw.push_back({
                    {static_cast<float>(x + i), static_cast<float>(y + j)},
                    decoration
                });
        }
    if (!load({64, 64}, tiles.data(), size.x, size.y))
        cerr << "Failed to load tileset.png\n";
    decorations_load();
    setPosition({static_cast<float>(position.x * size.x * 4), static_cast<float>(position.y * size.y * 4)});
}


string generator::Chunk::get4tiles(int x, int y) const {
    Tile tile0 = generator->get_tile(x, y);
    Tile tile1 = generator->get_tile(x + 1, y);
    Tile tile2 = generator->get_tile(x, y + 1);
    Tile tile3 = generator->get_tile(x + 1, y + 1);

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

void generator::Chunk::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();// getTransform() is defined by sf::Transformable
    states.transform.translate(Vector2f(32, 32));
    states.texture = &m_tileset;
    target.draw(vertices, states);

    for (const auto &d : decorations) {
        cout << "kamni\n";
        target.draw(*d);
    }
}

bool generator::Chunk::load(Vector2u tileSize, const int* tiles, const unsigned int width, const unsigned int height) {
    cout << "[generator/chunk/load] tileset: test01.png\n\n";
    // load the tileset texture
    if (!m_tileset.loadFromFile("textures/test01.png"))
        return false;

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            // get the current tile number
            const int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}

void generator::Chunk::decorations_load() {
    for (const auto &[abs_position, decoration] : decorations_raw) {
        cout << decoration.name << "\n";
        const auto tile = generator->get_tile(abs_position.x, abs_position.y);
        if (decoration.name == "stone")
            decorations.push_back(new object::Stone(abs_position, tile.biome, 0)); //tile.variation));
    }
}
