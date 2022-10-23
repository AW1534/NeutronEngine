//
// Created by awilt on 21/10/22.
//

#ifndef NEUTRONENGINE_WINDOW_H
#define NEUTRONENGINE_WINDOW_H
#include "Vector2.h"
#include "Color.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <list>
#include "Events.h"

namespace Neutron {
    GLFWwindow *CreateWindow(int, int, const char *, GLFWmonitor *, GLFWwindow *);

    class Window {
    public:
        GLFWwindow *glfwWindow{};
        Color bg = Color(50, 50, 60, 255);

        Window();
        explicit Window(char *title);
        explicit Window(bool fs);
        Window(int width, int height);
        Window(char *title, int width, int height);
        Window(char *title, int width, int height, bool fs);

        ~Window();

    private:
        void Constructor(char *title, int width, int height, bool fs);
    };

    static std::list<Window*> windows;
}


#endif //NEUTRONENGINE_WINDOW_H
