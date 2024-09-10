#include "scene.h"

class ScenePlay : public Scene {
private:
    void registerActions();
    Coordinator m_coordinator;

public:
    ScenePlay(GameEngine* game_engine);

    void update() override;
    void doAction(const Action& action) override;
    void render() override;
};
