//
// Created by aw1lt on 15/06/24.
//

#include <glad/gl.h>
#include "Neutron/Texture.h"

namespace Neutron {

    void Texture::Constructor(Image image) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        format = GL_RGB;
        if (image.channels == 1) {
            format = GL_RED;
        } else if (image.channels == 3) {
            format = GL_RGB;
        } else if (image.channels == 4) {
            format = GL_RGBA;
        }

        format = GL_RGBA; // TODO: FIX THE TEXTURES PLEASEEEEE

        glTexImage2D(GL_TEXTURE_2D, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::Texture(Image image) {
        Constructor(image);
    }

    Texture::Texture(std::string path) {
        Constructor(Image(path));
    }

    void Texture::Enable() {
        glActiveTexture(GL_TEXTURE0); // You can use GL_TEXTURE0 + i for multiple textures
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
}