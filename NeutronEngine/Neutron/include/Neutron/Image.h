//
// Created by aw1lt on 14/06/24.
//

#ifndef NEUTRONENGINE_IMAGE_H
#define NEUTRONENGINE_IMAGE_H

#include <string>

#include "Logger.h"
#include <GLFW/glfw3.h>

class Image {
public:
    int width{};
    int height{};
    int channels{};

    bool loaded = false;
    unsigned char* image;

    explicit Image(std::string path);

    ~Image();

    GLFWimage asGlfwImage();

    explicit operator GLFWimage() {
        return asGlfwImage();
    }
};

#endif //NEUTRONENGINE_IMAGE_H
