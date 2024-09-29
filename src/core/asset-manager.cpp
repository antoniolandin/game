#include "asset-manager.h"

void AssetManager::addTexture(const std::string& name, const std::string& path) {
    sf::Texture texture;
    texture.loadFromFile(path);
    m_textures[name] = texture;
}

// get the sprite from the zombie tileset (it has weird spacing)
sf::IntRect getSpriteRectFromZombieTileset(const int x, const int y)
{
    // define the tileset properties
    const int tile_width = 16;
    const int tile_height = 16;
    const int tile_spacing_x = 1;
    const float tile_spacing_y = 3;
    const float scale = 4;

    // calculate the position of the sprite in the tileset
    const int posX = (x * tile_width) + (x * tile_spacing_x);
    const int posY = (y * tile_height) + (y * tile_spacing_y);

    // generate the sprite from the tileset using the position and size
    return sf::IntRect(posX, posY, tile_width, tile_height);
}

void AssetManager::loadAnimation(const Entity& entity, const std::string& name, const std::string& path) {
    sf::Texture texture;
    texture.loadFromFile(path);
    m_textures[name] = texture;
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    return m_textures.at(name);
}
