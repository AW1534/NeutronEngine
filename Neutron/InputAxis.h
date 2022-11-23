//
// Created by awilt on 22/11/22.
//

#ifndef NEUTRONENGINE_INPUTAXIS_H
#define NEUTRONENGINE_INPUTAXIS_H

#include "Math/Axis.h"
#include "Math/Vector2.h"

namespace Neutron {

    class InputAxis {
    public:
        Axis x;
        Axis y;

        void SetSpeed(double speed);
        void SetSmoothness(double smoothness);

        Vector2 raw();
        Vector2 linear();
        Vector2 smooth();
    };

} // Neutron

#endif //NEUTRONENGINE_INPUTAXIS_H
