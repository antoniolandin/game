#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>
#include "core/types.h"

struct Idle {
    struct Properties {
        sf::IntRect rect;
        bool flip = false;
    };

    std::unordered_map<Direction, Properties> sprite_rects;
};
