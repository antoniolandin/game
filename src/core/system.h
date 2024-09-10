#pragma once

#include "types.h"
#include <set>

class Coordinator;

class System {
public:
    std::set<Entity> m_entities;
    Coordinator* m_coordinator;

    System(Coordinator* coordinator) : m_coordinator(coordinator) {}
};
