//
// Created by awilt on 22/11/22.
//

#ifndef NEUTRONENGINE_AXIS_H
#define NEUTRONENGINE_AXIS_H

#include "Neutron/macros/dll.h"

namespace Neutron::Math {

    class EXPORT Axis {
    public:
        double smoothSnapThreshold = 0.01;
        double deadzone = 0;

        double ps_val = 0; // previous smooth value
        double pl_val = 0; // previous linear value
        double val = 0;

        double speed = 0;
        double smoothness = 0.2;

        Axis(double* pos, double* neg);

        [[nodiscard]] double raw() const;
        double linear();
        [[nodiscard]] double smooth() const;
        void UpdateSmooth();

        void Update(int pos, int neg);
    };

} // Neutron

#endif //NEUTRONENGINE_AXIS_H
