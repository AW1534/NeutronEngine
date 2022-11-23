//
// Created by awilt on 21/10/22.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "macros/input.h"
#include "Window.h"
#include "Events.h"
#include "Logger.h"
#include "Objects/GameObject.h"

#include <iostream>
#include <csignal>

namespace Neutron {
    GLFWwindow *CreateWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
        GLFWwindow *window;

        if (!glewInit() != GLEW_OK) {
            Logger::Crit("GLEW returned an error when initializing");
            return nullptr;
        }

        if (!glfwInit()) {
            Logger::Crit("GLFW returned an error when initializing");
            return nullptr;
        }

        window = glfwCreateWindow(width, height, title, monitor, share);
        if (!window) {
            glfwTerminate();
        }


        return window;
    }

    void Window::Render() {
        for(auto obj : this->gameObjects) {
            this->UpdateObject(obj);
        }
    }

    void Window::InputHandler(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
        EventArgs args;

        for (auto it : windows) {
            if (it->glfwWindow == glfwWindow) {
                args["window"] = it;
            }
        }

        args["key"] = &key;
        args["scancode"] = &scancode;
        args["action"] = &action;
        args["mods"] = &mods;


        EventSystem::broadcast("input", args, false);

        switch (action) {
            case GLFW_PRESS:
                Logger::Info("inputPress");
                EventSystem::broadcast("inputPress", args, false);
                break;

            case GLFW_RELEASE:
                Logger::Info("inputRelease");
                EventSystem::broadcast("inputRelease", args, false);
                break;

            default:
                Logger::Info("unhandled input received");
        }
    }

    void segFaultHandler(int sig) {
        Logger::Error("interrupted by signal " + std::to_string(sig) + " (SIGSEGV)");
    }

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    void Window::Constructor(char *title, int width, int height, bool fs, int id) {
        signal(SIGSEGV, segFaultHandler);

        this->id = id;
        // Create Window
        this->glfwWindow = CreateWindow(width, height, title, fs ? glfwGetPrimaryMonitor() : nullptr, nullptr);
        this->vulkanSupported = glfwVulkanSupported();

        windows.push_back(this);

        if (this->glfwWindow == nullptr) {
            delete this;
        }

        glfwSetTime(0);

        EventArgs args;
        args["window"] = this;
        EventSystem::broadcast("windowInitializing", args);
        glfwSetKeyCallback(this->glfwWindow, InputHandler);
        while (!glfwWindowShouldClose(this->glfwWindow)) {
            /* Make the window's context current */
            glfwMakeContextCurrent(this->glfwWindow);

            glfwGetWindowSize(this->glfwWindow, &this->size.x, &this->size.y);
            this->deltaTime = glfwGetTime();
            Color col = this->bg.Normalise();

            EventArgs eArgs = EventArgs();
            eArgs["window"] = this;

            glViewport(0, 0, this->size.x, this->size.y);
            EventSystem::broadcast("beforeRender", eArgs);
            //EventSystem::broadcast("updateSync", eArgs, false);
            /* Render here */
            glClearColor(col.red, col.green, col.blue, col.alpha);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Render();

            /* Swap front and back buffers */
            glfwSwapBuffers(this->glfwWindow);

            /* Poll for and process events */
            glfwPollEvents();

            GLenum err = glGetError();
            if (err) {
                std::string e = (char *) (intptr_t) err;
                std::string txt = "ERROR";

                Logger::Warn(txt + e);

            }
            glfwSetTime(0);
        }
    }

#pragma region Window constructor implementations

    Window::Window() {
        this->Constructor((char *) "Neutron Engine", 640, 480, false, generateId());
    }

    Window::Window(char *title) {
        this->Constructor(title, 640, 480, false, generateId());
    }

    Window::Window(int width, int height) {
        this->Constructor((char *) "Neutron Engine", width, height, false, generateId());
    }

    Window::Window(bool fs) {
        this->Constructor((char *) "Neutron Engine", 640, 480, fs, generateId());
    }

    Window::Window(char *title, int width, int height) {
        this->Constructor(title, width, height, false, generateId());
    }

    Window::Window(char *title, int width, int height, bool fs) {
        this->Constructor(title, width, height, fs, generateId());
    }

    Window::Window(int id) {
        this->Constructor((char *) "Neutron Engine", 640, 480, false, id);
    }

    Window::Window(char *title, int id) {
        this->Constructor(title, 640, 480, false, id);
    }

    Window::Window(int width, int height, int id) {
        this->Constructor((char *) "Neutron Engine", width, height, false, id);
    }

    Window::Window(bool fs, int id) {
        this->Constructor((char *) "Neutron Engine", 640, 480, fs, id);
    }

    Window::Window(char *title, int width, int height, int id) {
        this->Constructor(title, width, height, false, id);
    }

    Window::Window(char *title, int width, int height, bool fs, int id) {
        this->Constructor(title, width, height, fs, id);
    }

#pragma endregion Window constructor implementations

    int generateId() {
        bool done = false;
        int curr = 0;
        while (!done) {
            for (auto it = windows.begin(); it != windows.end(); ++it){
                if ((*it)->id == curr) {
                    goto nextIt;
                }
            }
            done = true;
            nextIt:
                curr = random();
        }
        return curr;
    }

    Window* getWindow(int id) {
        for (auto it = windows.begin(); it != windows.end(); ++it){
            if ((*it)->id == id) {
                return (*it);
            }
        }

        return nullptr;
    }

    Window::~Window() {
        if (this->glfwWindow) {
            glfwDestroyWindow(this->glfwWindow);
        }

        windows.remove(this);

        // Terminate GLFW if no more windows exist
        if (windows.empty()) {
            Logger::Log("Window closed, calling glfwTerminate because no more windows are alive");
            EventSystem::deconst();
            for (GameObject* go : this->gameObjects) {
                delete go;
            }

            glfwTerminate();
        } else {
            Logger::Log("Window closed, but not calling glfwTerminate because more windows are alive");
        }
    }

    void Window::on(char* name, Callback cb) {
        Logger::Log(std::to_string(this->id) + "Has subscribed to " + name);
        EventSystem::get(name)->on([this, cb](EventArgs data) mutable {
            if (((Window*)data["window"])->id == this->id) {
                cb(data);
            }
        });
    }

    void Window::UpdateObject(GameObject *obj) {
        obj->_update(this->glfwWindow, this->vulkanSupported);
        for (auto o : obj->children) {
            UpdateObject(o);
        }
    }
}
