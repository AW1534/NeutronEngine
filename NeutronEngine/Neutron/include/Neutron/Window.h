//
// Created by awilt on 21/10/22.
//

#ifndef NEUTRONENGINE_WINDOW_H
#define NEUTRONENGINE_WINDOW_H
#include <list>
#include <memory>
#include <GLFW/glfw3.h>
#include <thread>
#include "Neutron/macros/dll.h"

#include "Neutron/Math/Vector2.h"
#include "Color.h"
#include "Events.h"
#include "InputSystem.h"
#include "GameObject.h"

#include "Image.h"
#include "Shader.h"

// TODO: create a better window management system with proper multithreading

namespace Neutron {
    typedef std::map<std::string, void*> EventArgs;
    typedef std::function<void(EventArgs)> Callback;

    GLFWwindow *CreateWindow(int, int, const char *, GLFWmonitor *, GLFWwindow *);

    void GLAPIENTRY
    MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam );

    class EXPORT Window {
    public:
        std::vector<GameObject*> gameObjects = {};
        std::shared_ptr<Input::InputSystem> inputSystem;

        double deltaTime;
        GLFWwindow *glfwWindow{};
        Color bg = Color(0, 0, 0, 255);
        int id;
        bool vulkanSupported;
        //Shader defaultShader = Shader(Shader::default_vert, Shader::default_frag);

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

        void AddGameObject(GameObject *go);

        void setIcon(const std::string& icon_path) const;
        void setIcon(Image icon) const;

    private:
        void Constructor(char *title, int width, int height, bool fs, int id);

        void Render();

        void RemoveGameObject(GameObject *go);

        void UpdateObjects();

        void StartObjects();
    };

    static std::list<Window*> windows;
    static int generateId();
    Window* getWindow(int id);
}


#endif //NEUTRONENGINE_WINDOW_H
