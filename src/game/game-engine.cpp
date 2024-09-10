#include "game-engine.h"
#include "scene-play.h"
#include <SFML/Window/Event.hpp>
#include <cassert>

GameEngine::GameEngine()
{
    // create the window
    m_window.create(sf::VideoMode(800, 600), "Game");
    m_window.setFramerateLimit(60);

    registerScene("play", std::make_shared<ScenePlay>(this));
    changeScene("play");
}

sf::RenderWindow& GameEngine::window()
{
    return m_window;
}

void GameEngine::userInput()
{
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            quit();
        }

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed) {
            // get the code of the key that was pressed
            int code;
            
            ActionType action_type;
            
            // if the event is a mouse button press, add the number of keys to the code
            if (event.type == sf::Event::MouseButtonPressed) {
                code = (int)event.mouseButton.button + sf::Keyboard::KeyCount;
                action_type = ACTION_START;
            }
            else {
                code = event.key.code;
                action_type = (event.type == sf::Event::KeyPressed) ? ACTION_START : ACTION_END;
            }

            // if the current scene does not have an action associated with this key, skip the event
            if (m_current_scene->actions().find(code) == m_current_scene->actions().end()) {
                continue;
            } 
            
            // get the name of the action associated with the key
            const std::string action_name = m_current_scene->actions().at(code);

            // look up the action and send the action to the scene
            m_current_scene->doAction(Action(action_name, action_type));
        }
    }
}

void GameEngine::registerScene(const std::string& name, std::shared_ptr<Scene> scene)
{
    // make sure the scene doesn't already exist
    assert(m_scenes.find(name) == m_scenes.end() && "Scene already exists.");

    // add the scene to the map
    m_scenes[name] = scene;
}

void GameEngine::changeScene(const std::string& name)
{
    // make sure the scene exists
    assert(m_scenes.find(name) != m_scenes.end() && "Scene does not exist.");

    // set the current scene
    m_current_scene = m_scenes[name];
}

void GameEngine::quit()
{
    m_running = false;
    m_window.close();
}

void GameEngine::run()
{
    assert(m_current_scene && "No scene set.");

    while (m_running) {
        userInput();
        m_current_scene->update();
        m_current_scene->render();
        m_window.display();
    }
}
