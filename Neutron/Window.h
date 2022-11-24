//
// Created by awilt on 21/10/22.
//

#ifndef NEUTRONENGINE_WINDOW_H
#define NEUTRONENGINE_WINDOW_H
#include "Math/Vector2.h"
#include "Color.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <list>
#include "Events.h"
#include "Objects/GameObject.h"
#include "InputSystem.h"

// TODO: create a better window management system with proper multithreading

namespace Neutron {
    typedef std::map<std::string, void*> EventArgs;
    typedef std::function<void(EventArgs)> Callback;

    GLFWwindow *CreateWindow(int, int, const char *, GLFWmonitor *, GLFWwindow *);

    class Window {
    public:
        std::vector<GameObject*> gameObjects = {};
        std::vector<InputSystem*> inputSystems = {};

        double deltaTime;
        GLFWwindow *glfwWindow{};
        Color bg = Color(0, 0, 0, 255);
        int id;
        bool vulkanSupported;

        struct Size {
            int x = 0;
            int y = 0;
        } size;

        Window();
        explicit Window(char *title);
        explicit Window(bool fs);
        Window(int width, int height);
        Window(char *title, int width, int height);
        Window(char *title, int width, int height, bool fs);
        Window(int id);
        Window(char *title, int id);
        Window(bool fs, int id);
        Window(int width, int height, int id);
        Window(char *title, int width, int height, int id);
        Window(char *title, int width, int height, bool fs, int id);
        ~Window();

        void on(char *name, Callback cb);
        void UpdateObject(GameObject* obj);

    private:
        void Constructor(char *title, int width, int height, bool fs, int id);

        void Render();

        static void InputHandler(GLFWwindow *window, int key, int scancode, int action, int mods);
    };

    static std::list<Window*> windows;
    static int generateId();
    Window* getWindow(int id);
}


#endif //NEUTRONENGINE_WINDOW_H
