//
// Created by awilt on 20/10/22.
//

#ifndef NEUTRONENGINE_VECTOR2_H
#define NEUTRONENGINE_VECTOR2_H

#include <string>
#include "Matrix.h"

#include "Neutron/macros/dll.h"

namespace Neutron::Math {
    class EXPORT Vector2 : public Matrix<3, 1> {
    public:
        Vector2();
        Vector2(float, float);
        Vector2(const Vector2& original);
        Vector2(const Matrix &original);

        float x;
        float y;
        [[nodiscard]] float getMagnitude();
        [[nodiscard]] float getRadians();
        [[nodiscard]] float getDegrees();
        void Normalize(float);

        Vector2 movedBy(const Vector2 other);
        Vector2 scaledBy(const Vector2 other);
        Vector2 rotatedBy(const Vector2 other);

        Vector2& operator=(const Vector2& other) = default;
        Vector2& operator=(Vector2&& other) = default;

        Vector2 operator +(Vector2 other);
        Vector2 operator -(Vector2 other);

        double& operator ()(unsigned int x = 0, unsigned int y = 0) = delete;
        double operator ()(unsigned int x = 0, unsigned int y = 0) const = delete;

        operator std::string();

        void Constructor(float x, float y);
    };
}

#endif //NEUTRONENGINE_VECTOR2_H
