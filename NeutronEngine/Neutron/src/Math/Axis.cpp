//
// Created by awilt on 22/11/22.
//

#include "Neutron/Math/Axis.h"
#include <cmath>

namespace Neutron::Math {
    Axis::Axis(double *pos, double *neg) {
        this->val = pos - neg;
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
        return ps_val;
    }

    void Axis::Update(int pos, int neg) {
        this->val = pos - neg;

        this->UpdateSmooth();
    }

    void Axis::UpdateSmooth() {

        double raw = this->raw();

        if(ps_val == raw) return;

        if(ps_val < raw)
            ps_val += abs(ps_val - raw) / smoothness;
        else if(ps_val > raw)
            ps_val -= abs(ps_val - raw) / smoothness;

        if(ps_val > 1)
            ps_val = 1;
        else if(ps_val < -1)
            ps_val = -1;
        else if(abs(raw - ps_val) <= this->smoothSnapThreshold)
            ps_val = raw;
    }
} // Neutron