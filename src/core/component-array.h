#pragma once

#include "types.h"
#include <array>
#include <cassert>
#include <unordered_map>

// the interface is necesary to store all the different component arrays in the same container
class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
private:
    std::array<T, MAX_ENTITIES> m_component_array {};

    // we use unordered maps because they have faster lookups and insertions than ordered maps
    std::unordered_map<Entity, size_t> m_entity_to_index_map {};
    std::unordered_map<size_t, Entity> m_index_to_entity_map {};
    size_t mSize {};

public:
    void insertData(Entity entity, T component)
    {
        // check that there is not a component for the entity (entity can only have one component of each type)
        assert(m_entity_to_index_map.find(entity) == m_entity_to_index_map.end() && "Component added to same entity more than once.");

        // put new entry at end
        size_t newIndex = mSize;

        // update maps
        m_entity_to_index_map[entity] = newIndex;
        m_index_to_entity_map[newIndex] = entity;

        // add component to end
        m_component_array[newIndex] = component;
        mSize++;
    }

    void removeData(Entity entity)
    {
        // check that the entity has a component
        assert(m_entity_to_index_map.find(entity) != m_entity_to_index_map.end() && "Removing non-existent component.");

        // get the index of the removed entity
        size_t indexOfRemovedEntity = m_entity_to_index_map[entity];

        // get the index of the last element
        size_t indexOfLastElement = mSize - 1;

        // copy the last entity to the removed entity's position
        m_component_array[indexOfRemovedEntity] = m_component_array[indexOfLastElement];

        // get the entity of the last element
        Entity entityOfLastElement = m_index_to_entity_map[indexOfLastElement];

        // update maps to point the last element to the spot of the removed element
        m_entity_to_index_map[entityOfLastElement] = indexOfRemovedEntity;
        m_index_to_entity_map[indexOfRemovedEntity] = entityOfLastElement;
        
        // remove entity from maps
        m_entity_to_index_map.erase(entity);
        m_index_to_entity_map.erase(indexOfLastElement);

        mSize--;
    }

    T& getData(Entity entity)
    {
        // check that the entity has a component
        assert(m_entity_to_index_map.find(entity) != m_entity_to_index_map.end() && "Retrieving non-existent component.");

        return m_component_array[m_entity_to_index_map[entity]];
    }
    
    // remove the entity component from the array if it had the component
    void entityDestroyed(Entity entity) override
    {
        // check that the entity has a component
        if (m_entity_to_index_map.find(entity) != m_entity_to_index_map.end()) {
            removeData(entity);
        }
    }
};
