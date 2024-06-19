//
// Created by aw1lt on 15/06/24.
//

#ifndef NEUTRONENGINE_TEXTURE_H
#define NEUTRONENGINE_TEXTURE_H

#include "Image.h"


namespace Neutron {
    class Texture {
    public:
        GLuint textureID;
        int width;
        int height;
        GLenum format = GL_RGB;

        explicit Texture(Image image);
        explicit Texture(std::string path);

        void Enable();

    protected:
        void Constructor(Image image);
    };
}


#endif //NEUTRONENGINE_TEXTURE_H
