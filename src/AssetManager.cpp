#include "AssetManager.h"

using namespace netgame;

AssetManager::AssetManager(const std::string &assets_path) noexcept {
  // append '/' if not provided
  if (!assets_path.ends_with('/')) {
    m_asset_path = assets_path + '/';
  }
}

std::size_t AssetManager::load(AssetType type, std::string path) {

  // Remove path clash with m_asset_path
  if (path.starts_with('/')) {
    path.erase(0);
  }
  auto filepath = m_asset_path + path;

  switch (type) {
  case AssetType::Music: {
    m_tracks.push_back(new Asset<sf::Music>{++m_last_asset_id});
    if (!m_tracks.back()->openFromFile(filepath)) {
      throw std::runtime_error{"Error loading Track: " + filepath};
    }
    break;
  }
  case AssetType::Texture: {
    m_textures.push_back(new Asset<sf::Texture>{++m_last_asset_id});
    if (!m_textures.back()->loadFromFile(filepath)) {
      throw std::runtime_error{"Error loading Image: " + filepath};
    }
    break;
  }
  }
  return m_last_asset_id;
}

void AssetManager::unload(std::size_t id) {
  auto id_match = [id](const auto &asset) { return asset->id == id; };
  {
    auto res = std::find_if(m_textures.begin(), m_textures.end(), id_match);
    if (res != m_textures.end())
      m_textures.erase(res);
  }
  {
    auto res = std::find_if(m_tracks.begin(), m_tracks.end(), id_match);
    if (res != m_tracks.end())
      m_tracks.erase(res);
  }
}

template <> Asset<sf::Texture> *AssetManager::get(std::size_t id) {
  auto id_match = [id](const auto &asset) { return asset->id == id; };

  return *std::find_if(m_textures.begin(), m_textures.end(), id_match);
}
template <> Asset<sf::Music> *AssetManager::get(std::size_t id) {
  auto id_match = [id](const auto &asset) { return asset->id == id; };

  return *std::find_if(m_tracks.begin(), m_tracks.end(), id_match);
}
