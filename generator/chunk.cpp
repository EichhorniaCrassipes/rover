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
    std::array<unsigned char, 256> var = {};

    for (int j = 0; j < size.y; j++)
        for (int i = 0; i < size.x; i++) {
            tiles[i + j * size.x] = {texturelist::maptiles[get4tiles(i+position.x, j+position.y)]};
            var[i + j * size.x] = std::rand() % 256;
        }
    if (!load("textures/test01.png", {64, 64}, tiles.data(), var.data(), size.x, size.y))
        cerr << "Failed to load tileset.png\n";
    // load_decorations("textures/deco01.png", {64, 64});
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
}

bool generator::Chunk::load(const string &tile_path, const Vector2u tileSize, const int* tiles, const unsigned char* var, const unsigned int width, const unsigned int height) {
    //cout << "[generator/chunk/load] tileset: " << tile_path << "\n\n";
    // load the tileset texture
    if (!m_tileset.loadFromFile(tile_path))
        return false;

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            // get the current tile number
            const int tileNumber = tiles[i + j * width];
            const unsigned char variationOffset = var[i + j * width];

            // find its position in the tileset texture
            const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            const int tv = variationOffset % (128/ tileSize.y);
            //std::cout <<tileNumber <<" "<<variationOffset<< " " << tu << " " << tv << "\n";
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
