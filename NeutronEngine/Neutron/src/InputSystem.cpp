//
// Created by aw1lt on 24/11/22.
//
#include "Neutron/Logger.h"
#include "Neutron/Events.h"
#include <GLFW/glfw3.h>

namespace Neutron::Input {
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        EventArgs args;

        for (auto it : windows) {
            if (it->glfwWindow == window) {
                args["window"] = it;
            }
        }

        args["key"] = &key;
        args["scancode"] = &scancode;
        args["action"] = &action;
        args["mods"] = &mods;


        EventSystem::broadcast("input", args, false);

        switch (action) {
            case GLFW_PRESS:
                Logger::Info("inputPress", "NEUTRON");
                EventSystem::broadcast("inputPress", args, false);
                break;

            case GLFW_RELEASE:
                Logger::Info("inputRelease", "NEUTRON");
                EventSystem::broadcast("inputRelease", args, false);
                break;

            case GLFW_REPEAT:
                Logger::Info("inputRepeat", "NEUTRON");
                EventSystem::broadcast("inputRepeat", args, false);

            default:
                Logger::Info("unhandled input received: " + std::to_string(action), "NEUTRON");
        }
    }

    InputSystem::InputSystem(GLFWwindow *win) {
        glfwSetKeyCallback(win, key_callback);
    }

    Math::Vector2 InputAxis::raw() {
        return Math::Vector2(float(this->x.raw()), float(this->y.raw()));
    }

    Math::Vector2 InputAxis::linear() {
        return Math::Vector2(float(this->x.linear()), float(this->y.linear()));;
    }

    Math::Vector2 InputAxis::smooth() {
        return Math::Vector2(float(this->x.smooth()), float(this->y.smooth()));;
    }

    void InputAxis::SetSpeed(double speed) {
        this->x.speed = speed;
        this->y.speed = speed;
    }

    void InputAxis::SetSmoothness(double smoothness) {
        this->x.smoothness = smoothness;
        this->y.smoothness = smoothness;
    }
} // Neutron::Input