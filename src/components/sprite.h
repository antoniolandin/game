#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <string>

struct Sprite {
    sf::Sprite sprite {};
    std::string tileset_name {};
    float scale;
};
