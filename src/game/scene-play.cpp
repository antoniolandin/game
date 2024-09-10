#include "scene-play.h"
#include "game/game-engine.h"
#include <SFML/Window/Keyboard.hpp>

ScenePlay::ScenePlay(GameEngine* game_engine)
    : Scene(game_engine)
{
    registerAction(sf::Keyboard::Escape, "QUIT");
}

void ScenePlay::update()
{
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
