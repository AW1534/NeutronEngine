//
// Created by aw1lt on 14/06/24.
//

#ifndef NEUTRONENGINE_IMAGE_H
#define NEUTRONENGINE_IMAGE_H

#include <string>

#include "Logger.h"
#include <GLFW/glfw3.h>
#include "Math/Vector2.h"

namespace Neutron {
    enum ImageChannels {
        GRAYSCALE = 1,
        TWO_CHANNELS = 2,
        RGB = 3,
        RGBA = 4
    };

    class Image {
    public:
        unsigned char* data;
        int width{};
        int height{};
        int channels{};

        bool loaded = false;

        void resize(int width, int height);

        explicit Image(std::string path, Math::Vector2);
        explicit Image(std::string path, int width, int height);
        explicit Image(std::string path);

        ~Image();

        GLFWimage asGlfwImage();

        explicit operator GLFWimage() {
            return asGlfwImage();
        }

    protected:
        int actualWidth{};
        int actualHeight{};
        void Constructor(std::string path);
    };

}
#endif //NEUTRONENGINE_IMAGE_H
