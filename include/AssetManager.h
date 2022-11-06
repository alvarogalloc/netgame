#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

namespace netgame {

enum class AssetType : uint8_t { Music, Texture };

template <typename T> struct Asset : T {
  constexpr Asset(std::size_t _id) { id = _id; }
  std::size_t id;
};

class AssetManager {
private:
  std::string m_asset_path{};
  std::size_t m_last_asset_id{0};
  std::vector<Asset<sf::Texture> *> m_textures{};
  std::vector<Asset<sf::Music> *> m_tracks{};

public:
  AssetManager(const std::string &assets_path) noexcept;
  ~AssetManager() noexcept = default;
  // returns id of loaded asset
  std::size_t load(AssetType type, std::string path);
  void unload(std::size_t id);
  template <typename T> Asset<T> *get(std::size_t id);
};
} // namespace netgame
