#include "scenes/GameScene.h"

using namespace netgame;

void GameScene::init(Game *game) { m_assets = game->get_assets(); }
void GameScene::on_update(float delta) {}

void GameScene::on_event(sf::Event &ev) {}

void GameScene::on_render(sf::RenderTexture &gfx) {
  gfx.clear(sf::Color::Magenta);
}

std::unique_ptr<Scene> GameScene::on_exit() {
  return std::make_unique<GameScene>();
}
GameScene::~GameScene() {}
