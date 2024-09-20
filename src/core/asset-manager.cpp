#include "asset-manager.h"

void AssetManager::addTexture(const std::string& name, const std::string& path) {
    sf::Texture texture;
    texture.loadFromFile(path);
    m_textures[name] = texture;
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    return m_textures.at(name);
}
