//
// Created by awilt on 21/10/22.
//

#include <cstring>
#include "Color.h"
#include <string>
#include <iostream>

namespace Neutron {
    Color::Color(float red, float green, float blue, float alpha) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }

    Color Color::Normalise(int num) const {
        return(Color(
                (this->red == 0) ? 0 : (this->red / 255) * num,
                (this->green == 0) ? 0 : (this->green / 255) * num,
                (this->blue == 0) ? 0 : (this->blue / 255) * num,
                (this->alpha == 0) ? 0 : (this->alpha / 255) * num
        ));
    }

    Color::operator std::string() {
        std::string txt = "(R: " + std::to_string(this->red) + ", G: " + std::to_string(this->green) +  ", B: " + std::to_string(this->blue) + ", A: " + std::to_string(this->alpha) + ")";
        return txt;
    }
}