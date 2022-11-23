//
// Created by awilt on 02/11/22.
//

#ifndef NEUTRONENGINE_DRAWABLE_H
#define NEUTRONENGINE_DRAWABLE_H

#include "Math/Vector2.h"
#include "vector"

namespace Neutron {

    class Drawable {
    public:
        virtual void Draw(bool vulkan);
    };

    class MeshDrawable : Drawable {
    public:
        std::vector<int> indexBuffer;
        std::vector<Vector2> vertices;

        explicit MeshDrawable(std::vector<Vector2> vertices, std::vector<int> indexBuffer = {});
        ~MeshDrawable();
        void Draw(bool vulkan, Vector2 offset = Vector2(0, 0));
    };

    class TextDrawable : Drawable {

    };

} // Neutron

#endif //NEUTRONENGINE_DRAWABLE_H
