#ifndef CHUNK
#define CHUNK

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

#include "../mapGenerator.h"

#include <vector>
using std::vector;
using std::pair;

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
using sf::Vector2;


namespace generator {
    class Chunk : public Drawable, public Transformable {
    public:
        Chunk(MapGenerator* generator_link, long long x, long long y, Texture* texture);
        Vector2<long long> getAbsolutePosition() const;
    private:
        MapGenerator* generator;
        VertexArray vertices;
        Vector2<long long> position;
        Texture* m_tileset;

        void draw(RenderTarget &target, RenderStates states) const override;
        void load(Vector2u tileSize, const int* tiles, const unsigned char* var, unsigned int width, unsigned int height);

        const Vector2i size{CHUNK_WIDTH, CHUNK_HEIGHT};

        static string get4tiles(const Tile &tile0, const Tile &tile1, const Tile &tile2, const Tile &tile3) ;
    };
}


#endif
