//
// Created by awilt on 21/10/22.
//

#ifndef NEUTRONENGINE_COLOR_H
#define NEUTRONENGINE_COLOR_H


#include <string>

namespace Neutron {
    class Color {
    public:

        float red = 255;
        float green = 255;
        float blue = 255;
        float alpha = 255;

        Color(float red, float green, float blue, float alpha);
        [[nodiscard]] Color Normalise(int num = 1) const;

        explicit operator std::string();
    };

    class Colour : Color {

    };
}


#endif //NEUTRONENGINE_COLOR_H
