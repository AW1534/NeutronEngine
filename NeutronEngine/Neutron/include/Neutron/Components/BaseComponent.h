//
// Created by aw1lt on 29/11/22.
//

#ifndef NEUTRONENGINE_BASECOMPONENT_H
#define NEUTRONENGINE_BASECOMPONENT_H

#include "Neutron/InputSystem.h"

struct InputArgs {
    int key;
    int scancode;
    int action;
    int mods;
};

namespace Neutron {
    class BaseComponent {
    public:
        void* win;
        void* gameObject;

        BaseComponent();
        ~BaseComponent();
        virtual void pre_Awake(void* win, void* go);
        virtual void Awake();
        virtual void pre_Start();
        virtual void Start();
        virtual void Update();
        virtual void Draw(bool vulkan);
        virtual void Input(InputArgs args);
        virtual void InputPress(InputArgs args);
        virtual void InputRelease(InputArgs args);
        virtual void InputRepeat(InputArgs args);

        void handleMethod(Neutron::Input::Type type, InputArgs args);
    };

} // Neutron

#endif //NEUTRONENGINE_BASECOMPONENT_H
