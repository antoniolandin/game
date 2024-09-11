#include "math/vec2.h"

struct Transform {
    Vec2 position;
    Vec2 previous_position;
    Vec2 velocity;
    float speed;
};
