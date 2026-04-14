#ifndef ROVER_CHUNK_H
#define ROVER_CHUNK_H
#include <filesystem>

#include "../../generator/mapGenerator.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

class Chunk : public sf::Drawable, public sf::Transformable
{
public:
   Chunk(const generator::MapGenerator &gen, int x, int y);
   ~Chunk() override;
private:
   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
   sf::VertexArray vertices;
   sf::Vector2<int> position;
   sf::Texture m_tileset;
   const sf::Vector2<int> size;

   bool load( sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
};


#endif //ROVER_CHUNK_H