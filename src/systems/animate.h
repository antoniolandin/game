#pragma once

#include "core/system.h"

class AnimationSystem : public System {
public:
    void init();
    void update(float dt);
};
