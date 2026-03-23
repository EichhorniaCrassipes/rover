#include "engine/engine.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "objects/object.h"


int main() {
    const game::Engine engine;
    engine.run();
    return 0;
}
