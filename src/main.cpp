#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <thread>

std::tuple<sf::Image *, sf::Music *> loadAssets() {
  sf::Image *img = new sf::Image;
  sf::Music *music = new sf::Music;
  // asynchronously load all assets
  auto music_promise = std::async(std::launch::async, &sf::Music::openFromFile,
                                  music, "assets/music.ogg");
  auto img_promise = std::async(std::launch::async, &sf::Image::loadFromFile,
                                img, "assets/capybara.png");
  music_promise.get();
  img_promise.get();
  return std::make_tuple(std::move(img), std::move(music));
}

void render_loop(sf::RenderWindow &window) {

  sf::Event event;
  while (window.isOpen()) {
    window.clear(sf::Color::Green);
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.display();
  }
}
int main() {
  sf::RenderWindow window{{400, 800}, "Netgame"};
  window.setVerticalSyncEnabled(true);
  auto [img, music] = loadAssets();
  render_loop(window);
}
