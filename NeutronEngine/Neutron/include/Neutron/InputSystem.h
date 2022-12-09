//
// Created by aw1lt on 24/11/22.
//

#ifndef NEUTRONENGINE_INPUTSYSTEM_H
#define NEUTRONENGINE_INPUTSYSTEM_H

#include <map>
#include <GLFW/glfw3.h>

#include "Neutron/Math/Vector2.h"
#include "Neutron/Math/Axis.h"

#include "Neutron/macros/dll.h"

// TODO: Finish InputSystem
// TODO: Figure out input values

namespace Neutron::Input {

    enum EXPORT Type {
        GENERIC,
        PRESS,
        RELEASE,
        REPEAT
    };

    class EXPORT InputValue {

    };

    class EXPORT InputAxis : public InputValue {
    public:
        Math::Axis x;
        Math::Axis y;

        void SetSpeed(double speed);
        void SetSmoothness(double smoothness);

        Math::Vector2 raw();
        Math::Vector2 linear();
        Math::Vector2 smooth();
    };

    class EXPORT InputSystem {
    public:
        std::map<char, InputValue> inputValues = {};

        InputSystem(GLFWwindow* win);
    };

} // Neutron

#endif //NEUTRONENGINE_INPUTSYSTEM_H
