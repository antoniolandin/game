#include "scene-play.h"
#include "components/aabb.h"
#include "components/input.h"
#include "components/rect-shape.h"
#include "components/renderable.h"
#include "components/sprite.h"
#include "components/transform.h"
#include "game/game-engine.h"
#include "systems/render-aabb.h"
#include <SFML/Window/Keyboard.hpp>
#include <filesystem>

ScenePlay::ScenePlay(GameEngine* game_engine)
    : Scene(game_engine)
{
    // initialize coordinator
    m_coordinator.init();

    // register actions, components and systems
    registration();

    // spawn player
    spawnPlayer();

    // spawn test enemy
    spawnEnemy();
}

void ScenePlay::registration()
{
    // register actions
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::W, "MOVE_UP");
    registerAction(sf::Keyboard::S, "MOVE_DOWN");
    registerAction(sf::Keyboard::A, "MOVE_LEFT");
    registerAction(sf::Keyboard::D, "MOVE_RIGHT");

    // register components
    m_coordinator.registerComponent<Transform>();
    m_coordinator.registerComponent<AABB>();
    m_coordinator.registerComponent<RectShape>();
    m_coordinator.registerComponent<Renderable>();
    m_coordinator.registerComponent<Input>();
    m_coordinator.registerComponent<Sprite>();

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

    m_movement_system = m_coordinator.registerSystem<Movement>();
    {
        Signature signature;
        signature.set(m_coordinator.getComponentType<Transform>());
        signature.set(m_coordinator.getComponentType<Input>());
        m_coordinator.setSystemSignature<Movement>(signature);
    }
    m_movement_system->init();

    m_collision_system = m_coordinator.registerSystem<Collision>();
    {
        Signature signature;
        signature.set(m_coordinator.getComponentType<Transform>());
        signature.set(m_coordinator.getComponentType<AABB>());
        m_coordinator.setSystemSignature<Collision>(signature);
    }
    m_collision_system->init();

    // render sprite system
    m_render_sprite_system = m_coordinator.registerSystem<RenderSprite>();
    {
        Signature signature;
        signature.set(m_coordinator.getComponentType<Sprite>());
        signature.set(m_coordinator.getComponentType<Transform>());
        signature.set(m_coordinator.getComponentType<Renderable>());
        m_coordinator.setSystemSignature<RenderSprite>(signature);
    }
    m_render_sprite_system->init();

    // register assets
    std::filesystem::path project_root = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path();
    m_coordinator.addTexture("zombie_tileset", project_root / "assets/tileset.png");
}

void ScenePlay::spawnPlayer()
{
    m_player = m_coordinator.createEntity();

    Vec2 player_size = Vec2(64, 64);
    Vec2 window_center = Vec2(width() / 2.f, height() / 2.f);
    float player_speed = 200;

    m_coordinator.addComponent(m_player, AABB { player_size, player_size / 2 });
    m_coordinator.addComponent(m_player, Transform { window_center, window_center, Vec2(0, 0), player_speed });
    m_coordinator.addComponent(m_player, RectShape {});
    m_coordinator.addComponent(m_player, Sprite { {}, "zombie_tileset", 28, 10});
    m_coordinator.addComponent(m_player, Renderable { &m_game_engine->window() });
    m_coordinator.addComponent(m_player, Input {});

    m_render_aabb_system->initEntity(m_player);
    m_render_sprite_system->initEntity(m_player);
}

void ScenePlay::spawnEnemy()
{
    Entity enemy = m_coordinator.createEntity();

    Vec2 enemy_size = Vec2(64, 64);
    Vec2 enemy_position = Vec2(width() / 4.f, height() / 4.f);
    float enemy_speed = 100;

    m_coordinator.addComponent(enemy, AABB { enemy_size, enemy_size / 2 });
    m_coordinator.addComponent(enemy, Transform { enemy_position, enemy_position, Vec2(0, 0), enemy_speed });
    m_coordinator.addComponent(enemy, RectShape {});
    m_coordinator.addComponent(enemy, Renderable { &m_game_engine->window() });

    m_render_aabb_system->initEntity(enemy);
}

void ScenePlay::doAction(const Action& action)
{
    if (action.type == ACTION_START) {
        if (action.name == "QUIT") {
            m_game_engine->quit();
        } else if (action.name == "PAUSE") {
            m_paused = !m_paused;
        } else if (action.name == "MOVE_UP") {
            m_coordinator.getComponent<Input>(m_player).up = true;
        } else if (action.name == "MOVE_DOWN") {
            m_coordinator.getComponent<Input>(m_player).down = true;
        } else if (action.name == "MOVE_LEFT") {
            m_coordinator.getComponent<Input>(m_player).left = true;
        } else if (action.name == "MOVE_RIGHT") {
            m_coordinator.getComponent<Input>(m_player).right = true;
        }
    } else if (action.type == ACTION_END) {
        if (action.name == "MOVE_UP") {
            m_coordinator.getComponent<Input>(m_player).up = false;
        } else if (action.name == "MOVE_DOWN") {
            m_coordinator.getComponent<Input>(m_player).down = false;
        } else if (action.name == "MOVE_LEFT") {
            m_coordinator.getComponent<Input>(m_player).left = false;
        } else if (action.name == "MOVE_RIGHT") {
            m_coordinator.getComponent<Input>(m_player).right = false;
        }
    }
}

void ScenePlay::render()
{
    m_game_engine->window().clear(sf::Color::White);
    m_render_sprite_system->update();
    m_render_aabb_system->update();
    m_render_sprite_system->update();
}

void ScenePlay::update()
{
    if (!m_paused) {
        m_movement_system->update(m_game_engine->dt());
        m_collision_system->update();
    }
}
