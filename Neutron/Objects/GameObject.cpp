//
// Created by awilt on 26/10/22.
//

#include <GLFW/glfw3.h>
#include "GameObject.h"
#include "../Logger.h"

namespace Neutron {

    void GameObject::_update(GLFWwindow* win, bool useVulkan) {
        update(win, useVulkan);
    }

    void GameObject::update(GLFWwindow* win, bool useVulkan) {

    }

    void GameObject::update() {

    }

    void MeshObject::_update(GLFWwindow* win, bool useVulkan) {
        update(win, useVulkan);
    }

    void MeshObject::update(GLFWwindow* win, bool useVulkan) {
        this->mesh.Draw(useVulkan, this->position);
    }

    void MeshObject::update() {

    }

    MeshObject::MeshObject(MeshDrawable mesh) : mesh(mesh) {

    }
} // Neutron