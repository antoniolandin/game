#include "coordinator.h"

void Coordinator::init()
    {
        // create pointers to each manager
        m_component_manager = std::make_unique<ComponentManager>();
        m_entity_manager = std::make_unique<EntityManager>();
        m_system_manager = std::make_unique<SystemManager>();
    }

    // entity methods
    Entity Coordinator::createEntity()
    {
        return m_entity_manager->createEntity();
    }

    void Coordinator::destroyEntity(Entity entity)
    {
        m_entity_manager->destroyEntity(entity);
        m_component_manager->entityDestroyed(entity);
        m_system_manager->entityDestroyed(entity);
    }

    std::uint32_t Coordinator::numEntities()
    {
       return m_entity_manager->livingEntityCount();
    }

    // component methods
    template <typename T>
    void Coordinator::registerComponent()
    {
        m_component_manager->registerComponent<T>();
    }

    template <typename T>
    void Coordinator::addComponent(Entity entity, T component)
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
    void Coordinator::removeComponent(Entity entity)
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
    T& Coordinator::getComponent(Entity entity)
    {
        return m_component_manager->getComponent<T>(entity);
    }

    template <typename T>
    ComponentType Coordinator::getComponentType()
    {
        return m_component_manager->getComponentType<T>();
    }

    // system methods
    template <typename T>
    std::shared_ptr<T> Coordinator::registerSystem()
    {
        return m_system_manager->registerSystem<T>();
    }

    template <typename T>
    void Coordinator::setSystemSignature(Signature signature)
    {
        m_system_manager->setSignature<T>(signature);
    }
