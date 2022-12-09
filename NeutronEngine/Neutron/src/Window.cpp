//
// Created by awilt on 21/10/22.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Neutron/Window.h"
#include "Neutron/Shader.h"

#include <iostream>
#include <csignal>

namespace Neutron {
    Shader* s = nullptr;

    void segFaultHandler(int sig) {
        Logger::Error("interrupted by signal " + std::to_string(sig) + " (SIGSEGV). If you can confirm it is not as a result of your code, please create an issue on GitHub to report this.", "NEUTRON");
    }

    GLFWwindow *CreateWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) {
        signal(SIGSEGV, segFaultHandler);
        GLFWwindow *window;

        if (!glfwInit()) {
            Logger::Crit("GLFW returned an error when initializing. The window will not be created.", "NEUTRON");
            return nullptr;
        }

        window = glfwCreateWindow(width, height, title, monitor, share);
        if (!window) {
            glfwTerminate();
        }

        GLenum glewErr = glewInit();

        if (glewErr != GLEW_OK) {
            Logger::Warn(std::string((char*)glewGetErrorString(glewErr)), "NEUTRON");
        }

        return window;
    }

    void Window::AddGameObject(GameObject* go) {
        this->gameObjects.push_back(go);
        go->_Awake(this);
    }

    void Window::RemoveGameObject(GameObject* target) {
        int i = 0;
        for (GameObject* go : gameObjects) {
            if (go == target) {
                delete gameObjects[i];  // guaranteed to cause a segfault, because i'm not deleting it from the vector so the engine will continue to try operations on it
                break;
            }

            i++;
        }
    }

    void Window::UpdateObjects() {
        for (GameObject* go : gameObjects) {
            go->_Update(
                    this->glfwWindow,
                    this->vulkanSupported
            );
        }
    }

    void Window::StartObjects() {
        for (GameObject* go : gameObjects) {
            go->_Start();
        }
    }

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    void Window::Constructor(char *title, int width, int height, bool fs, int id) {
        this->id = id;
        // Create Window
        this->glfwWindow = CreateWindow(width, height, title, fs ? glfwGetPrimaryMonitor() : nullptr, nullptr);
        this->vulkanSupported = glfwVulkanSupported();

        //s = new Shader("pla.frag");

        windows.push_back(this);

        if (this->glfwWindow == nullptr) {
            delete this;
        }

        glfwSetTime(0);

        EventArgs wargs;
        wargs["window"] = this;
        EventSystem::broadcast("windowInitializing", wargs);
        EventArgs bargs;
        bargs["window"] = this;
        EventSystem::broadcast("beforeStartObjects", bargs, false);
        this->StartObjects();
        //Logger::Log(std::to_string(s.id));
        //glUseProgram(s->id);
        while (!glfwWindowShouldClose(this->glfwWindow)) {
            std::make_unique<Input::InputSystem>(glfwWindow);

            /* Make the window's context current */
            glfwMakeContextCurrent(this->glfwWindow);

            glfwGetWindowSize(this->glfwWindow, &this->size.x, &this->size.y);
            this->deltaTime = glfwGetTime();
            Color col = this->bg.Normalise();

            EventArgs eArgs = EventArgs();
            eArgs["window"] = this;

            glViewport(0, 0, this->size.x, this->size.y);
            //EventSystem::broadcast("beforeRender", eArgs);
            //EventSystem::broadcast("updateSync", eArgs, false);
            /* Render here */
            glClearColor(col.red, col.green, col.blue, col.alpha);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            UpdateObjects();

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
        //glDeleteProgram(s->id);
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
            for (auto it = windows.begin(); it != windows.end(); ++it) {
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
        windows.remove(this);

        if (this->glfwWindow) {
            glfwDestroyWindow(this->glfwWindow);
        }

        // Terminate GLFW if no more windows exist
        if (windows.empty()) {
            Logger::Info("Window closed, calling glfwTerminate because no more windows are alive", "NEUTRON");
            EventSystem::deconst();
            for (GameObject* go : this->gameObjects) {
                delete go;
            }

            glfwTerminate();
        } else {
            Logger::Info("Window closed, but not calling glfwTerminate because more windows are alive", "NEUTRON");
        }
    }

    void Window::on(char* name, Callback cb) {
        EventSystem::get(name)->on([this, cb](EventArgs data) mutable {
            if (((Window*)data["window"])->id == this->id) {
                cb(data);
            }
        });
    }
}
