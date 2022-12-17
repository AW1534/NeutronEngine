//
// Created by aw1lt on 24/11/22.
//

#ifndef NEUTRONENGINE_INPUTSYSTEM_H
#define NEUTRONENGINE_INPUTSYSTEM_H

#include <memory>
#include <map>
#include <GLFW/glfw3.h>

#include "Neutron/Math/Vector2.h"
#include "Neutron/Math/Axis.h"

#include "Neutron/macros/dll.h"

// TODO: Finish InputSystem
// TODO: Figure out input values

namespace Neutron::Input {

    enum EXPORT Type {
        GENERIC,
        PRESS,
        RELEASE,
        REPEAT
    };

    class EXPORT InputValue {
        virtual void Input() {};
        virtual void Update() {};
    };

    class EXPORT InputAxis1D : public InputValue {
    public:
        Math::Axis axis = Math::Axis(0, 0);

        int positiveKey;
        int negativeKey;

        InputAxis1D(GLFWwindow* win, int pos, int neg) : positiveKey(pos), negativeKey(neg) {};

        void SetSpeed(double speed);
        void SetSmoothness(double smoothness);

        double raw() const;
        double linear();
        double smooth() const;
    };

    class EXPORT InputAxis2D : public InputValue {
    public:
        // constructor that takes a Window pointer and four GLFW key codes
        Math::Axis x = Math::Axis(0, 0);
        Math::Axis y = Math::Axis(0, 0);

        int posxKey;
        int negxKey;
        int posyKey;
        int negyKey;


        InputAxis2D(GLFWwindow *win, int x_pos, int x_neg, int y_pos, int y_neg) : posxKey(x_pos), negxKey(x_neg), posyKey(y_pos), negyKey(y_neg) {
            Logger::Log("menu mardi pudd");
        }

        void SetSpeed(double speed);
        void SetSmoothness(double smoothness);

        Math::Vector2 raw() const;
        Math::Vector2 linear();
        Math::Vector2 smooth() const;
    };

    class EXPORT InputSystem {
    public:
        std::map<std::string, std::shared_ptr<InputValue*>> inputValues;

        template <typename T>
        T GetValue(std::string key) {
            return dynamic_cast<T>(*inputValues[key]);
        }

        explicit InputSystem(GLFWwindow* win);

    };

} // Neutron

#endif //NEUTRONENGINE_INPUTSYSTEM_H
