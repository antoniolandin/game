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
    void init();

    Entity createEntity();

    void destroyEntity(Entity entity);
    std::uint32_t numEntities();

    template <typename T>
    void registerComponent();

    template <typename T>
    void addComponent(Entity entity, T component);

    template <typename T>
    void removeComponent(Entity entity);

    template <typename T>
    T& getComponent(Entity entity);

    template <typename T>
    ComponentType getComponentType();

    // system methods
    template <typename T>
    std::shared_ptr<T> registerSystem();

    template <typename T>
    void setSystemSignature(Signature signature);
};
