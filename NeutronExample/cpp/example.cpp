//
// Created by aw1lt on 06/12/22.
//

#include <Neutron/Logger.h>
#include <Neutron/Components/RendererComponents.h>
#include <Neutron/Window.h>

#include "Controller.h"
#include "Neutron/Shader.h"
#include "Neutron/Utils/Files.h"

using namespace Neutron;
using namespace Neutron::Utils;

int main(int argc, char *argv[]) {
    Logger::Log("Neutron is now a lib. I would like to kindly invite you to suck it.");

    EventSystem::get("windowInitializing")->on([](EventArgs args) {

    });

    EventSystem::get("beforeStartObjects")->on([](EventArgs args) {
        //Window* win = EventSystem::getArg<Window*>(args, "window");
        Window* win = (Window*) args["window"];

        std::vector<Math::Vector2> vertices = {
                Math::Vector2(0.0, 0.0),
                Math::Vector2(0.25, 0.5),
                Math::Vector2(0.5, 0.0),
                Math::Vector2(0.5, -0.5),
                Math::Vector2(0.0, -0.5)
        };

        win->bg = Color(255, 0, 255, 255);

        GameObject* player = new GameObject();
        player->AddComponent<Controller>();
        player->AddComponent<MeshRendererComponent>()->setShape(vertices);
        win->AddGameObject(player);
        Logger::Assert(false, "ok");
    });

    Window();

    return 0;
}