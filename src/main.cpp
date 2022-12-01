#include "Animation.h"
#include "AssetManager.h"
#include "Game.h"
#include "scenes/GameScene.h"
#include "scenes/StartScene.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <exception>
#include <future>
#include <iostream>
#include <thread>

// void close_game(std::integral auto code) {
//   std::cerr << "closing game with code " << code << '\n';
//   exit(code);
// }
//
// void render_loop(sf::RenderWindow &window, netgame::AssetManager *assets) {
//
//   sf::Event event;
//
//   netgame::AnimationDescription idle_anim_desc{
//       .m_spritesheet = *assets->get<sf::Texture>(2),
//       .m_cellsize{64, 64},
//       .startpos{0, 64},
//       .n_frames = 8,
//       .curr_frame = 0,
//       .duration = 400,
//       .progress = 0,
//   };
//   netgame::AnimationDescription walk_anim_desc{
//       .m_spritesheet = *assets->get<sf::Texture>(2),
//       .m_cellsize{64, 64},
//       .startpos{0, 64 * 8},
//       .n_frames = 8,
//       .duration = 800,
//   };
//
//   // netgame::Animation idle_capy_animation(idle_anim_desc);
//   netgame::Animation walk_capy_animation(walk_anim_desc);
//   // idle_capy_animation.get_sprite().setScale({4, 4});
//   walk_capy_animation.get_sprite().setScale({4, 4});
//
//   sf::Clock deltaclock;
//   while (window.isOpen()) {
//     window.clear(sf::Color::Green);
//     walk_capy_animation.update(deltaclock.restart().asMilliseconds());
//     // window.draw(idle_capy_animation.get_sprite());
//     window.draw(walk_capy_animation.get_sprite());
//     while (window.pollEvent(event)) {
//       if (event.type == sf::Event::Closed)
//         window.close();
//       if (event.type == sf::Event::EventType::KeyPressed)
//       {
//
//       }
//     }
//
//     window.display();
//   }
// }
//
// int main() {
//   using namespace std::literals;
//   try {
//     sf::RenderWindow window{{400, 800}, "Netgame"};
//     window.setVerticalSyncEnabled(true);
//     auto assets = new netgame::AssetManager("assets");
//     auto id = assets->load(netgame::AssetType::Music, "music.ogg");
//     auto img_id = assets->load(netgame::AssetType::Texture, "capybara.png");
//     render_loop(window, assets);
//     delete assets;
//   } catch (const std::exception &e) {
//     std::cerr << e.what() << '\n';
//     close_game(1);
//   }
// }

int main() {
  netgame::Game game("capy");
  game.set_scene(std::make_unique<netgame::GameScene>());
  while (game.running()) {
    game.update();
    game.render();
  }
}
