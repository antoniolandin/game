#include "system.h"
#include "types.h"
#include <cassert>
#include <memory>
#include <unordered_map>

class SystemManager {
private:
    // map from system type string pointer to a signature
    std::unordered_map<const char*, Signature> m_signatures {};

    // map from system type string pointer to a system pointer
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems {};

public:
    template <typename T>
    std::shared_ptr<T> registerSystem()
    {
        const char* type_name = typeid(T).name();

        assert(m_systems.find(type_name) == m_systems.end() && "Registering system more than once.");

        // create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        m_systems.insert({ type_name, system });
        return system;
    }

    template <typename T>
    void setSignature(Signature signature)
    {
        const char* type_name = typeid(T).name();

        assert(m_systems.find(type_name) != m_systems.end() && "System used before registered.");

        // set the signature for this system
        m_signatures.insert({ type_name, signature });
    }

    void entityDestroyed(Entity entity)
    {
        // erase a destroyed entity from all system lists
        // m_entities is a set so no check needed
        for (auto const& pair : m_systems) {
            auto const& system = pair.second;

            system->m_entities.erase(entity);
        }
    }

    void entitySignatureChanged(Entity entity, Signature entity_signature)
    {
        // notify each system that an entity's signature changed
        for (auto const& pair : m_systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& system_signature = m_signatures[type];

            // entity signature matches system signature - insert into set
            if ((entity_signature & system_signature) == system_signature) {
                system->m_entities.insert(entity);
            }
            // entity signature does not match system signature - erase from set
            else {
                system->m_entities.erase(entity);
            }
        }
    }
};
