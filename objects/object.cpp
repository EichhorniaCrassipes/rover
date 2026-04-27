#include "object.h"

#include "../engine/libraries.h"

#include "SFML/Graphics/RenderTarget.hpp"


object::Object::Object(const string &index, const Vector2i &sprite_size) : texture(game::TEXTURE_LIBRARY[index]), sprite(texture) {
    this->sprite_size = sprite_size;
    this->index = index;
    sprite.setTextureRect({{0, 0}, sprite_size});

    scale = {1, 1};
    position = {0, 0};
}


Sprite object::Object::getSprite() const { return sprite; }
Vector2f object::Object::getPosition() const { return position; }
string object::Object::getLibraryIndex() const { return index; }

void object::Object::setPosition(const Vector2f new_position) {
    position = new_position;
    sprite.setPosition(position);
}
void object::Object::setScale(const Vector2f new_scale) {
    scale = new_scale;
    sprite.setScale(scale);
}

void object::Object::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    states.transform.translate(position);
    states.transform.scale(scale);
    states.texture = &texture;
    target.draw(sprite, states);
}
