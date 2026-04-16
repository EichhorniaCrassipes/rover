#ifndef CHUNK
#define CHUNK

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

#include "mapGenerator.h"

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


namespace generator {
    class Chunk : public Drawable, public Transformable {
    public:
        Chunk(const MapGenerator &gen, int x, int y);
        ~Chunk() override = default;
    private:
        VertexArray vertices;
        sf::Vector2<int> position;
        Texture m_tileset;

        void draw(RenderTarget &target, RenderStates states) const override;
        bool load(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

        const sf::Vector2<int> size;

        static string get4tiles(const MapGenerator& gen, int x, int y);
    };
}


#endif
