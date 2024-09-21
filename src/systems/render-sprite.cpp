#include "render-sprite.h"
#include "core/coordinator.h"
#include "components/sprite.h"
#include "components/transform.h"
#include "components/renderable.h"

void RenderSprite::init() {
}

void RenderSprite::initEntity(Entity entity) {
    auto& sprite = m_coordinator->getComponent<Sprite>(entity);
    sprite.sprite.setTexture(m_coordinator->getTexture(sprite.tileset_name), true);
    sprite.sprite.setOrigin(8, 8);
    sprite.sprite.setScale(sprite.scale, sprite.scale);
}

void RenderSprite::update() {
    for (auto const& entity: m_entities) {
        auto& sprite = m_coordinator->getComponent<Sprite>(entity);
        auto& transform = m_coordinator->getComponent<Transform>(entity);
        auto& renderable = m_coordinator->getComponent<Renderable>(entity);

        // set the position of the sprite
        sprite.sprite.setPosition(transform.position.x, transform.position.y);

        // draw the sprite
        renderable.window->draw(sprite.sprite);
    }
}
