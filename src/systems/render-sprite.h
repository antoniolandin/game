#pragma once

#include "core/system.h"

class RenderSprite : public System {
public:
    void init();
    void initEntity(Entity entity);
    void update();
};
