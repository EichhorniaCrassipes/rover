#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

using sf::RenderWindow;
using sf::Text;
using sf::Font;
using sf::VideoMode;
using sf::Vector2f;
using std::to_string;
using std::string;

int main() {
    unsigned long long frames_counter = 0, ticks_counter = 0;

    RenderWindow window(
        VideoMode({1280, 720}),
        "SFML-built-test"
    );
    window.setVerticalSyncEnabled(true);

    Font font;
    if (!font.openFromFile("fonts/Kuro Regular.otf")) return 1;

    Text frames(font);
    frames.setCharacterSize(50);
    frames.setPosition(Vector2f{1280 / 3, 720 / 3});
    Text ticks(font);
    ticks.setCharacterSize(50);
    ticks.setPosition(Vector2f{1280 / 3, 720 * 2 / 3});

    sf::Clock ticker;
    ticker.restart();
    const unsigned tick_delta_abs = 69;
    const double tick_delta = 1. / tick_delta_abs;
    double last_5s_ticks = 0;
    unsigned last_5s_ticks_counter = 0;
    sf::Clock tick_5s;
    tick_5s.restart();
    string tick_5s_status_string = "counting...";

    sf::Clock framer;
    framer.restart();
    double last_framer_value = 0, last_ticker_value = 0;
    double last_5s_frames = 0;
    unsigned last_5s_frames_counter = 0;
    sf::Clock frame_5s;
    frame_5s.restart();
    string frame_5s_status_string = "counting...";

    while (window.isOpen()) {
        while (const auto event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();

        window.clear();

        const auto framer_current_value = framer.getElapsedTime().asSeconds();
        double framer_display = 1 / (framer_current_value - last_framer_value);
        last_5s_frames += framer_display;
        last_5s_frames_counter++;
        frames.setString(to_string(frames_counter) + "; " + to_string(static_cast<int>(framer_display)) + "; " + frame_5s_status_string);
        last_framer_value = framer_current_value;

        auto ticker_current_value = ticker.getElapsedTime().asSeconds();
        /*
        if (ticker_current_value - last_ticker_value > tick_delta) {
        */
        if ((ticker_current_value - last_ticker_value) * tick_delta_abs >= 1) {
            double ticker_display = 1 / (ticker_current_value - last_ticker_value);
            last_5s_ticks += ticker_display;
            last_5s_ticks_counter++;
            ticks.setString(to_string(ticks_counter) + "; " + to_string(static_cast<int>(ticker_display)) + "; " + tick_5s_status_string);
            last_ticker_value = ticker_current_value;
            ticks_counter++;
        }

        if (tick_5s.getElapsedTime().asSeconds() >= 2) {
            tick_5s.restart();
            tick_5s_status_string = to_string(static_cast<int>(last_5s_ticks / last_5s_ticks_counter));
            last_5s_ticks_counter = 0;
            last_5s_ticks         = 0;
        }
        if (frame_5s.getElapsedTime().asSeconds() >= 2) {
            frame_5s.restart();
            frame_5s_status_string = to_string(static_cast<int>(last_5s_frames / last_5s_frames_counter));
            last_5s_frames_counter = 0;
            last_5s_frames         = 0;
        }

        window.draw(frames);
        window.draw(ticks);

        window.display();
        frames_counter++;
    }
    return 0;
}