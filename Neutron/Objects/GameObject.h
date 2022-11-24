//
// Created by awilt on 26/10/22.
//

#ifndef NEUTRONENGINE_OBJECT_H
#define NEUTRONENGINE_OBJECT_H

#include <list>
#include "GLFW/glfw3.h"
#include "../Drawable.h"

// TODO: Make a mesh editor? (maybe with Python)

namespace Neutron {
    class GameObject {
    public:
        Vector2 position = Vector2(0, 0);
        std::vector<GameObject*> children;

        virtual void _update(GLFWwindow* win, bool useVulkan);
        virtual void update();
        virtual void update(GLFWwindow *win, bool useVulkan);
    };

    class MeshObject : public GameObject {
    public:
        MeshObject(MeshDrawable mesh);

        MeshDrawable mesh;

        virtual void _update(GLFWwindow* win, bool useVulkan);
        virtual void update();
        virtual void update(GLFWwindow *win, bool useVulkan);
    };

} // Neutron

#endif //NEUTRONENGINE_OBJECT_H
