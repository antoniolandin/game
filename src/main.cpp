#include "core/entity-manager.h"
#include <iostream>

int main (int argc, char *argv[]) {

    EntityManager entity_manager;
    
    std::cout << entity_manager.livingEntityCount() << std::endl;
    entity_manager.createEntity();
    std::cout << entity_manager.livingEntityCount() << std::endl;
    
    return 0;
}
