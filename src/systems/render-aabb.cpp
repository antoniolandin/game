#include "render-aabb.h"
#include "components/aabb.h"
#include "components/rect-shape.h"
#include "components/transform.h"
#include "components/renderable.h"
#include "core/coordinator.h"

void RenderAABB::init()
{
}

// initialize entity
void RenderAABB::initEntity(Entity entity)
{
    auto& rect_shape = m_coordinator->getComponent<RectShape>(entity);
    auto& aabb = m_coordinator->getComponent<AABB>(entity);
    
    rect_shape.shape.setOrigin(aabb.half_size.x, aabb.half_size.y);
    rect_shape.shape.setSize(sf::Vector2f(aabb.size.x, aabb.size.y));
    rect_shape.shape.setFillColor(sf::Color::Transparent);
    rect_shape.shape.setOutlineColor(sf::Color::Red);
    rect_shape.shape.setOutlineThickness(1);
}

// update all entities
void RenderAABB::update()
{
    for (auto const& entity : m_entities) {
        auto& transform = m_coordinator->getComponent<Transform>(entity);
        auto& rect_shape = m_coordinator->getComponent<RectShape>(entity);
        auto& renderable = m_coordinator->getComponent<Renderable>(entity);

        rect_shape.shape.setPosition(transform.position.x, transform.position.y);

        renderable.window->draw(rect_shape.shape);
    }
}
