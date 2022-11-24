//
// Created by aw1lt on 24/11/22.
//

#ifndef NEUTRONENGINE_INPUTSYSTEM_H
#define NEUTRONENGINE_INPUTSYSTEM_H

#include <map>
#include "Math/Vector2.h"
#include "Math/Axis.h"

// TODO: Finish InputSystem
// TODO: Figure out input values

namespace Neutron {

    class InputValue {

    };

    class InputAxis : InputValue {
    public:
        Axis x;
        Axis y;

        void SetSpeed(double speed);
        void SetSmoothness(double smoothness);

        Vector2 raw();
        Vector2 linear();
        Vector2 smooth();
    };

    class InputSystem {
        std::map<char, InputValue> inputValues = {};


    };

} // Neutron

#endif //NEUTRONENGINE_INPUTSYSTEM_H
