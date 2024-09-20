#pragma once

#include <string>
#include <SFML/Graphics/Sprite.hpp>

struct Sprite {
    sf::Sprite sprite;
    std::string tileset_name;
    int posX;
    int posY;
};
