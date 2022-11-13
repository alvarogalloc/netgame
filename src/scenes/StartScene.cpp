#include "AssetManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <iostream>
#include <scenes/StartScene.h>

using namespace netgame;

// called when changing scenes
void StartScene::init(Game *game) {
  m_assets = game->get_assets();
  auto music_id = m_assets->load(AssetType::Music, "music.ogg");
  auto bg_id = m_assets->load(AssetType::Texture, "bg.png");
  auto play_button_id = m_assets->load(AssetType::Texture, "btns.png");
  auto font_id = m_assets->load(AssetType::Font, "BitPotion.ttf");
  auto capy_id = m_assets->load(AssetType::Texture, "capybara.png");
  ids.insert(ids.end(), {music_id, bg_id, play_button_id, font_id, capy_id});
  m_music =m_assets->get<sf::Music>(music_id);
  m_music->play();

  m_bg_sprite.setTexture(*m_assets->get<sf::Texture>(bg_id));
  m_play_button.setTexture(*m_assets->get<sf::Texture>(play_button_id));

  // from (0,0) grab a 26x17 chunk of pixels
  m_play_button.setTextureRect({0, 0, 26, 17});
  // scale in x and y by 4
  m_play_button.setScale({4.f, 4.f});
  m_play_button.setOrigin(m_play_button.getTextureRect().width / 2.f,
                          m_play_button.getTextureRect().height / 2.f);
  m_play_button.setPosition({game->get_dimensions().width / 2.f,
                             game->get_dimensions().height / 2.f});

  // scale to fit window
  m_bg_sprite.setScale({float(game->get_dimensions().height) /
                            m_bg_sprite.getTexture()->getSize().x,
                        float(game->get_dimensions().height) /
                            m_bg_sprite.getTexture()->getSize().y});

  // init Title text
  m_title_text.setFont(*m_assets->get<sf::Font>(font_id));
  m_title_text.setString("Capybaras");
  m_title_text.setPosition({game->get_dimensions().width / 2.f, 50.f});
  m_title_text.setCharacterSize(120);
  m_title_text.setFillColor({229, 228, 226});
  m_title_text.setOrigin(m_title_text.getLocalBounds().width / 2.f,
                         m_title_text.getLocalBounds().height / 2.f);

  // lastly set capy
  m_capy_walk_desc.m_spritesheet = m_assets->get<sf::Texture>(capy_id);
  m_capy_walk_desc.m_cellsize = {64, 64};
  m_capy_walk_desc.startpos = {0, 64 * 8};
  m_capy_walk_desc.n_frames = 8;
  m_capy_walk_desc.duration = 1200;
  m_capy_walk = Animation(m_capy_walk_desc);
  m_capy_walk.get_sprite().setScale(3, 3);

  m_capy_walk.get_sprite().setPosition({game->get_dimensions().width / 2.f - 64,
                                        game->get_dimensions().height / 2.f});
}
void StartScene::on_update(float delta) {
  // must pass as milliseconds
  m_capy_walk.update(delta * 1000);
  // little trick for the text to blend
  if (m_title_text.getFillColor().a <= 2) {
    is_blending_up = true;
  } else if (m_title_text.getFillColor().a >= 253) {
    is_blending_up = false;
  }
  if (is_blending_up) {
    m_title_text.setFillColor(sf::Color(
        m_title_text.getFillColor().r, m_title_text.getFillColor().g,
        m_title_text.getFillColor().b, m_title_text.getFillColor().a + 3));
  } else {
    m_title_text.setFillColor(sf::Color(
        m_title_text.getFillColor().r, m_title_text.getFillColor().g,
        m_title_text.getFillColor().b, m_title_text.getFillColor().a - 3));
  }
}

void StartScene::on_event(sf::Event &ev) {
  switch (ev.type) {
  case sf::Event::MouseButtonPressed:
    if (m_play_button.getGlobalBounds().contains(ev.mouseButton.x,
                                                 ev.mouseButton.y)) {
      m_play_button.setTextureRect({26, 0, 26, 17});
      // reset origin
      m_play_button.setOrigin(m_play_button.getTextureRect().width / 2.f,
                              m_play_button.getTextureRect().height / 2.f);
    }
    break;
  case sf::Event::MouseButtonReleased:
    // exit if release mouse inside button
    if (m_play_button.getGlobalBounds().contains(ev.mouseButton.x,
                                                 ev.mouseButton.y)) {
      exit = true;
    }
    m_play_button.setTextureRect({0, 0, 26, 17});
    m_play_button.setOrigin(m_play_button.getTextureRect().width / 2.f,
                            m_play_button.getTextureRect().height / 2.f);
    break;
  default:

    break;
  }
}

void StartScene::on_render(sf::RenderTexture &gfx) {
  gfx.clear(sf::Color::Green);
  gfx.draw(m_bg_sprite);
  gfx.draw(m_play_button);
  gfx.draw(m_title_text);
  gfx.draw(m_capy_walk.get_sprite());
}

std::unique_ptr<Scene> StartScene::on_exit() {
  m_music->stop();
  for (auto &id : ids) {
    m_assets->unload(id);
  }
  return std::make_unique<StartScene>();
}
StartScene::~StartScene() {}
