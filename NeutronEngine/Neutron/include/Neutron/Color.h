//
// Created by awilt on 21/10/22.
//

#ifndef NEUTRONENGINE_COLOR_H
#define NEUTRONENGINE_COLOR_H

#define Colour Color

#include <string>

namespace Neutron {
    class Color {
    public:

        float red = 255;
        float green = 255;
        float blue = 255;
        float alpha = 255;

        Color(float red, float green, float blue, float alpha = 255);
        [[nodiscard]] Color Normalise(int num = 1) const;

        operator std::string();
    };
}


#endif //NEUTRONENGINE_COLOR_H
