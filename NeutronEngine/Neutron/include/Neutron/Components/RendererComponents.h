//
// Created by awilt on 02/11/22.
//

#ifndef NEUTRONENGINE_DRAWABLE_H
#define NEUTRONENGINE_DRAWABLE_H

#include "Neutron/Math/Vector2.h"
#include "vector"
#include "BaseComponent.h"
#include "Neutron/Shader.h"
#include "Neutron/Texture.h"
#include "Neutron/Color.h"

namespace Neutron {

    std::vector<unsigned int> GenerateIndexBuffer(const std::vector<Math::Vector2>& vertices);
    std::vector<Color> GenerateColorMap(std::vector<Math::Vector2> &vertices, Color color);

    std::vector<float> PrimitiveVertexBuffer(std::vector<Math::Vector2> &vertices);
    std::vector<float> PrimitiveVertexBuffer(std::vector<Math::Vector2> &vertices, Color color);
    std::vector<float> PrimitiveVertexBuffer(std::vector<Math::Vector2>& vertices, std::vector<Color>& colors);

    struct Vertex {
        float x, y;         // Position
        float r, g, b, a;    // Color
        float u, v;         // Texture coordinates
    };

    class MeshRendererComponent : public BaseComponent {
    public:
        bool visible = true;

        std::vector<unsigned int> indexBuffer {};
        std::vector<Math::Vector2> vertexBuffer {};
        Shader* shader;
        Texture* texture;
        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint ebo = 0;

        MeshRendererComponent* setShape(std::vector<Math::Vector2> vertexBuffer, std::vector<unsigned int> indexBuffer, Color color = {255, 255, 255});
        MeshRendererComponent* setShape(std::vector<Math::Vector2> vertexBuffer, std::vector<unsigned int> indexBuffer = {}, std::vector<Color> = {});

        void Draw(bool vulkan) override;
        ~MeshRendererComponent();
    };

} // Neutron

#endif //NEUTRONENGINE_DRAWABLE_H
