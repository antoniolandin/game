#pragma once

#include "core/system.h"
#include <SFML/Graphics.hpp>

class RenderAABB : public System
{
    public:
        void init();
        void initEntity(Entity entity);
        void update();
};
