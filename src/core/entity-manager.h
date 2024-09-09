#pragma once

#include "types.h"
#include <array>
#include <cassert>
#include <queue>

class EntityManager {
private:
    // queue of unused entity ids
    std::queue<Entity> m_available_entities {};

    // array of signatures where the index corresponds to the entity id
    std::array<Signature, MAX_ENTITIES> m_signatures {};

    // total living entities
    std::uint32_t m_living_entity_count {};

public:
    EntityManager();
    Entity createEntity();
    void destroyEntity(Entity entity);
    void setSignature(Entity entity, Signature signature);
    Signature getSignature(Entity entity);
    uint32_t livingEntityCount();
};
