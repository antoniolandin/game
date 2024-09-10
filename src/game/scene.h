#pragma once

#include <unordered_map>
#include "action.h"
#include "core/coordinator.h"

class GameEngine;

class Scene {
protected:
    GameEngine* m_game_engine;
    Coordinator m_coordinator;
    std::unordered_map<std::uint16_t, std::string> m_actions {};
    bool m_paused {};
    size_t m_current_frame {};
    
    // setters
    void setPaused(bool paused);
    void registerAction(std::uint16_t input_code, const std::string& action_name);

public:
    Scene(GameEngine* game_engine);

    // methods to be implemented by the derived class
    virtual void update() = 0;
    virtual void doAction(const Action& action) = 0;
    virtual void render() = 0;

    // getters
    size_t width() const;
    size_t height() const;
    size_t currentFrame() const;
    const std::unordered_map<std::uint16_t, std::string>& actions() const;
};
