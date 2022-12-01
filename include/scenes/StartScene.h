#pragma once
#include "Animation.h"
#include "Game.h"
#include "Scene.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

namespace netgame {

class StartScene final : public netgame::Scene {

public:
  StartScene() {}
  void on_update(float delta) override;
  void on_event(sf::Event &ev) override;
  void on_render(sf::RenderTarget &gfx) override;
  std::unique_ptr<Scene> on_exit() override;
  ~StartScene();

private:
  void init(Game *game) override;
  std::vector<size_t> ids;
  netgame::AnimationDescription m_capy_walk_desc;
  netgame::Animation m_capy_walk;
  sf::Sprite m_bg_sprite;
  sf::Music *m_music;
  sf::Sprite m_play_button;
  bool is_blending_up {1};
  sf::Text m_title_text;

  //debug
  sf::Image snapshot;
};
} // namespace netgame
