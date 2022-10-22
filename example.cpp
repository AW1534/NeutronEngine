#include <iostream>

#include "neutron/macros.h"
#include "neutron/Window.h"
#include "neutron/Events.h"

int main() {
    N::EventSystem::get("update")->on([](Neutron::EventArgs data){
        std::cout << "update" << std::endl;
    });
    N::Window("Example");
    return 0;
}