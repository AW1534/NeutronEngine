//
// Created by awilt on 22/11/22.
//

#ifndef NEUTRONENGINE_AXIS_H
#define NEUTRONENGINE_AXIS_H

#include "Neutron/macros/dll.h"

namespace Neutron::Math {

    class EXPORT Axis {
    public:
        double pl_val = 0;
        double val = 0;

        double speed = 0;
        double smoothness = 0.2;

        Axis(double* pos, double* neg);

        [[nodiscard]] double raw() const;
        double linear();
        [[nodiscard]] double smooth() const;
    };

} // Neutron

#endif //NEUTRONENGINE_AXIS_H
