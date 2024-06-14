//
// Created by aw1lt on 07/12/22.
//

#ifndef NEUTRONEXAMPLEC_CONTROLLER_H
#define NEUTRONEXAMPLEC_CONTROLLER_H

#include "Neutron/macros/input.h"

#include <memory>
#include <Neutron/Components/BaseComponent.h>
#include "Logger.h"
#include <optional>

using namespace Neutron;

class Controller : public BaseComponent {
public:
    Window* window;
    GameObject* go;
    unsigned int health;
    std::shared_ptr<Input::InputSystem> is;

    void Awake() {

    }

    void Start() {

        Logger::Log("Awake");

        this->window = (Window*)this->win;
        Logger::Log("among us");

        is = this->window->inputSystem;

        Logger::Log("among us");

        Logger::Assert(is != nullptr, "Input system is null", 5);


        Logger::Log("among us");

        Logger::Log("New player created!");

        Neutron::EventSystem::get("inputPress")->on([this](EventArgs args){
            int key = *EventSystem::GetArg<int*>(args, "key");

            Logger::Log(std::to_string(this->is->keys.find(GLFW_KEY_W)->second));
            Logger::Log(std::to_string(key) + " Was pressed!!");
            return;
        });

    }

    void Update() {
        Logger::Log(std::to_string(is->keyDown(GLFW_KEY_W)));


    }

    void InputPress(InputArgs args) {
        Logger::Log("bkjnjnkjnkjn");
    }
};


#endif //NEUTRONEXAMPLEC_CONTROLLER_H
