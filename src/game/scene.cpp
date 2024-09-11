#include "scene.h"
#include "game/game-engine.h"
#include <cassert>

Scene::Scene(GameEngine *game_engine)
    : m_game_engine(game_engine)
{
}

void Scene::registerAction(std::uint16_t input_code, const std::string& name)
{
    assert(m_actions.find(input_code) == m_actions.end() && "Action already exists.");
    m_actions[input_code] = name;
}

size_t Scene::width() const
{
    return m_game_engine->window().getSize().x;
}

size_t Scene::height() const
{
    return m_game_engine->window().getSize().y;
}

size_t Scene::currentFrame() const
{
    return m_current_frame;
}

const std::unordered_map<std::uint16_t, std::string>& Scene::actions() const
{
    return m_actions;
}
