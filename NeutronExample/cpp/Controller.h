//
// Created by aw1lt on 07/12/22.
//

#ifndef NEUTRONEXAMPLEC_CONTROLLER_H
#define NEUTRONEXAMPLEC_CONTROLLER_H

#include <Neutron/Components/BaseComponent.h>
#include <Neutron/Logger.h>
#include <optional>

using namespace Neutron;

class Controller : public BaseComponent {
public:
    GameObject* go;
    unsigned int health;

    void Start() {
        go = static_cast<GameObject *>(this->gameObject);
        Logger::Log("New player created!");
    }

    void Update() {
        //Logger::Log("b");
    }

    void InputPress(InputArgs args) {
        Logger::Log("bkjnjnkjnkjn");
    }
};


#endif //NEUTRONEXAMPLEC_CONTROLLER_H
