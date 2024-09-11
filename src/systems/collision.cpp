#include "collision.h"
#include "core/coordinator.h"
#include "components/transform.h"
#include "components/aabb.h"

void Collision::init() {
}

void Collision::update() {
    for (auto const& entity: m_entities) {
        auto& transform = m_coordinator->getComponent<Transform>(entity);
        auto& aabb = m_coordinator->getComponent<AABB>(entity);

        // check collision with other entities
        for (auto const& other_entity: m_entities) {
            if (entity == other_entity) {
                continue;
            }

            auto& other_transform = m_coordinator->getComponent<Transform>(other_entity);
            auto& other_aabb = m_coordinator->getComponent<AABB>(other_entity);
            
            // get the overlap
            Vec2 delta = other_transform.position - transform.position;
            Vec2 overlap = aabb.half_size + other_aabb.half_size - Vec2::abs(delta);

            // get the previous overlap
            Vec2 previous_delta = other_transform.previous_position - transform.previous_position;
            Vec2 previous_overlap = aabb.half_size + other_aabb.half_size - Vec2::abs(previous_delta);

            if (overlap.x > 0 && overlap.y > 0) {
                // vertical collision
                if(overlap.y >= 0 && previous_overlap.y <= 0)
                {
                    if(delta.y > 0)
                    {
                        // collision with the top of the other entity
                        transform.position.y -= overlap.y;
                    }
                    else
                    {
                        // collision with the bottom of the other entity
                        transform.position.y += overlap.y;
                    }
                }
                
                // horizontal collision
                if(overlap.x >= 0 && previous_overlap.x <= 0)
                {
                    if(delta.x > 0)
                    {
                        // collision with the left of the other entity 
                        transform.position.x -= overlap.x;
                    }
                    else
                    {
                        // collision with the right of the other entity
                        transform.position.x += overlap.x;
                    }
                }
            }
        }
    } 
}
