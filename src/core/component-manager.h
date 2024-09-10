#include "component-array.h"
#include "types.h"
#include <cassert>
#include <memory>
#include <typeinfo>
#include <unordered_map>

class ComponentManager {
private:
    // map from type string pointer to a component type
    std::unordered_map<const char*, ComponentType> m_component_types {};

    // map from type string pointer to a component array
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_component_arrays {};

    // the component type to be assigned to the next registered component - starting at 0
    ComponentType m_next_component_type {};

    // convenience function to get the statically casted pointer to the ComponentArray of type T.
    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        // get the name of the type
        const char* typeName = typeid(T).name();

        // check if the component type has been registered
        assert(m_component_types.find(typeName) != m_component_types.end() && "Component not registered before use.");

        // return the ComponentArray of type T
        return std::static_pointer_cast<ComponentArray<T>>(m_component_arrays[typeName]);
    }

public:
    template <typename T>
    void registerComponent()
    {
        // get the name of the type
        const char* typeName = typeid(T).name();

        // check that the component type has not already been registered
        assert(m_component_types.find(typeName) == m_component_types.end() && "Registering component type more than once.");

        // add this component type to the component type map
        m_component_types.insert({ typeName, m_next_component_type });

        // create a ComponentArray pointer and add it to the component arrays map
        m_component_arrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

        // increment the value so that the next component registered will be different
        m_next_component_type++;
    }

    template <typename T>
    ComponentType getComponentType()
    {
        // get the name of the type
        const char* typeName = typeid(T).name();

        // check that the component type has been registered
        assert(m_component_types.find(typeName) != m_component_types.end() && "Component not registered before use.");

        // return this component's type - used for creating signatures
        return m_component_types[typeName];
    }

    template <typename T>
    void addComponent(Entity entity, T component)
    {
        // add a component to the array for an entity
        getComponentArray<T>()->insertData(entity, component);
    }

    template <typename T>
    void removeComponent(Entity entity)
    {
        // remove a component from the array for an entity
        getComponentArray<T>()->removeData(entity);
    }

    template <typename T>
    T& getComponent(Entity entity)
    {
        // get a reference to a component from the array for an entity
        return getComponentArray<T>()->getData(entity);
    }

    void entityDestroyed(Entity entity)
    {
        // notify each component array that an entity has been destroyed
        // if it has a component for that entity, it will remove it
        for (auto const& pair : m_component_arrays) {
            auto const& component = pair.second;

            component->entityDestroyed(entity);
        }
    }
};
