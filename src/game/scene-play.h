#pragma once

#include "scene.h"
#include "systems/render-aabb.h"
#include "systems/movement.h"

class ScenePlay : public Scene {
private:
    Coordinator m_coordinator;
    Entity m_player;

    // systems
    std::shared_ptr<RenderAABB> m_render_aabb_system;
    std::shared_ptr<Movement> m_movement_system;

    void registration();
    void spawnPlayer();

public:
    ScenePlay(GameEngine* game_engine);

    void update() override;
    void doAction(const Action& action) override;
    void render() override;
};
