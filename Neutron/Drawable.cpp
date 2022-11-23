//
// Created by awilt on 02/11/22.
//

#include <GLFW/glfw3.h>
#include "Drawable.h"
#include "Logger.h"
#include "Helper.h"

namespace Neutron {
    void Drawable::Draw(bool vulkan) {
        Logger::Log("No defined draw method");
    }

    void MeshDrawable::Draw(bool vulkan, Vector2 offset) {
        int triangles = this->indexBuffer.size()/3;
        int tcount = 0;


        for (int x = 0; x<triangles; x++) {
            tcount++;
            glBegin(GL_TRIANGLES);
            try {
                for (int y = 0; y<3; y++) {
                    Vector2 point = this->vertices[this->indexBuffer[x*3+y]];
                    glVertex2f(point.x + offset.x, point.y + offset.y);
                }
                glEnd();
            } catch (std::exception e) {
                Logger::Warn("There was an exception while rendering triangle #" + std::to_string(tcount) + " in a mesh");
            }
        }
    }

    MeshDrawable::MeshDrawable(std::vector<Vector2> vertices, std::vector<int> indexBuffer) {

        if (indexBuffer.empty()) {
            indexBuffer = generateIndexBuffer(vertices);
        }

        this->indexBuffer = indexBuffer;
        this->vertices = vertices;
    }

    MeshDrawable::~MeshDrawable() {
        Logger::Info("mesh destroyed");
    }

} // Neutron