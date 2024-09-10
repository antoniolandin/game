#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "scene.h"
#include <memory>
#include <unordered_map>


class GameEngine {
protected:
    sf::RenderWindow m_window;
    std::shared_ptr<Scene> m_current_scene;
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
    bool m_running = true;

    void userInput();

public:
    // constructor
    GameEngine();

    // getters
    sf::RenderWindow& window();

    // scene management
    void registerScene(const std::string& name, std::shared_ptr<Scene> scene);
    void changeScene(const std::string& name);

    // game loop
    void quit();
    void run();
};
