#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class AssetManager {
private:
    std::map<std::string, sf::Texture> m_textures;
public:
    void addTexture(const std::string& name, const std::string& path);
    sf::Texture& getTexture(const std::string& name);
};
