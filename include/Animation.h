#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace netgame {
struct AnimationDescription {
  sf::Texture &m_spritesheet;
  sf::Vector2i m_cellsize;
  sf::Vector2i startpos;
  uint8_t n_frames;
  uint8_t curr_frame;
  float duration;
  float progress;
};
class Animation {
private:
  AnimationDescription m_description;
  sf::Sprite m_sprite;


public:
  Animation(AnimationDescription description);
  void update(sf::Int32 delta);
  sf::Sprite & get_sprite();
  ~Animation() = default;
};
} // namespace netgame
