//
// Created by aw1lt on 29/11/22.
//

#include "Neutron/Components/BaseComponent.h"
#include "Neutron/Window.h"

namespace Neutron {

    void BaseComponent::Draw(bool vulkan) {

    }

    void BaseComponent::Awake() {

    }

    void BaseComponent::handleMethod(Input::Type type, InputArgs args) {
        switch(type) {
            case Input::Type::PRESS:
                this->InputPress(args);
            case Input::Type::RELEASE:
                this->InputRelease(args);
            case Input::Type::REPEAT:
                this->InputRepeat(args);
        }
    }

    void BaseComponent::_Awake(void* win, void* go) {
        this->win = win;
        this->gameObject = go;
        this->Awake();

        Window* wwin = (Window*) win;

        EventSystem::get("inputPress")->on([this](EventArgs args) {
            InputArgs iArgs;

            iArgs.action = *(int*)args["action"];
            iArgs.key = *(int*)args["key"];
            iArgs.mods = *(int*)args["mods"];
            iArgs.scancode = *(int*)args["scancode"];

            this->handleMethod(Input::Type::PRESS, iArgs);
        });

        EventSystem::get("inputRelease")->on([this](EventArgs args) {
            InputArgs iArgs;

            iArgs.action = *(int*)args["action"];
            iArgs.key = *(int*)args["key"];
            iArgs.mods = *(int*)args["mods"];
            iArgs.scancode = *(int*)args["scancode"];

            this->handleMethod(Input::Type::RELEASE, iArgs);
        });

        EventSystem::get("inputRepeat")->on([this](EventArgs args) {
            InputArgs iArgs;

            iArgs.action = *(int*)args["action"];
            iArgs.key = *(int*)args["key"];
            iArgs.mods = *(int*)args["mods"];
            iArgs.scancode = *(int*)args["scancode"];

            this->handleMethod(Input::Type::REPEAT, iArgs);
        });

        EventSystem::get("input")->on([this](EventArgs args) {
            InputArgs iArgs;

            iArgs.action = *(int*)args["action"];
            iArgs.key = *(int*)args["key"];
            iArgs.mods = *(int*)args["mods"];
            iArgs.scancode = *(int*)args["scancode"];

            this->Input(iArgs);
        });
    }

    void BaseComponent::_Start() {
        this->Start();
    }

    void BaseComponent::Start() {

    }

    BaseComponent::BaseComponent() {
    }

    BaseComponent::~BaseComponent() {

    }

    void BaseComponent::Update() {

    }

    void BaseComponent::Input(InputArgs args) {

    }

    void BaseComponent::InputPress(InputArgs args) {
        Logger::Log("hi");
    }

    void BaseComponent::InputRelease(InputArgs args) {
    }

    void BaseComponent::InputRepeat(InputArgs args) {

    }

} // Neutron