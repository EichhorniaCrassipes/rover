#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <unordered_map>

using sf::RenderWindow;
using sf::Text;
using sf::Font;
using sf::VideoMode;
using sf::Vector2f;
using std::to_string;
using std::string;
using std::unordered_map;

int main() {
    unsigned long long frames = 0;

    RenderWindow window(
        VideoMode({1280, 720}),
        "SFML-built-test"
    );
    window.setFramerateLimit(24);

    auto clock = sf::Clock();
    clock.restart();

    Font font;
    if (!font.openFromFile("fonts/Kuro Regular.otf")) return 1;

    float x_coordinate = 615;
    float y_coordinate = 355;

    unordered_map<int, string> achievements;
    achievements[67] = "67 number achieved";
    achievements[69] = "69 number achieved";
    achievements[228] = "228 number achieved";
    achievements[1488] = "1488 number achieved";
    string ach_text;

    unordered_map<int, bool> flag;
    flag[67] = false;
    flag[69] = false;
    flag[228] = false;
    flag[1488] = false;

    Text frames_text(font);
    frames_text.setCharacterSize(50);
    frames_text.setPosition(Vector2f{x_coordinate, y_coordinate});

    frames_text.setFillColor(sf::Color::White);

    Text achievement_text(font);
    achievement_text.setCharacterSize(25);
    achievement_text.setFillColor(sf::Color::Black);
    achievement_text.setOutlineThickness(0);
    achievement_text.setOutlineColor(sf::Color::Cyan);
    achievement_text.setOutlineThickness(2);

    Text instruction_text(font);
    instruction_text.setCharacterSize(25);
    instruction_text.setString("WASD to move \nSpace to return default coords \nP to catch \nEscape to close");
    achievement_text.setPosition(Vector2f{900, 5});

    float delta_t = 1;

    while (window.isOpen()) {
        if (clock.getElapsedTime().asSeconds() >= 1/24)
        {
            delta_t = clock.getElapsedTime().asSeconds();
            clock.restart();
        }
        achievement_text.setString(ach_text);
        while (const auto event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                x_coordinate += delta_t*30.5f;
                frames_text.setPosition(Vector2f{x_coordinate, y_coordinate});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                y_coordinate -= delta_t*30.5f;
                frames_text.setPosition(Vector2f{x_coordinate, y_coordinate});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                x_coordinate -= delta_t*30.5f;
                frames_text.setPosition(Vector2f{x_coordinate, y_coordinate});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                y_coordinate += delta_t*30.5f;
                frames_text.setPosition(Vector2f{x_coordinate, y_coordinate});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                y_coordinate = 355;
                x_coordinate = 615;
                frames_text.setPosition(Vector2f{x_coordinate, y_coordinate});
            }


        window.clear();


        window.draw(instruction_text);
        window.draw(achievement_text);
        frames_text.setString(to_string(frames));
        window.draw(frames_text);

        window.display();
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        {
            frames++;
        }
        else
        {
            for (const auto& achievement : achievements)
            {
                if (frames == achievement.first)
                {
                    for (auto& flg : flag)
                    {
                        if (achievement.first == flg.first && !flg.second)
                        {
                            flg.second = true;
                            ach_text += achievement.second + "\n";
                        }
                    }
                }
            }
        }

    }
    return 0;
}