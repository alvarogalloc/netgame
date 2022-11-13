#include "Game.h"
#include "AssetManager.h"
#include "Scene.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <iostream>
#include <memory>

using namespace netgame;

Game::Game(std::string_view game_name) noexcept
    : m_game_name(game_name), m_dimesions(sf::VideoMode{600, 600}) {

  {

    sf::Clock delay;
    m_window = std::make_unique<sf::RenderWindow>(m_dimesions, m_game_name,
                                                  sf::Style::Default);
    m_window->setFramerateLimit(60);

#if !defined(NDEBUG)
    std::cout << "[Game] Window initialized in " << delay.restart().asSeconds()
              << " seconds\n";
#endif
  }

  // nothing to benchmark here
  m_assets = std::make_unique<AssetManager>("assets");

  // bind renderer to renderer sprite
  m_renderer.create(m_dimesions.width, m_dimesions.height);
  m_renderer_sprite.setTexture(m_renderer.getTexture());
}
sf::VideoMode Game::get_dimensions() const { return m_dimesions; }
AssetManager *Game::get_assets() const { return m_assets.get(); }

bool Game::running() const {
  // if window is open and there is a scene playing
  return m_window->isOpen() && m_current_scene != nullptr;
}

void Game::set_scene(ptr<Scene> scene) {
  m_current_scene = std::move(scene);
  {
    sf::Clock delay;
    m_current_scene->init(this);
#if !defined(NDEBUG)
    std::cout << "[Scene] Assets initialized in " << delay.restart().asSeconds()
              << " seconds \n";
#endif
  }
}

void Game::update() {
  if (m_current_scene->exit) {
    set_scene(m_current_scene->on_exit());
  }
  while (m_window->pollEvent(m_ev)) {
    if (m_ev.type == sf::Event::Closed) {
      m_window->close();
    }
    m_current_scene->on_event(m_ev);
  }
  m_current_scene->on_update(m_clock.restart().asSeconds());
}
void Game::render() {
  m_current_scene->on_render(m_renderer);
  m_window->clear();
  // needed
  m_renderer.display();

  m_window->draw(m_renderer_sprite);
  m_window->display();
}
