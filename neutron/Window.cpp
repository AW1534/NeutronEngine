//
// Created by awilt on 21/10/22.
//

#include "Window.h"
#include "Events.h"
#include "Logger.h"

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


        return window;
    }

    void Window::Constructor(char *title, int width, int height, bool fs) {
        // Create Window
        this->glfwWindow = CreateWindow(width, height, title, fs ? glfwGetPrimaryMonitor() : nullptr, nullptr);

        windows.push_back(this);

        if (this->glfwWindow == nullptr) {
            delete this;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(this->glfwWindow);

        EventSystem::broadcast("windowCreated", false);
        while (!glfwWindowShouldClose(this->glfwWindow)) {

            Color col = this->bg.Normalise();

            Logger::Log((std::string)col);

            EventArgs eArgs = EventArgs();
            eArgs["window"] = reinterpret_cast<std::any *>(this);

            EventSystem::broadcast("update", eArgs);
            /* Render here */
            glClearColor(col.red, col.green, col.blue, col.alpha);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            /* Swap front and back buffers */
            glfwSwapBuffers(this->glfwWindow);

            /* Poll for and process events */
            glfwPollEvents();

            GLenum err = glGetError();
            if (err) {
                std::cout << "ERROR " << err << std::endl;
            }
        }
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
        if (this->glfwWindow) {
            glfwDestroyWindow(this->glfwWindow);
        }

        windows.remove(this);

        // Terminate GLFW if no more windows exist
        if (windows.empty()) {
            glfwTerminate();
        }
    }
}
