#include "player-animation.h"
#include "components/facing.h"
#include "components/transform.h"
#include "components/animate.h"
#include "core/coordinator.h"

void PlayerAnimation::init()
{
}

void PlayerAnimation::update()
{
    for (auto const& entity: m_entities)
    {
        // get the components
        auto& facing = m_coordinator->getComponent<Facing>(entity);
        auto& transform = m_coordinator->getComponent<Transform>(entity);
        auto& animate = m_coordinator->getComponent<Animate>(entity);
        
        // store the current animation
        const std::string current_animation = animate.current_animation;
        
        // set the type of animation
        if (transform.velocity.x != 0 || transform.velocity.y != 0)
        {
            animate.current_animation = "WALK";
        }
        else
        {
            animate.current_animation = "IDLE";
        }
        
        // set the direction of the animation
        switch(facing.direction)
        {
            case UP:
                animate.current_animation += "_UP";
                break;
            case DOWN:
                animate.current_animation += "_DOWN";
                break;
            case LEFT:
                animate.current_animation += "_LEFT";
                break;
            case RIGHT:
                animate.current_animation += "_RIGHT";
                break;
        }
        
        // if the animation has changed, reset the frame
        if (current_animation != animate.current_animation)
        {
            animate.current_frame = 0;
        }
    }
}
