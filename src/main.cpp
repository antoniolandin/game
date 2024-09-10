#include "core/coordinator.h"
#include "components/transform.h"
#include <iostream>

Coordinator g_coordinator;

int main (int argc, char *argv[]) {

    g_coordinator.init();

    g_coordinator.registerComponent<Transform>();

    std::cout << "Number of entities: " << g_coordinator.numEntities() << std::endl;
    g_coordinator.createEntity(); 
    std::cout << "Number of entities: " << g_coordinator.numEntities() << std::endl;

    return 0;
}
