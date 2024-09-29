#pragma once

#include "core/types.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
private:
    std::map<std::string, sf::Texture> m_textures;

public:
    void addTexture(const std::string& name, const std::string& path);
    void loadAnimation(const Entity& entity, const std::string& name, const std::string& path);
    sf::Texture& getTexture(const std::string& name);
};
