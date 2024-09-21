#include "idle.h"
#include "components/facing.h"
#include "components/idle.h"
#include "components/sprite.h"
#include "components/transform.h"
#include "core/coordinator.h"

void IdleSystem::init()
{
}

void IdleSystem::update()
{
    for (auto const& entity : m_entities) {
        auto& facing = m_coordinator->getComponent<Facing>(entity);
        auto& idle = m_coordinator->getComponent<Idle>(entity);
        auto& sprite = m_coordinator->getComponent<Sprite>(entity);
        auto& transform = m_coordinator->getComponent<Transform>(entity);

        // if the entity is moving, do not set the idle sprite
        if (transform.velocity.x != 0 || transform.velocity.y != 0) {
            continue;
        }

        sprite.sprite.setTextureRect(idle.sprite_rects.at(facing.direction).rect);
        if (idle.sprite_rects.at(facing.direction).flip) {
            sprite.sprite.setScale(-sprite.scale, sprite.scale);
        } else if (facing.direction == LEFT) {
            sprite.sprite.setScale(sprite.scale, sprite.scale);
        }
    }
}
