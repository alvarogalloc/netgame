#include "AssetManager.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <exception>
#include <future>
#include <iostream>
#include <thread>

void close_game(std::integral auto code)
{
    std::cerr << "closing game with code " << code << '\n';
    exit(code);
}

void render_loop(sf::RenderWindow &window)
{

    sf::Event event;
    while (window.isOpen())
    {
        window.clear(sf::Color::Green);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.display();
    }
}

int main()
{
    using namespace std::literals;
    try
    {
        sf::RenderWindow window{{400, 800}, "Netgame"};
        window.setVerticalSyncEnabled(true);
        auto assets = netgame::AssetManager("assets");
        auto id = assets.load(netgame::AssetType::Music, "music.ogg");
        std::cout << assets.get<sf::Music>(id).id <<'\n';
        render_loop(window);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        close_game(1);
    }
}
