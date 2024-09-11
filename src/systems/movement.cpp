#include "movement.h"

#include "core/coordinator.h"
#include "components/input.h"
#include "components/transform.h"

void Movement::init()
{
}

Vec2 velocityFromInput(const Input& input)
{
    Vec2 velocity = Vec2(0, 0);

    int count = 0;

    if (input.up) {
        velocity.y -= 1;
        count++;
    }
    else if (input.down) {
        velocity.y += 1;
        count++;
    }
    if (input.left) {
        velocity.x -= 1;
        count++;
    }
    else if (input.right) {
        velocity.x += 1;
        count++;
    }
    
    // normaliza if the velocity is diagonal
    if (count > 1) {
        velocity /= 1.41421356;
    }

    return velocity;
}

void Movement::update(float dt)
{
    for (auto& entity : m_entities) {
        auto& transform = m_coordinator->getComponent<Transform>(entity);
        auto& input = m_coordinator->getComponent<Input>(entity);

        // get the velocity
        Vec2 velocity = velocityFromInput(input);

        // update the position
        transform.position += velocity * transform.speed * dt;
    }
}
