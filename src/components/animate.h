#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <map>
#include <string>


struct Animate {
    struct Animation {
        float frame_duration = 0;
        std::vector<sf::IntRect> frames;
        bool flip = false;
    };

    std::map<std::string, Animation> frames;
    std::string current_animation;
    int current_frame = 0;
    float elapsed_time = 0;
};
