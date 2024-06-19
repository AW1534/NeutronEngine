//
// Created by awilt on 26/10/22.
//

#ifndef NEUTRONENGINE_OBJECT_H
#define NEUTRONENGINE_OBJECT_H

#include <list>
#include <vector>
#include <memory>
#include "GLFW/glfw3.h"
#include "../include/Neutron/Math/Vector2.h"
#include "../include/Neutron/Components/BaseComponent.h"

#include "../include/Neutron/macros/dll.h"
#include "Neutron/Components/Transform.h"

// TODO: Make a mesh editor? (maybe with Python)

namespace Neutron {
    class EXPORT GameObject {
    public:
        std::vector<GameObject*> children;
        std::vector<std::shared_ptr<BaseComponent>> components;
        Transform* transform;

        virtual void _Awake(void* win) {
            this->transform = AddComponent<Transform>();
            for (std::shared_ptr<BaseComponent> component : this->components) {
                component->pre_Awake(win, this);
            }
        }

        virtual void _Start() {
            for (std::shared_ptr<BaseComponent> component : this->components) {
                component->pre_Start();
            }
        }

        virtual void _Update(GLFWwindow* win, bool useVulkan) {
            Update(win, useVulkan);
            for (std::shared_ptr<BaseComponent> component : components) {
                component->Update();
            }
        }

        virtual void Update(GLFWwindow* win, bool useVulkan) {
            for (std::shared_ptr<BaseComponent> component : components) {
                component->Draw(useVulkan);
            }
        }


        template <typename T, typename ...Args>
        T* AddComponent(Args&&... args) {
            std::shared_ptr<T> comp = std::make_shared<T>();
            this->components.push_back(comp);
            return &(*comp);
        }

        template <typename T>
        T* GetComponent() {
            for (std::shared_ptr<BaseComponent> comp : this->components) {
                if (T* res = dynamic_cast<T*>(&(*comp))) {
                    return &(*res);
                }
            }

            return nullptr;
        }
    };

} // Neutron

#endif //NEUTRONENGINE_OBJECT_H
