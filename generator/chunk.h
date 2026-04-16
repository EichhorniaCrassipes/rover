#ifndef CHUNK
#define CHUNK

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

#include "mapGenerator.h"

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


namespace generator {
    class Chunk : public Drawable, public Transformable {
    public:
        Chunk(MapGenerator* generator_link, int x, int y);
        ~Chunk() override;
    private:
        MapGenerator* generator;
        VertexArray vertices;
        Vector2i position;
        Texture m_tileset;

        void draw(RenderTarget &target, RenderStates states) const override;
        bool load_tiles(const string &tile_path, Vector2u tileSize, const int* tiles, const unsigned char* var, unsigned int width, unsigned int height);
        void load_decorations(const string &tile_path, Vector2u tileSize, const int* tiles);

        const sf::Vector2<int> size;

        vector<pair<Vector2f, TileDecoration>> decorations_raw;
        vector<Drawable*> decorations;

        string get4tiles(int x, int y) const;
    };
}


#endif
