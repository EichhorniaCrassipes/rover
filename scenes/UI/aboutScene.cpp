#include "aboutScene.h"

#include <iostream>
using std::cout;

#include "../../engine/enums.h"
#include "../../engine/libraries.h"


scene::AboutScene::AboutScene(RenderWindow* window_link, EngineStats* scene_index_link)
    : UIScene(window_link, scene_index_link),
      title(nullptr), hint(nullptr), description(nullptr),
      github_qr(nullptr), itch_qr(nullptr),
      github_caption(nullptr), itch_caption(nullptr)
{
    if (!background_texture.loadFromFile("image/menu9_2.jpg"))
        cout << "[AboutScene] error loading texture image/menu9_2.jpg" << std::endl;
    background.setTexture(&background_texture);
    background.setSize({static_cast<float>(engine_stats->window_width),
                        static_cast<float>(engine_stats->window_height)});

    if (!font.openFromFile("fonts/OCR A Extended Regular.ttf"))
        cout << "[AboutScene] error loading font" << std::endl;

    if (!github_qr_texture.loadFromFile("image/repo_qr.png"))
        cout << "[AboutScene] error loading image/repo_qr.png" << std::endl;

    if (!itch_qr_texture.loadFromFile("image/itch_qr.png"))
        cout << "[AboutScene] error loading image/itch_qr.png" << std::endl;
}

scene::AboutScene::~AboutScene()
{
    delete title;
    delete hint;
    delete description;
    delete github_qr;
    delete itch_qr;
    delete github_caption;
    delete itch_caption;
}

void scene::AboutScene::on_start()
{
    initText();
    initQRCodes();
    initDescription();
}

void scene::AboutScene::initText()
{
    delete title;
    title = new Text(font, L"About", 150);
    title->setFillColor(sf::Color(237, 147, 0));
    title->setOutlineThickness(3);
    title->setOutlineColor(sf::Color::Black);
    const auto title_bounds = title->getLocalBounds();
    title->setPosition({
        (static_cast<float>(engine_stats->window_width)  - title_bounds.size.x) / 2.f,
        static_cast<float>(engine_stats->window_height) * 0.05f
    });

    delete hint;
    hint = new Text(font, L"Press [Escape] to go back", 40);
    hint->setFillColor(sf::Color(200, 200, 200, 180));
    hint->setOutlineThickness(1);
    hint->setOutlineColor(sf::Color::Black);
    const auto hint_bounds = hint->getLocalBounds();
    hint->setPosition({
        (static_cast<float>(engine_stats->window_width) - hint_bounds.size.x) / 2.f,
        static_cast<float>(engine_stats->window_height) * 0.92f
    });
}

void scene::AboutScene::initQRCodes()
{
    const float w        = static_cast<float>(engine_stats->window_width);
    const float h        = static_cast<float>(engine_stats->window_height);
    const float qr_size  = h * 0.30f;
    const float margin   = w * 0.05f;   // distance from screen edge to QR
    const float cap_gap  = h * 0.018f;  // gap between QR bottom and caption top
    const unsigned caption_size = static_cast<unsigned>(h * 0.036f);
    const float qr_y    = h * 0.32f;

    delete github_qr;
    github_qr = new Sprite(github_qr_texture);
    {
        const auto sz = github_qr_texture.getSize();
        const float scale = qr_size / static_cast<float>(sz.x);
        github_qr->setScale({scale, scale});
    }
    github_qr->setPosition({margin, qr_y});

    delete github_caption;
    github_caption = new Text(font, "Visit our GitHub repo", caption_size);
    github_caption->setFillColor(sf::Color::White);
    github_caption->setOutlineThickness(1);
    github_caption->setOutlineColor(sf::Color::Black);
    {
        const auto cap = github_caption->getLocalBounds();
        github_caption->setPosition({
            margin + (qr_size - cap.size.x) / 2.f - cap.position.x,
            qr_y + qr_size + cap_gap
        });
    }

    delete itch_qr;
    itch_qr = new Sprite(itch_qr_texture);
    {
        const auto sz = itch_qr_texture.getSize();
        const float scale = qr_size / static_cast<float>(sz.x);
        itch_qr->setScale({scale, scale});
    }
    const float itch_qr_x = w - margin - qr_size;
    itch_qr->setPosition({itch_qr_x, qr_y});

    delete itch_caption;
    itch_caption = new Text(font, "Visit also our itch page", caption_size);
    itch_caption->setFillColor(sf::Color::White);
    itch_caption->setOutlineThickness(1);
    itch_caption->setOutlineColor(sf::Color::Black);
    {
        const auto cap = itch_caption->getLocalBounds();
        itch_caption->setPosition({
            itch_qr_x + (qr_size - cap.size.x) / 2.f - cap.position.x - 50,
            qr_y + qr_size + cap_gap
        });
    }
}

void scene::AboutScene::initDescription()
{
    const float w = static_cast<float>(engine_stats->window_width);
    const float h = static_cast<float>(engine_stats->window_height);
    const unsigned desc_size = static_cast<unsigned>(h * 0.034f);
    const float qr_y    = h * 0.32f;
    const float qr_size = h * 0.30f;

    delete description;
    description = new Text(font,
        "[ Controls ]\n\n"
        "Movement:   WASD / Arrow Keys\n"
        "Map zoom:   Mouse scroll\n"
        "Inventory:  Keys 1-5",
        desc_size);
    description->setFillColor(sf::Color::White);
    description->setOutlineThickness(1);
    description->setOutlineColor(sf::Color::Black);

    const auto b = description->getLocalBounds();
    description->setPosition({
        (w - b.size.x) / 2.f - b.position.x,
        qr_y + (qr_size - b.size.y) / 2.f - b.position.y
    });
}

void scene::AboutScene::render()
{
    sf::RenderStates states;
    if (game::SHADER_LIBRARY.count("darken"))
        states.shader = &game::SHADER_LIBRARY.at("darken");
    window->draw(background, states);
    if (title)          window->draw(*title);
    if (hint)           window->draw(*hint);
    if (github_qr)      window->draw(*github_qr);
    if (github_caption) window->draw(*github_caption);
    if (itch_qr)        window->draw(*itch_qr);
    if (itch_caption)   window->draw(*itch_caption);
    if (description)    window->draw(*description);
}

void scene::AboutScene::update() {}

scene::Status scene::AboutScene::event(const Event& event)
{
    if (event.is<sf::Event::KeyReleased>()) {
        const auto* key = event.getIf<sf::Event::KeyReleased>();
        if (!key) return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};

        if (key->scancode == sf::Keyboard::Scancode::Escape)
            return {true, game::DO_NOT_UPDATE_SCENE, game::UI_scenes::MENU};
    }
    return {false, game::DO_NOT_UPDATE_SCENE, game::DO_NOT_UPDATE_SCENE};
}
