//
// Created by awilt on 22/11/22.
//

#include "InputAxis.h"

namespace Neutron {
    Vector2 InputAxis::raw() {
        return Vector2(float(this->x.raw()), float(this->y.raw()));
    }

    Vector2 InputAxis::linear() {
        return Vector2(float(this->x.linear()), float(this->y.linear()));;
    }

    Vector2 InputAxis::smooth() {
        return Vector2(float(this->x.smooth()), float(this->y.smooth()));;
    }

    void InputAxis::SetSpeed(double speed) {
        this->x.speed = speed;
        this->y.speed = speed;
    }

    void InputAxis::SetSmoothness(double smoothness) {
        this->x.smoothness = smoothness;
        this->y.smoothness = smoothness;
    }
} // Neutron