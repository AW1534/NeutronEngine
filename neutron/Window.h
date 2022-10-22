//
// Created by awilt on 21/10/22.
//

#ifndef NEUTRONENGINE_WINDOW_H
#define NEUTRONENGINE_WINDOW_H
#include "Vector2.h"
#include "Color.h"
#include <GLFW/glfw3.h>
#include <thread>
#include "Events.h"

namespace Neutron {

    GLFWwindow *CreateWindow(int, int, const char *, GLFWmonitor *, GLFWwindow *);

    class Window {
    public:
        GLFWwindow *glfwWindow{};
        Color bg = Color(0, 0, 0, 0);
        EventSystem eventSystem;

        Window();

        ~Window();

        explicit Window(char *title);

        explicit Window(bool fs);

        Window(int width, int height);

        Window(char *title, int width, int height);

        Window(char *title, int width, int height, bool fs);

    private:
        void Constructor(char *title, int width, int height, bool fs);
    };
}


#endif //NEUTRONENGINE_WINDOW_H
