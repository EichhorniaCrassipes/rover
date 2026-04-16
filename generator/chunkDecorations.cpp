#include "chunkDecorations.h"

#include <iostream>
using std::cout;
using std::cerr;

#include "mapGenerator.h"

#include "../objects/map/stone.h"


generator::ChunkDecorations::ChunkDecorations(MapGenerator* generator_link, const int x, const int y) : position{x, y}, size{16, 16} {
    generator = generator_link;
    cout << "\n[generator/chunkDecorations] at x = " << x << ", y = " << y << '\n';

    for (int j = 0; j < size.y; j++)
        for (int i = 0; i < size.x; i++) {
            auto tile_result = generator->get_tile(x + i, y + j);
            for (const auto &decoration : tile_result.decorations)
                decorations.push_back({
                    tile_result.biome,
                    decoration,
                    {static_cast<float>(i), static_cast<float>(j)}
                });
        }

    if (!load("textures/deco01.png", {64, 64}))
        cerr << "Failed to load decoration set\n";

    setPosition({static_cast<float>(position.x * size.x * 4), static_cast<float>(position.y * size.y * 4)});
}

void generator::ChunkDecorations::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    states.transform.scale({64, 64});
    states.texture = &m_decorations;
    target.draw(decoration_vertices, states);
}

bool generator::ChunkDecorations::load(const string &set_path, const Vector2u tileSize) {
    cout << "[generator/chunkDecorations/load] " << set_path << '\n';
    if (!m_decorations.loadFromFile(set_path)) return false;

    decoration_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    cout << decorations.size() << '\n';
    decoration_vertices.resize(decorations.size() * 6);

    size_t i = 0;
    for (const auto &[biome, decoration, coordinates] : decorations) {
        const int tu = biome == "test0" ? 0 : 1,
                  tv = 0;

        sf::Vertex* triangles = &decoration_vertices[i++ * 6];

        triangles[0].position = coordinates + decoration.offset + Vector2f{0, 0};
        triangles[1].position = coordinates + decoration.offset + Vector2f{1, 0};
        triangles[2].position = coordinates + decoration.offset + Vector2f{0, 1};
        triangles[3].position = coordinates + decoration.offset + Vector2f{0, 1};
        triangles[4].position = coordinates + decoration.offset + Vector2f{1, 0};
        triangles[5].position = coordinates + decoration.offset + Vector2f{1, 1};

        cout << "triangles:\n";
        for (char k = 0; k < 6; ++k)
            cout << '[' << k << "]: " << triangles[k].position.x << '\n';
        cout << '\n';

        triangles[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
        triangles[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        triangles[2].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        triangles[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        triangles[4].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        triangles[5].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    }

    return true;
}
