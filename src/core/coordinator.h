#pragma once

#include "component-manager.h"
#include "entity-manager.h"
#include "system-manager.h"
#include "types.h"
#include <memory>

class Coordinator {
private:
    std::unique_ptr<ComponentManager> m_component_manager;
    std::unique_ptr<EntityManager> m_entity_manager;
    std::unique_ptr<SystemManager> m_system_manager;

public:
    void init()
    {
        // create pointers to each manager
        m_component_manager = std::make_unique<ComponentManager>();
        m_entity_manager = std::make_unique<EntityManager>();
        m_system_manager = std::make_unique<SystemManager>();
    }

    // entity methods
    Entity createEntity()
    {
        return m_entity_manager->createEntity();
    }

    void destroyEntity(Entity entity)
    {
        m_entity_manager->destroyEntity(entity);
        m_component_manager->entityDestroyed(entity);
        m_system_manager->entityDestroyed(entity);
    }

    std::uint32_t numEntities()
    {
        return m_entity_manager->livingEntityCount();
    }

    // component methods
    template <typename T>
    void registerComponent()
    {
        m_component_manager->registerComponent<T>();
    }

    template <typename T>
    void addComponent(Entity entity, T component)
    {
        // add the component in the component manager
        m_component_manager->addComponent<T>(entity, component);

        // modify the entity signature to include the new component
        auto signature = m_entity_manager->getSignature(entity);
        signature.set(m_component_manager->getComponentType<T>(), true);

        // update the signature in the managers
        m_entity_manager->setSignature(entity, signature);
        m_system_manager->entitySignatureChanged(entity, signature);
    }

    template <typename T>
    void removeComponent(Entity entity)
    {
        // remove the component in the component manager
        m_component_manager->removeComponent<T>(entity);

        // modify the entity signature to remove the component
        auto signature = m_entity_manager->getSignature(entity);
        signature.set(m_component_manager->getComponentType<T>(), false);

        // update the signature in the managers
        m_entity_manager->setSignature(entity, signature);
        m_system_manager->entitySignatureChanged(entity, signature);
    }

    template <typename T>
    T& getComponent(Entity entity)
    {
        return m_component_manager->getComponent<T>(entity);
    }

    template <typename T>
    ComponentType getComponentType()
    {
        return m_component_manager->getComponentType<T>();
    }

    // system methods
    template <typename T>
    std::shared_ptr<T> registerSystem()
    {
        return m_system_manager->registerSystem<T>(this);
    }

    template <typename T>
    void setSystemSignature(Signature signature)
    {
        m_system_manager->setSignature<T>(signature);
    }
};
