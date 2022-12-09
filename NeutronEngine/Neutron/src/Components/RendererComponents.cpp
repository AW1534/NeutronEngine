//
// Created by awilt on 02/11/22.
//

#include <GLFW/glfw3.h>
#include "Neutron/Components/RendererComponents.h"

#include "../../include/Neutron/GameObject.h"

namespace Neutron {
    std::vector<int> generateIndexBuffer(std::vector<Math::Vector2> vertices) {
        std::vector<int> indexBuffer = {};
        for (int i = 0; i < vertices.size() - 2; i++) {
            indexBuffer.push_back(0);
            indexBuffer.push_back(i+1);
            indexBuffer.push_back(i+2);
        }

        return indexBuffer;
    }

    void MeshRendererComponent::Draw(bool vulkan) {
        int triangles = this->indexBuffer.size()/3;
        int tcount = 0;


        for (int x = 0; x<triangles; x++) {
            tcount++;
            glBegin(GL_TRIANGLES);
            try {
                for (int y = 0; y<3; y++) {
                    GameObject go = *(GameObject*) this->gameObject;
                    Math::Vector2 point = this->vertices[this->indexBuffer[x*3+y]];
                    Math::Vector2 p = point.movedBy(go.transform->position).scaledBy(go.transform->scale);
                    glVertex2f(p.x, p.y);
                }
                glEnd();
            } catch (std::exception e) {
                Logger::Warn("There was an exception while rendering triangle #" + std::to_string(tcount) + " in a mesh");
            }
        }
    }

    MeshRendererComponent* MeshRendererComponent::setShape(std::vector<Math::Vector2> vertices, std::vector<int> indexBuffer) {
        if (indexBuffer.empty()) {
            indexBuffer = generateIndexBuffer(vertices);
        }

        std::vector<Math::Vector2> v = vertices;

        this->indexBuffer = indexBuffer;
        this->vertices = vertices;

        return this;
    }

} // Neutron