#include "scenes/GameScene.h"
#include "scenes/StartScene.h"
#include <iostream>
#include <thread>

using namespace netgame;

void GameScene::init(Game *game) {
  // m_name = "Main Scene";
  m_assets = game->get_assets();
  std::this_thread::sleep_for(std::chrono::milliseconds(40));
}
void GameScene::on_update(float delta) {
  std::cout << "hola\n";
}

void GameScene::on_event(sf::Event &ev) {
  if (ev.key.code == sf::Keyboard::Space) {
    exit = true;
  }
}

void GameScene::on_render(sf::RenderTarget &gfx) {
  gfx.clear(sf::Color::Magenta);
    // snapshot = gfx.getTexture().copyToImage();

}

std::unique_ptr<Scene> GameScene::on_exit() {
  // snapshot.saveToFile("Gamescene.png");
  return std::make_unique<StartScene>();
}
GameScene::~GameScene() {}
