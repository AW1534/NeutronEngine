//
// Created by awilt on 21/10/22.
//

#include "Window.h"
#include "Events.h"

#include <GLFW/glfw3.h>
#include <thread>
#include <iostream>

namespace Neutron {
    GLFWwindow *CreateWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
        GLFWwindow *window;

        /* Initialize the library */
        if (!glfwInit())
            return nullptr;

        window = glfwCreateWindow(width, height, title, monitor, share);
        if (!window) {
            glfwTerminate();
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClearColor(0.25, 0.25, 0.25, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            GLenum err = glGetError();
            if (err) {
                std::cout << "ERROR " << err << std::endl;
            }
        }

        return window;
    }

    void Window::Constructor(char *title, int width, int height, bool fs) {
        // Create Window
        this->glfwWindow = CreateWindow(width, height, title, fs ? glfwGetPrimaryMonitor() : nullptr, nullptr);

        // Create Thread
        std::thread([this]() {
            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(this->glfwWindow)) {
                /* Render here */
                glClearColor(1, 0, 0, 1);
                glClear(GL_COLOR_BUFFER_BIT);
                /* Swap front and back buffers */
                glfwSwapBuffers(this->glfwWindow);

                /* Poll for and process events */
                glfwPollEvents();

                GLenum err = glGetError();
                if (err) {
                    std::cout << "ERROR " << err << std::endl;
                }
            }
        }).join();
    }

// region Window definitions
    Window::Window() {
        this->Constructor((char *) "Neutron Engine", 640, 480, false);
    }

    Window::Window(char *title) {
        this->Constructor(title, 640, 480, false);
    }

    Window::Window(int width, int height) {
        this->Constructor((char *) "Neutron Engine", width, height, false);
    }

    Window::Window(bool fs) {
        this->Constructor((char *) "Neutron Engine", 640, 480, fs);
    }

    Window::Window(char *title, int width, int height) {
        this->Constructor(title, width, height, false);
    }

    Window::Window(char *title, int width, int height, bool fs) {
        this->Constructor(title, width, height, fs);
    }

// endregion

    Window::~Window() {
        std::cout << "window destroyed?" << std::endl;
        if (this->glfwWindow) {
            glfwDestroyWindow(this->glfwWindow);
        }
    }
}
