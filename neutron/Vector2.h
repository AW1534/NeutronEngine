//
// Created by awilt on 20/10/22.
//

#ifndef NEUTRONENGINE_VECTOR2_H
#define NEUTRONENGINE_VECTOR2_H

#include <string>

namespace Neutron {
    class Vector2 {
    public:
        Vector2();
        Vector2(int, int);
        float x;
        float y;
        [[nodiscard]] float getMagnitude() const;
        [[nodiscard]] float getRadians() const;
        [[nodiscard]] float getDegrees() const;
        void Normalize(float);

        Vector2 operator + (Vector2);
        Vector2 operator - (Vector2);
        int operator * (Vector2);

        Vector2 operator + (int);
        Vector2 operator - (int);
        Vector2 operator * (int);
        Vector2 operator / (int);

        explicit operator std::string() const;
    };
}

#endif //NEUTRONENGINE_VECTOR2_H
