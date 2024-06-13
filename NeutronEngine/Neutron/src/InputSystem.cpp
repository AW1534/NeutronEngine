//
// Created by aw1lt on 24/11/22.
//
#include <Logger/Logger.h>
#include "Neutron/Events.h"
#include "Neutron/InputSystem.h"

#include <GLFW/glfw3.h>

namespace Neutron::Input {
    static void key_callback_wrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
        InputSystems.find(window)->second->key_callback(key, scancode, action, mods);
    }

    void InputSystem::key_callback(int key, int scancode, int action, int mods) {
        EventArgs args;

        args["inputSystem"] = this; // TODO: this is for debugging purposes.
        args["window"] = this->window;

        args["key"] = &key;
        args["scancode"] = &scancode;
        args["action"] = &action;
        args["mods"] = &mods;


        EventSystem::broadcast("input", args, false);
        Logger::Log(std::to_string(key));

        switch (action) {
            case GLFW_PRESS:
                this->keys.find(key)->second = true;
                Logger::Assert(this->keys.find(key)->second, "Input System check failed", 4, "NEUTRON");
                Logger::Info("inputPress", "NEUTRON");
                EventSystem::broadcast("inputPress", args, false);
                break;

            case GLFW_RELEASE:
                this->keys.find(key)->second = false;
                Logger::Info("inputRelease", "NEUTRON");
                EventSystem::broadcast("inputRelease", args, false);
                break;

            case GLFW_REPEAT:
                this->keys.find(key)->second = true;
                Logger::Info("inputRepeat", "NEUTRON");
                EventSystem::broadcast("inputRepeat", args, false);

            default:
                Logger::Info("unhandled input received: " + std::to_string(action), "NEUTRON");
        }
    }

    InputSystem::InputSystem(GLFWwindow *win) {
        InputSystems.insert({win, this});

        for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i) {
            keys[i] = false;
        }

        this->window = win;
        glfwSetKeyCallback(win, key_callback_wrapper);
    }

    InputSystem::~InputSystem() {
        InputSystems.erase(this->window);
    }

    bool InputSystem::keyDown(int key) {
        auto it = this->keys.find(key);
        if (it != this->keys.end()) {
            return it->second;
        }
        return false;
    }

    Math::Vector2 InputAxis2D::raw() const {
        return {float(this->x.raw()), float(this->y.raw())};
    }

    Math::Vector2 InputAxis2D::linear() {
        return {float(this->x.linear()), float(this->y.linear())};
    }

    Math::Vector2 InputAxis2D::smooth() const {
        return {float(this->x.smooth()), float(this->y.smooth())};;
    }

    void InputAxis2D::SetSpeed(double speed) {
        this->x.speed = speed;
        this->y.speed = speed;
    }

    void InputAxis2D::SetSmoothness(double smoothness) {
        this->x.smoothness = smoothness;
        this->y.smoothness = smoothness;
    }

    void InputAxis1D::SetSpeed(double speed) {
        this->axis.speed = speed;
    }

    void InputAxis1D::SetSmoothness(double smoothness) {
        this->axis.smoothness = smoothness;
    }

    double InputAxis1D::raw() const {
        return this->axis.raw();
    }

    double InputAxis1D::linear() {
        return this->axis.linear();
    }

    double InputAxis1D::smooth() const {
        return this->axis.smooth();
    }
} // Neutron::Input