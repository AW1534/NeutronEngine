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
    Window* win;
    GameObject* go;
    unsigned int health;

    void Awake() {

    }

    void Start() {
        Logger::Log("Awake");

        win = (Window*) this->win;

        win->inputSystem->inputValues["move"] = std::make_shared<Input::InputAxis2D>(win->glfwWindow, KEY_W, KEY_S, KEY_D, KEY_A);

        go = static_cast<GameObject *>(this->gameObject);
        Logger::Log("New player created!");
    }

    void Update() {
        //Logger::Log("b");
    }

    void InputPress(InputArgs args) override {
        Logger::Log("bkjnjnkjnkjn");
    }
};


#endif //NEUTRONEXAMPLEC_CONTROLLER_H
