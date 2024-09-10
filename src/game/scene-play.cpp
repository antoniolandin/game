#include "scene-play.h"
#include "components/rect-shape.h"
#include "game/game-engine.h"
#include <SFML/Window/Keyboard.hpp>
#include "components/transform.h"
#include "components/aabb.h"
#include "components/renderable.h"
#include "systems/render-aabb.h"

ScenePlay::ScenePlay(GameEngine* game_engine)
    : Scene(game_engine)
{
    // initialize coordinator
    m_coordinator.init();
    
    // register actions, components and systems
    registration(); 

    // spawn player
    spawnPlayer();
}

void ScenePlay::registration()
{
    // register actions
    registerAction(sf::Keyboard::Escape, "QUIT");

    // register components
    m_coordinator.registerComponent<Transform>();
    m_coordinator.registerComponent<AABB>();
    m_coordinator.registerComponent<RectShape>();
    m_coordinator.registerComponent<Renderable>();

    // register systems
    m_render_aabb_system = m_coordinator.registerSystem<RenderAABB>();
    {
        Signature signature;
        signature.set(m_coordinator.getComponentType<RectShape>());
        signature.set(m_coordinator.getComponentType<AABB>());
        signature.set(m_coordinator.getComponentType<Transform>());
        signature.set(m_coordinator.getComponentType<Renderable>());
        m_coordinator.setSystemSignature<RenderAABB>(signature);
    }

    m_render_aabb_system->init();
}

void ScenePlay::spawnPlayer()
{
    Entity player = m_coordinator.createEntity();

    Vec2 player_size = Vec2(64, 64);
    Vec2 window_center = Vec2(width()/2.f, height()/2.f);

    m_coordinator.addComponent(player, AABB{player_size, player_size/2});
    m_coordinator.addComponent(player, Transform{window_center, Vec2(0,0)});
    m_coordinator.addComponent(player, RectShape{});
    m_coordinator.addComponent(player, Renderable{&m_game_engine->window()});
    
    m_render_aabb_system->initEntity(player);
}

void ScenePlay::update()
{
    m_render_aabb_system->update();
}

void ScenePlay::doAction(const Action& action)
{
    if(action.type == ACTION_START)
    {
        if(action.name == "QUIT")
        {
            m_game_engine->quit();
        }
    }
    else if(action.type == ACTION_END)
    {
    }
}


void ScenePlay::render()
{
}
