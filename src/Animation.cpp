#include "Animation.h"
#include <iostream>

using namespace netgame;

Animation::Animation(AnimationDescription description)
    : m_description(description) {
  m_sprite.setTexture(m_description.m_spritesheet);
}

// TODO: add support for rows and columns and different directions
void Animation::update(sf::Int32 delta) {
  auto frame_duration = m_description.duration / m_description.n_frames;
  m_description.progress += delta;

  // if the animation finished, reset it
  if (m_description.progress >= m_description.duration) {
    m_description.progress = 0;
    m_description.curr_frame = 0;
    m_sprite.setTextureRect({m_description.startpos.x, m_description.startpos.y,
                             m_description.m_cellsize.x,
                             m_description.m_cellsize.y});
    return;
  }

  // if there is a step
  if (m_description.progress >= frame_duration * m_description.curr_frame) {
    m_sprite.setTextureRect(
        {m_description.startpos.x +
             (m_description.m_cellsize.x * ++m_description.curr_frame),
         m_description.startpos.y, m_description.m_cellsize.x, m_description.m_cellsize.y});
  }
}

sf::Sprite &Animation::get_sprite() { return m_sprite; }
