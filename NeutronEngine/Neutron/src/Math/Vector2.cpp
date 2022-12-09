//
// Created by awilt on 20/10/22.
//

#include <cmath>
#include "Neutron/Math/Vector2.h"

namespace Neutron::Math {
    Vector2::Vector2() : Matrix<3, 1>() {
        this->Constructor(0, 0);
    }

    Vector2::Vector2(double x, double y) : Matrix<3, 1>() {
        this->Constructor(x, y);
    }

    Vector2::Vector2(const Vector2 &original) : Matrix<3, 1>() {
        Constructor(original.data[0][0], original.data[1][0]);
    }

    Vector2::Vector2(const Matrix &original) : Matrix<3, 1>() {
        Constructor(original(0, 0), original(1, 0));
    }

    void Vector2::Constructor(double x, double y) {
        data[0][0] = x;
        data[1][0] = y;
        Proxy<double>::set_ref(this->x, data[0][0]);
        Proxy<double>::set_ref(this->y, data[1][0]);
        this->data[2][0] = 1;
    }

    double Vector2::getMagnitude() {
        return std::sqrt(std::hypot((double)this->x, (double)this->y));
    }

    double Vector2::getRadians() {
        return std::atan2((double)this->x, (double)this->y);
    }

    double Vector2::getDegrees() {
        return 180 * this->getRadians() / M_PI;
    }

    void Vector2::Normalize(double targetMagnitude = 1) {
        float mag = this->getMagnitude();

        if (mag > 0) {
            this->x *= targetMagnitude/mag;
            this->y *= targetMagnitude/mag;
        }
    }

    Vector2 Vector2::movedBy(const Vector2 other) {
        return Vector2(*this + other);
    }

    Vector2 Vector2::rotatedBy(const Vector2 other) {
        Logger::Warn("Rotation attempted but not implemented");
        return *this;
    }

    Vector2 Vector2::scaledBy(const Vector2 other) {
        return Vector2((*this) * Matrix<3, 3>::Scale({ *other.x, *other.y }));
    }

    Vector2 Vector2::operator+(Vector2 other) {
        return Vector2(
                this->x + other.x,
                this->y + other.y
                );
    }

    Vector2 Vector2::operator-(Vector2 other) {
        return Vector2(
                this->x - other.x,
                this->y - other.y
        );
    }
}