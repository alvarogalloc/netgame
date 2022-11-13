#pragma once
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <ginseng/ginseng.hpp>
#include <memory>
#include <string>
#include "Scene.h"
namespace netgame {
template <typename T> using ptr = std::unique_ptr<T>;

// fwd declarations
class AssetManager;
class Game {
public:
  using database = ginseng::database;
  using ent_id = database::ent_id;
  using com_id = database::com_id;

  Game(std::string_view game_name) noexcept;
  sf::VideoMode get_dimensions() const;
  AssetManager* get_assets() const;
  bool running() const;
  void set_scene(ptr<Scene> scene);
  void update();
  void render();
  ~Game() noexcept = default;

private:
  std::string m_game_name;
  ptr<Scene> m_current_scene;
  ptr<AssetManager> m_assets;
  ptr<sf::RenderWindow> m_window;
  sf::Event m_ev;
  sf::RenderTexture m_renderer;
  sf::Sprite m_renderer_sprite;
  sf::VideoMode m_dimesions;
  sf::Clock m_clock;
};
} // namespace netgame
