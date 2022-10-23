//
// Created by awilt on 20/10/22.
//

#include <cmath>
#define _USE_MATH_DEFINES
#include "Vector2.h"
#include <string>

namespace Neutron {
    Vector2::Vector2() {
        this->x = 0;
        this->y = 0;
    }

    Vector2::Vector2(int x, int y) {
        this->x = x;
        this->y = y;
    }

    float Vector2::getMagnitude() const {
        return std::sqrt(std::hypot(Vector2::x, Vector2::y));
    }

    float Vector2::getRadians() const {
        return std::atan2(Vector2::x, Vector2::y);
    }

    __attribute__((unused)) float Vector2::getDegrees() const {
        return 180 * this->getRadians() / M_PI;
    }

    Vector2::operator std::string() const {
        std::string txt = "(X: " + std::to_string(this->x) + ", Y: " + std::to_string(this->y) + ")";
        return txt;
    }

    void Vector2::Normalize(float targetMagnitude = 1) {
        float mag = this->getMagnitude();

        if (mag > 0) {
            this->x *= targetMagnitude/mag;
            this->y *= targetMagnitude/mag;
        }
    }

    Vector2 Vector2::operator+(Vector2 v) {
        return Vector2(v.x + this->x, v.y + this->y);
    }

    Vector2 Vector2::operator-(Vector2 v) {
        return Vector2(v.x - this->x, v.y - this->y);
    }

    int Vector2::operator*(Vector2 v) {
        return v.x * this->x + v.y * this->y;
    }

    Vector2 Vector2::operator+(int n) {
        return Vector2(this->x + n, this->y + n);
    }

    Vector2 Vector2::operator-(int n) {
        return Vector2(this->x - n, this->y - n);
    }

    Vector2 Vector2::operator*(int n) {
        return Vector2(this->x * n, this->y * n);
    }

    Vector2 Vector2::operator/(int n) {
        return Vector2(this->x / n, this->y / n);
    }

}