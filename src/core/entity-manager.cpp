#include "entity-manager.h"

EntityManager::EntityManager()
{
    // initialize the queue with all possible entity ids
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        m_available_entities.push(entity);
    }
}

Entity EntityManager::createEntity()
{
    assert(m_living_entity_count < MAX_ENTITIES && "Too many entities in existence.");

    // take an id from the front of the queue
    Entity id = m_available_entities.front();
    m_available_entities.pop();
    m_living_entity_count++;

    return id;
}

void EntityManager::destroyEntity(Entity entity)
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // invalidate the destroyed entity's signature (sets all bits to false)
    m_signatures[entity].reset();

    // put the destroyed id at the back of the queue
    m_available_entities.push(entity);
    m_living_entity_count--;
}

void EntityManager::setSignature(Entity entity, Signature signature)
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // put this entity's signature into the array
    m_signatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // get this entity's signature from the array
    return m_signatures[entity];
}

uint32_t EntityManager::livingEntityCount()
{
    return m_living_entity_count;
}
