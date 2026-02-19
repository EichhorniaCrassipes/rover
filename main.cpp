#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using sf::RenderWindow;
using sf::Text;
using sf::Font;
using sf::VideoMode;
using sf::Vector2f;
using std::to_string;

int main() {
    unsigned long long frames = 0;

    RenderWindow window(
        VideoMode({1280, 720}),
        "SFML-built-test"
    );
    window.setFramerateLimit(24);

    Font font;
    if (!font.openFromFile("fonts/Kuro Regular.otf")) return 1;

    Text frames_text(font);
    frames_text.setCharacterSize(50);
    frames_text.setPosition(Vector2f{615, 355});

    while (window.isOpen()) {
        while (const auto event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();

        window.clear();

        frames_text.setString(to_string(frames));
        window.draw(frames_text);

        window.display();
        frames++;
    }
    return 0;
}