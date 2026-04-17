#ifndef CHUNK_DECORATIONS
#define CHUNK_DECORATIONS

#include "mapGenerator.h"

#include <vector>
using std::vector;
using std::pair;

#include <string>
using std::string;

#include "SFML/Graphics/Drawable.hpp"
using sf::Drawable;

#include "SFML/Graphics/Texture.hpp"
using sf::Texture;

#include "SFML/Graphics/Transformable.hpp"
using sf::Transformable;

#include "SFML/Graphics/VertexArray.hpp"
using sf::VertexArray;
using sf::RenderStates;
using sf::RenderTarget;

#include <SFML/System/Vector2.hpp>
using sf::Vector2u;
using sf::Vector2i;


namespace generator {
    struct ChunkDecorationsDecorationInfo {
        string biome;
        TileDecoration decoration;
        Vector2f global_coordinates;
    };

    class ChunkDecorations : public Drawable, public Transformable {
    public:
        ChunkDecorations(MapGenerator* generator_link, int x, int y, Texture* texture);
    private:
        MapGenerator* generator;

        VertexArray decoration_vertices;
        Vector2i position;
        Texture* m_decorations;

        const sf::Vector2<int> size;

        void draw(RenderTarget &target, RenderStates states) const override;
        void load( Vector2u tileSize);

        vector<ChunkDecorationsDecorationInfo> decorations;
    };
}


#endif
