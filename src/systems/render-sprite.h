#pragma once

#include "core/system.h"

class RenderSprite : public System {
public:
    void init();
    void getSpriteFromZombieTileset(const Entity entity);
    void initEntity(const Entity entity);
    void update();
};
