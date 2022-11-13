#pragma once
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

namespace netgame {
// fwd declaration
class Game;
class AssetManager;
class Scene {
public:
  virtual void on_update(float delta) = 0;
  virtual void on_render(sf::RenderTexture &gfx) = 0;
  virtual void on_event(sf::Event &ev) = 0;
  virtual std::unique_ptr<Scene> on_exit() = 0;
  // sf::VideoMode get_window_dimensions() {return};
  // [[deprecated("Use the Render Texture overload, its better!")]] virtual void
  // on_render(sf::RenderWindow &window) = 0;
  virtual ~Scene() noexcept = default;
  friend class Game;

protected:
  Scene() noexcept {}

  // TODO: add a simpler way to share data with Game class
  // for now just initialize them when calling init()
  AssetManager *m_assets;
  bool exit;

private:
  virtual void init(Game *game){};
};

} // namespace netgame
