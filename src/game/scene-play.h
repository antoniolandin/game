#pragma once

#include "scene.h"
#include "systems/render-aabb.h"

class ScenePlay : public Scene {
private:
    Coordinator m_coordinator;
    std::vector<Entity> m_entities;

    // systems
    std::shared_ptr<RenderAABB> m_render_aabb_system;

    void registration();
    void spawnPlayer();

public:
    ScenePlay(GameEngine* game_engine);

    void update() override;
    void doAction(const Action& action) override;
    void render() override;
};
