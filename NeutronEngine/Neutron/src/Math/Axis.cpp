//
// Created by awilt on 22/11/22.
//

#include "Neutron/Math/Axis.h"
#include <cmath>

namespace Neutron::Math {
    Axis::Axis(double *pos, double *neg) {

    }

    double Axis::raw() const {
        return Axis::val;
    }

    double Axis::linear() {
        if (pl_val == val) {return val;}

        double lVal = pl_val + speed;
        if (pl_val < val && lVal > val) {pl_val = val; return val;}
        if (pl_val > val && lVal < val) {pl_val = val; return val;}

        pl_val = lVal;
        return lVal;
    }

    double Axis::smooth() const {
        return pl_val - pl_val * (1 - abs(int(pl_val))) * (1 - smoothness);
    }
} // Neutron