#pragma once

#include "core/system.h"

class Movement : public System {
public:
    void init();
    void update(float dt);
};
