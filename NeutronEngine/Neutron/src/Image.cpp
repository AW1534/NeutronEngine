//
// Created by aw1lt on 14/06/24.
//

#include "Neutron/Image.h"

#define STB_IMAGE_IMPLEMENTATION // required for stb_image
#include "stb_image.h"
#include "Logger.h"

Image::Image(std::string path) {

    image = stbi_load(path.c_str(), &width, &height, &channels, 4);

    Logger::Assert(image != nullptr, "Failed to load '" + path + "'", 3);

    loaded = true;
}

Image::~Image() {
    stbi_image_free(image);
}

GLFWimage Image::asGlfwImage() {
    GLFWimage glfwImage;
    glfwImage.width = width;
    glfwImage.height = height;
    glfwImage.pixels = image;

    return glfwImage;
}