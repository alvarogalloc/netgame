#include "Game.h"
#include "AssetManager.h"
#include "Scene.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>

using namespace netgame;

Game::Game(std::string_view game_name) noexcept
    : m_game_name(game_name), m_dimesions(sf::VideoMode{600, 600}) {

  {

    // auto start = std::chrono::steady_clock::now();
    // m_window->setVerticalSyncEnabled(true);
    // auto delta = std::chrono::steady_clock::now() - start;

// #if !defined(NDEBUG)
//     std::cout << "[Game] Window initialized in " << 400
//               << " milliseconds\n";
// #endif
  }

  // nothing to benchmark here
  m_assets = std::make_unique<AssetManager>("assets");
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
    auto start = std::chrono::steady_clock::now();
    m_current_scene->init(this);
#if !defined(NDEBUG)
    std::cout << "["
              << "Scene"
              << "] Assets initialized in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::steady_clock::now() - start)
                     .count()
              << " milliseconds \n";
#endif
  }
}

void Game::update() {
  if (m_current_scene->exit) {
    set_scene(m_current_scene->on_exit());
    return;
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
  m_window->clear();
  m_current_scene->on_render(*m_window);
  m_window->display();
}
