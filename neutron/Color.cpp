//
// Created by awilt on 21/10/22.
//

#include "Color.h"

namespace Neutron {
    Color::Color(float red, float green, float blue, float alpha) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }

    Color Color::outOf(int num) {
        return(Color(
                this->red == 0 ? 0 :( this->red / 255) * num,
                this->green == 0 ? 0 : (this->green / 25) * num,
                this->blue == 0 ? 0 : (this->blue / 25) * num,
                this->alpha == 0 ? 0 : (this->alpha / 25) * num
        ));
    }

}