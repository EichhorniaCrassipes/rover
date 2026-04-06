#ifndef ROVER_CHUNK_H
#define ROVER_CHUNK_H
#include <filesystem>

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "../object.h"

class Chunk : public sf::Drawable, public sf::Transformable
{
public:
   Chunk();
   ~Chunk() override;
private:
   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
   sf::VertexArray vertices;
   sf::Vector2<int> position;
   sf::Texture m_tileset;

   bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
};


#endif //ROVER_CHUNK_H