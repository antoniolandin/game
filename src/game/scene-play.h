#pragma once

#include "scene.h"
#include "systems/movement.h"
#include "systems/render-aabb.h"
#include "systems/collision.h"
#include "systems/render-sprite.h"

class ScenePlay : public Scene {
private:
    Coordinator m_coordinator;
    Entity m_player;

    // systems
    std::shared_ptr<RenderAABB> m_render_aabb_system;
    std::shared_ptr<Movement> m_movement_system;
    std::shared_ptr<Collision> m_collision_system;
    std::shared_ptr<RenderSprite> m_render_sprite_system; 

    void registration();
    void spawnPlayer();
    void spawnEnemy();

public:
    ScenePlay(GameEngine* game_engine);

    void update() override;
    void doAction(const Action& action) override;
    void render() override;
};
