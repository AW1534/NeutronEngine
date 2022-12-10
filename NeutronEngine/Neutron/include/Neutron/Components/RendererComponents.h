//
// Created by awilt on 02/11/22.
//

#ifndef NEUTRONENGINE_DRAWABLE_H
#define NEUTRONENGINE_DRAWABLE_H

#include "Neutron/Math/Vector2.h"
#include "vector"
#include "BaseComponent.h"
#include "Neutron/Shader.h"

namespace Neutron {
    std::vector<int> generateIndexBuffer(std::vector<Math::Vector2> vertices);

    class MeshRendererComponent : public BaseComponent {
    public:
        std::vector<int> indexBuffer {};
        std::vector<Math::Vector2> vertices {};
        Shader* shader;

        MeshRendererComponent* setShape(std::vector<Math::Vector2> vertices, std::vector<int> indexBuffer = {});
        void Draw(bool vulkan);
    };

} // Neutron

#endif //NEUTRONENGINE_DRAWABLE_H
