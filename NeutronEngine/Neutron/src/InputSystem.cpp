//
// Created by aw1lt on 24/11/22.
//
#include <Logger/Logger.h>
#include "Neutron/Events.h"
#include "Neutron/InputSystem.h"

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
        Logger::Log("test");
        glfwSetKeyCallback(win, key_callback);
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