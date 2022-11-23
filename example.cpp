#include "Neutron/Window.h"
#include "Neutron/Events.h"
#include "Neutron/Logger.h"
#include "Neutron/Color.h"
#include "Neutron/Objects/GameObject.h"
#include "Neutron/macros/input.h"
#include "Neutron/macros/mesh.h"

using namespace Neutron;

int main() {
    Logger::level = 0;
    float speed = 100;

    EventSystem::get("windowInitializing")->on([](EventArgs args) {
       Window* win = (Window*) args["window"];

       std::vector<Vector2> vertices = {
           Vector2(0.0, 0.0),
           Vector2(0.25, 0.5),
           Vector2(0.5, 0.0),
           Vector2(0.5, -0.5),
           Vector2(0.0, -0.5)
       };

       MeshDrawable triMesh = MeshDrawable(vertices);
       win->gameObjects.push_back(new MeshObject(triMesh));
       win->bg = Color(255, 0, 255, 255);
    });

    EventSystem::get("inputPress")->on([](EventArgs args) {
        int* key = (int*) args["key"];

        if (*key == KEY_SPACE) {
            Logger::Log("jump u fucking cunt");
        }

        if (*key == KEY_ESCAPE) {
            exit(0);
        }
    });

    EventSystem::get("inputRelease")->on([](EventArgs args) {
    });

    EventSystem::get("beforeRender")->on([](EventArgs args) {
        Window* win = (Window*) args["window"];

        win->gameObjects[0]->position.y += 10 * win->deltaTime;
    });

    Window(0);
    return 0;
}