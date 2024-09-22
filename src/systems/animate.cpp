#include "animate.h"
#include "components/animate.h"
#include "components/sprite.h"
#include "core/coordinator.h"

void AnimationSystem::init()
{
}

void AnimationSystem::update(float dt)
{
    for (auto const& entity : m_entities) {
        auto& animate = m_coordinator->getComponent<Animate>(entity);
        auto& sprite = m_coordinator->getComponent<Sprite>(entity);

        // update the sprite with the current frame
        sprite.sprite.setTextureRect(
            animate.frames.at(animate.current_animation).frames.at(animate.current_frame));
        
        // flip the sprite if necessary
        if (animate.frames.at(animate.current_animation).flip) {
            sprite.sprite.setScale(-sprite.scale, sprite.scale);
        } else {
            sprite.sprite.setScale(sprite.scale, sprite.scale);
        }

        // update the elapsed time
        animate.elapsed_time += dt;
        if (animate.elapsed_time >= animate.frames.at(animate.current_animation).frame_duration) {
            animate.elapsed_time = 0;

            animate.current_frame++;
            if (animate.current_frame >= animate.frames.at(animate.current_animation).frames.size()) {
                animate.current_frame = 0;
            }
        }
    }
}
