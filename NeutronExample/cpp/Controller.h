//
// Created by aw1lt on 07/12/22.
//

#ifndef NEUTRONEXAMPLEC_CONTROLLER_H
#define NEUTRONEXAMPLEC_CONTROLLER_H

#include "Neutron/macros/input.h"

#include <memory>
#include <Neutron/Components/BaseComponent.h>
#include <Logger/Logger.h>
#include <optional>

using namespace Neutron;

class Controller : public BaseComponent {
public:
    Window* window;
    GameObject* go;
    unsigned int health;

    void Awake() {

    }

    void Start() {

        Logger::Log("Awake");

        this->window = (Window*)this->win;
        Logger::Log("among us");

        std::shared_ptr<Input::InputSystem> is = this->window->inputSystem;

        Logger::Log("among us");

        Logger::Assert(is != nullptr, "Input system is null", 5);

        auto iv = (*is).GetValue<Input::InputAxis2D*>("move");

        Logger::Log("among us");

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
