#pragma once
#include "Animation.h"
#include "Game.h"
#include "Scene.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

namespace netgame {

class GameScene final : public netgame::Scene {

public:
  GameScene() {}
  void on_update(float delta) override;
  void on_event(sf::Event &ev) override;
  void on_render(sf::RenderTarget &gfx) override;
  std::unique_ptr<Scene> on_exit() override;
  ~GameScene();

private:
  void init(Game *game) override;
    //debug
  sf::Image snapshot;

};
}
