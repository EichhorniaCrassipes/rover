#ifndef CHUNK
#define CHUNK

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

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
    class Chunk : public Drawable, public Transformable {
    public:
        Chunk(MapGenerator* generator_link, int x, int y);
    private:
        MapGenerator* generator;

        VertexArray tile_vertices;
        Vector2i position;
        Texture m_tileset;

        const sf::Vector2<int> size;

        void draw(RenderTarget &target, RenderStates states) const override;
        bool load(const string &tile_path, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

        string get4tiles(int x, int y) const;
    };
}


#endif
