#include "render-sprite.h"
#include "core/coordinator.h"
#include "components/sprite.h"
#include "components/transform.h"
#include "components/renderable.h"

void RenderSprite::init() {
}

// get the sprite from the zombie tileset (it has weird spacing)
void RenderSprite::getSpriteFromZombieTileset(const Entity entity) {
    // get the sprite component
    auto& sprite = m_coordinator->getComponent<Sprite>(entity);

    // get the texture from the asset manager
    auto& texture = m_coordinator->getTexture(sprite.tileset_name);
    
    // define the tileset properties
    const int tile_width = 16;
    const int tile_height = 16;
    const int tile_spacing_x = 1;
    const float tile_spacing_y = 1.5;
    const float scale = 4;

    // calculate the position of the sprite in the tileset
    const int posX = ((sprite.posX + 1) * tile_width) + (sprite.posX * tile_spacing_x) + 1;
    const int posY = ((sprite.posY + 1) * tile_height) + (sprite.posY * tile_spacing_y) - 1;

    // generate the sprite from the tileset using the position and size
    sprite.sprite.setTexture(texture, true);
    sprite.sprite.setScale(scale, scale);
    sprite.sprite.setTextureRect(sf::IntRect(posX, posY, tile_width, tile_height));
    sprite.sprite.setOrigin(tile_width / 2.f, tile_height / 2.f);
}

void RenderSprite::initEntity(const Entity entity) {
    getSpriteFromZombieTileset(entity);
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
