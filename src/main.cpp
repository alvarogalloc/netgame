#include "Animation.h"
#include "AssetManager.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <exception>
#include <future>
#include <iostream>
#include <thread>

void close_game(std::integral auto code) {
  std::cerr << "closing game with code " << code << '\n';
  exit(code);
}

void render_loop(sf::RenderWindow &window, netgame::AssetManager *assets) {

  sf::Event event;

  netgame::AnimationDescription desc{
      .m_spritesheet = *assets->get<sf::Texture>(2),
      .m_cellsize{64, 64},
      .startpos{0, 64},
      .n_frames = 6,
      .curr_frame = 0,
      .duration = 800,
      .progress = 0,
  };

  netgame::Animation capy_animation(desc);

  sf::Clock deltaclock;
  while (window.isOpen()) {
    window.clear(sf::Color::Green);
    capy_animation.update(deltaclock.restart().asMilliseconds());
    window.draw(capy_animation.get_sprite());
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.display();
  }
}

int main() {
  using namespace std::literals;
  try {
    sf::RenderWindow window{{400, 800}, "Netgame"};
    window.setVerticalSyncEnabled(true);
    auto assets = new netgame::AssetManager("assets");
    auto id = assets->load(netgame::AssetType::Music, "music.ogg");
    auto img_id = assets->load(netgame::AssetType::Texture, "capybara.png");
    render_loop(window, assets);
    delete assets;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    close_game(1);
  }
}
