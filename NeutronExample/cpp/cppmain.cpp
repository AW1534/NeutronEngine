//
// Created by aw1lt on 06/12/22.
//

#include "Logger.h"
#include <Neutron/Components/RendererComponents.h>
#include <Neutron/Window.h>

#include "Controller.h"
#include "Neutron/Shader.h"
#include "Neutron/Utils/Files.h"
#include "Neutron/Texture.h"

using namespace Neutron;
using namespace Neutron::Utils;

int main(int argc, char *argv[]) {
    Shader* shader;
    Texture* p_tex;

    EventSystem::get("windowInitializing")->on([](EventArgs args) {

    });

    EventSystem::get("beforeStartObjects")->on([&](EventArgs args) {
        //Window* win = EventSystem::getArg<Window*>(args, "window");

        Window* win = (Window*) args["window"];

//        std::vector<Math::Vector2> vertices = { // pentagons
//                Math::Vector2(0.0, 0.0),
//                Math::Vector2(0.25, 0.5),
//                Math::Vector2(0.5, 0.0),
//                Math::Vector2(0.5, -0.5),
//                Math::Vector2(0.0, -0.5)
//        };

//        std::vector<Math::Vector2> vertices = {
//                Math::Vector2(0.5f,  0.5f),  // top right
//                Math::Vector2(0.5f, -0.5f),  // bottom right
//                Math::Vector2(-0.5f, -0.5f), // bottom left
//                Math::Vector2(-0.5f,  0.5f)  // top left
//        };


        std::vector<Math::Vector2> vertices = {
                Math::Vector2(0.5f,  -0.5f),  // top
                Math::Vector2(-0.5f, -0.5f),  // bottom right
                Math::Vector2(0.0f, 0.5f), // bottom left
        };

        std::vector<Color> colors = {
                {1.0f, 0.0f, 0.0f},  // bottom right
                {0.0f, 1.0f, 0.0f},  // bottom left
                {0.0f, 0.0f, 1.0f}   // top
        };

        win->bg = Color(255, 0, 255, 255);

        GameObject* player = new GameObject();
        p_tex = new Texture("../branding/logtex.jpeg");
        //player->AddComponent<Controller>();
        player->AddComponent<MeshRendererComponent>()->setShape(vertices, {}, colors);
        //player->GetComponent<MeshRendererComponent>()->texture = p_tex;
        win->AddGameObject(player);

        shader = new Shader("/home/aw1lt/CLionProjects/NeutronEngine/NeutronExample/cpp/player.frag");

        player->GetComponent<MeshRendererComponent>()->shader =shader;

//        GameObject* r = new GameObject();
//        //r->AddComponent<Controller>();
//        r->AddComponent<MeshRendererComponent>()->setShape(vertices);
//        r->GetComponent<MeshRendererComponent>()->shader =shader;
//        win->AddGameObject(r);
//
//        r->transform->position = Math::Vector2(0.1, 0.1);
    });

    Window();
    free(shader);
    free(p_tex);

    return 0;
}